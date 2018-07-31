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
    font.setPointSize(6);
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
        ui->gridLayout_2->setColumnMinimumWidth(1,10);
    else if(len > 2 && len <= 6)
        ui->gridLayout_2->setColumnMinimumWidth(2,10);
    else
        ui->gridLayout_2->setColumnMinimumWidth(3,10);

    //create buttons
    //QPushButton *newButton[10];
    QList<QPushButton*> newButton;
    int i = 0;



    foreach(Button button, buttons.buttonList()){
        //qDebug() << button.name();
        newButton.append(new QPushButton(this));
        newButton[i]->setText(button.name());
        ui->gridLayout_2->addWidget(newButton[i]);

        //connect(action, &QAction::triggered, engine, [=]() { engine->processAction(action->text()); });
        //connect(button, &QPushButton::clicked, [this, button](){    ui->label->setText(button->text());        });
        connect(newButton[i], &QPushButton::clicked, [this,i](){on_click_button(buttons,i);});
        i++;
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

void MainWindow::on_click_button(ButtonList &buttons, int index)
{
    qDebug() << index << buttons.buttonList()[index].name();
    QMessageBox::warning(this,"ayy", QString("button clicked:" + buttons.buttonList()[index].name()));
}


