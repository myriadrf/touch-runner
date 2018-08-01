//Copyright (C) 2018 Norbertas Kremeris, LIME MICROSYSTEMS

#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
