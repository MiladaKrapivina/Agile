#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QtDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTcpSocket *socket;
    QByteArray Data;
public slots:
    void sockReady();
    void sockDisc();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
