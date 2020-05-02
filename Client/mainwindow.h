#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QtDebug>
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

 protected:
    Ui::MainWindow *ui;
};


class client: public QTcpSocket{
    Q_OBJECT

    QTcpSocket socket;
    QByteArray Data;

    public slots:
    void onReadyRead();
    void con_serv();

    void sockDisc();

 void write(QString  data);
};


#endif // MAINWINDOW_H
