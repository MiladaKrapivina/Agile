#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Header.h"
#include "agileclient.h"
#include "authorization.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_authorization_clicked();
    void change();
    void fillLiast();
    void settaskview();
    void get_List(QString param);
    void get_TaskINFO();
    void setCurrProj();
    void setCurrTask();
    void on_addproj_clicked();
    void create(QString param);
    void set(QString param);
    void set_imp();
    void set_done();
    void set_prior();
    void on_addtask_clicked();
    void on_SaveText_clicked();
    void delite(QString param);
    void get_sp_lists(QString param);
    void PslotCustomMenuRequested(QPoint pos);
    void TslotCustomMenuRequested(QPoint pos);
    void delpr();
    void delts();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    client* cli;
    QJsonDocument doc;
    authorization* ath=new authorization;
};


#endif // MAINWINDOW_H
