#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    void on_click_button(ButtonList &buttons, int index);

private:
    Ui::MainWindow *ui;
    bool osmo_running = false;
    ButtonList buttons;
};

#endif // MAINWINDOW_H
