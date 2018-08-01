//Copyright (C) 2018 Norbertas Kremeris, LIME MICROSYSTEMS

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "qtermwidget5/qtermwidget.h"
#include <QTextEdit>
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
    /// Slot for processing all button clicks, 'index' - no. of sender
    void onGuiButtonClick(int index);
    void on_actionABOUT_triggered();

    void sendCtrlC();

private:
    Ui::MainWindow *ui;
    bool osmo_running = false;

    /// This keeps button configuration information loaded from the config.json file
    ButtonList buttons;
    /// This is the list of pointers to dynamically generated GUI QPushButtons
    QList<QPushButton*> guiButtonList; //gui button list

    /// Activates all GUI pushbuttons
    void guiButtonActivate();
    /// Deactivates all GUI pushbuttons except no. 'index'
    void guiButtonDeactivate(int index);

    void setTextTermFormatting(QTextEdit * textEdit, QString const & text);
    void parseEscapeSequence(int attribute, QListIterator< QString > & i, QTextCharFormat & textCharFormat, QTextCharFormat const & defaultTextCharFormat);

    int mFontSize = 8;
};

#endif // MAINWINDOW_H
