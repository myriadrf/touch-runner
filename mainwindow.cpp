//Copyright (C) 2018 Norbertas Kremeris, LIME MICROSYSTEMS

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

#include <QFontDatabase>
//button information
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //setup sane terminal environment
    setenv("TERM", "xterm-256color", 1);
    //load button config
    buttons.load();

    mFontSize = buttons.getFontSize();

    ui->setupUi(this);
    ui->console_widget->changeDir("/opt");
    ui->console_widget->sendText("clear\r");

    //set console parameters
    //ui->console_widget->devicePixelRatio()
    QFont font = QApplication::font();
    font.setFamily("Monospace");
    font.setPointSize(mFontSize);
    ui->console_widget->setTerminalFont(font);
    ui->console_widget->setColorScheme("DarkPastels");


    //get no. of buttons
    int len = buttons.len();

    //set layout according to amount of buttons
    if(len <= 2)
        ui->gridLayout_2->setColumnMinimumWidth(1,0);
    else if(len > 2 && len <= 6)
        ui->gridLayout_2->setColumnMinimumWidth(2,0);
    else
        ui->gridLayout_2->setColumnMinimumWidth(3,0);

    //create QPushButton widgets for the GUI
    QFont guiButtonFont;
    guiButtonFont.setPointSize(mFontSize);
    for(int i = 0; i < len; i++){
        guiButtonList.append(new QPushButton(this));
        guiButtonList[i]->setFont(guiButtonFont);
        guiButtonList[i]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        guiButtonList[i]->setText(QString("Start\n" + buttons.buttonList()->at(i).name()));
        ui->gridLayout_2->addWidget(guiButtonList[i]);
        connect(guiButtonList[i], &QPushButton::clicked, [this,i](){this->onGuiButtonClick(i);});
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

void MainWindow::onGuiButtonClick(int index)
{
    if(buttons.locking(index)){
        if(buttons.active(index)){
            //stop currently active demo
            ui->console_widget->sendText(QString(buttons.buttonList()->at(index).stopCommand() + "\r"));
            guiButtonList[index]->setText(QString("Start\n" + buttons.buttonList()->at(index).name()));
            buttons.setActive(index,false);
            guiButtonActivate();

        } else{
            //start a new demo
            guiButtonList[index]->setText(QString("Stop\n" + buttons.buttonList()->at(index).name()));
            ui->console_widget->sendText(QString(buttons.buttonList()->at(index).startCommand() + "\r"));
            buttons.setActive(index,true);
            guiButtonDeactivate(index);
        }
    }//if(buttons.locking(index)

    else {
        //start a new demo, non locking
        ui->console_widget->sendText(QString(buttons.buttonList()->at(index).startCommand() + "\r"));
    }

    buttons.save();

}

void MainWindow::guiButtonActivate()
{
    int len = buttons.len();
    for(int i = 0; i < len; i++)
        guiButtonList[i]->setEnabled(true);
}

void MainWindow::guiButtonDeactivate(int index)
{
    int len = buttons.len();
    for(int i = 0; i < len; i++){
        if(i != index)
        guiButtonList[i]->setEnabled(false);

    }
}






void MainWindow::sendCtrlC()
{

    //not supported on Raspberry Pi3 DietPI-stretch (old qt libs at v5.7, needs v5.11)
/*
    foreach(QObject *obj, ui->console_widget->children())
      {
        if(QLatin1String(obj->metaObject()->className()) == QLatin1String("Konsole::TerminalDisplay"))
        {
          QKeyEvent *event1 = new QKeyEvent(QEvent::KeyPress, Qt::Key_C, Qt::ControlModifier);
          QCoreApplication::postEvent(obj, event1);

          QKeyEvent *event2 = new QKeyEvent(QEvent::KeyRelease, Qt::Key_C, Qt::ControlModifier);
          QCoreApplication::postEvent(obj, event2);
          break;
        }
      }
*/
}
