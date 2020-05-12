#ifndef AGILE_H
#define AGILE_H

#include "AgileServer.h"
#include "Header.h"

class base{
public:
    base();
    QString returndata();

protected:
    QSqlQuery *query;
    QString data;
    QSqlDatabase db;
};

class user: public base {

public:

    void debug();
    void create_user(QString name,QString email,QString password);
    void check_user (QString,QString password);
    void change_user_password(QString name, QString password);
    void delete_user(QString name);
    void get_all_project (QString user);
};


class project: public base {

public:
    void debug();
    void delete_project(QString name);
    void create_project(QString name,QString owner,QString tasks=nullptr);
    void get_all_tasks (QString project );
    void get_done_tasks (QString project);
    void get_imp_tasks (QString project);
    void get_prior_tasks (QString project, int prior);
};


class task: public base {
    bool check_pass(QString pass);

public:
    void get_task_info(QString name,QString project);
    void debug();
    void create_task(QString name,QString project,QString time);
    void delete_task(QString name);
    void set_done(QString taskname, QString i);
    void set_important(QString taskname, int i);
    void set_date(QString taskname, QString date);
    void set_priority(QString taskname, QString pr);
    void set_deadline(QString taskname, QString date);

};

#endif // AGILE_H
