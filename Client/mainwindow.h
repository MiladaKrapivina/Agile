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
    void on_addproj_clicked();
    void on_addtask_clicked();
    void change();
    void priorcolour();
    void setstartui();
    void updateTSlist();
    void setTasks_to_area();
    void updatePRlist();
    void setCurProj();
    void setCurTask();
    void filltaskW();
void setImp_to_Area();
    //
      void set_done();//проверить
      void set_important();

      void set_priority();
void setnot_done();
void fillImp();
void fillNdone();
protected:

    Ui::MainWindow *ui;
    QListWidget* alltask=new QListWidget;
    QListWidget* imptask=new QListWidget;
    QListWidget* notdone=new QListWidget;
private:
    client* cli;

};


#endif // MAINWINDOW_H
