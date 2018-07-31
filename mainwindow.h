//Copyright (C) 2018 Norbertas Kremeris, LIME MICROSYSTEMS

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "qtermwidget5/qtermwidget.h"

#include "ButtonList.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_pushButton_OsmoToggle_clicked();

    void on_actionABOUT_triggered();

    void on_click_button(int index);

private:
    Ui::MainWindow *ui;
    bool osmo_running = false;
    ButtonList buttons; //button information
    QList<QPushButton*> newButton; //gui button list
    QList<bool> buttonsActive;
    void buttonActivate();
    void buttonDeactivate(int index);
};

#endif // MAINWINDOW_H
