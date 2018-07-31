#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qtermwidget5/qtermwidget.h"

#include "about_dialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include "Button.h"
#include "ButtonList.h"
#include <QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //setup sane terminal environment
    setenv("TERM", "konsole-256color", 1);

    ui->setupUi(this);
    ui->console_widget->changeDir("/opt");
    ui->console_widget->sendText("clear\r");

    ui->centralWidget->layout()->setContentsMargins(2,2,2,2);

    //set console parameters
    //ui->console_widget->devicePixelRatio()
    QFont font = QApplication::font();
    font.setFamily("Monospace");
    //font.setPointSize(6);
    ui->console_widget->setTerminalFont(font);
    ui->console_widget->setColorScheme("Solarized");

    //=======BUTTON CONFIG=========
    //load button config

    buttons.load();

    //get no. of buttons
    int len = buttons.len();
    qDebug() << len;

    //set layout according to amount of buttons
    if(len <= 2)
        ui->gridLayout_2->setColumnMinimumWidth(1,0);
    else if(len > 2 && len <= 6)
        ui->gridLayout_2->setColumnMinimumWidth(2,0);
    else
        ui->gridLayout_2->setColumnMinimumWidth(3,0);


    for(int i = 0; i < len; i++){
        //qDebug() << button.name();
        newButton.append(new QPushButton(this));
        buttonsActive.append(new bool);
        buttonsActive[i] = false;
        newButton[i]->setText(QString("Start\n" + buttons.buttonList()->at(i).name()));
        ui->gridLayout_2->addWidget(newButton[i]);
        connect(newButton[i], &QPushButton::clicked, [this,i](){on_click_button(i);});
    }
    QObject::connect(ui->console_widget, SIGNAL(finished()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionABOUT_triggered()
{
    about_dialog about;
    about.setModal(true);
    about.exec();
}

void MainWindow::on_click_button(int index)
{
    //Button button = buttons.buttonList()[index];
    //qDebug() << index << button.name();
    //QMessageBox::warning(this,"ayy", QString("button clicked:" + buttons.buttonList()[index].name()));

    qDebug () << buttonsActive[index];
    if(buttonsActive[index]){
        //stop tasks
        qDebug() << "stopping";
        ui->console_widget->sendText(QString(buttons.buttonList()->at(index).stopCommand() + "\r"));
        newButton[index]->setText(QString("Start\n" + buttons.buttonList()->at(index).name()));
        buttonsActive[index] = false;
        buttonActivate();

    } else{
        //start tasks
        qDebug() << "starting";
        newButton[index]->setText(QString("Stop\n" + buttons.buttonList()->at(index).name()));
        ui->console_widget->sendText(QString(buttons.buttonList()->at(index).startCommand() + "\r"));
        buttonsActive[index] = true;
        buttonDeactivate(index);
    }
}

void MainWindow::buttonActivate()
{
    int len = buttons.len();
    for(int i = 0; i < len; i++)
        newButton[i]->setEnabled(true);
}

void MainWindow::buttonDeactivate(int index)
{
    int len = buttons.len();
    for(int i = 0; i < len; i++){
        if(i != index)
        newButton[i]->setEnabled(false);

    }
}


