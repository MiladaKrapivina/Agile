#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setStyleSheet(
                "QPushButton{"
                "border-radius: 4px transparent;"
                "border-bottom: 3px transparent;"
                "border-right: 2px transparent;"
                "border-left: 2px transparent;}"
                "QPushButton:hover{"
                "background-color: rgb(255,130,00);} "
                "QPushButton:pressed  {"
                "background-color: rgb(232,95,76); } "
                );


    return a.exec();
}
