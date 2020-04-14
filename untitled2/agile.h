#ifndef AGILE_H
#define AGILE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

class Agile
{
public:
    void connect_to_database();

    void delete_user(QString name);
    void delete_project(QString name);
    void delete_task(QString name);

    void create_user(QString name,QString email,QString password);
    void create_project(QString name,QString owner,QString tasks);
    void create_task(QString name,QString project,QString time);

    void change_user_password(QString name, QString password);

    void task_done(QString taskname);
    void task_important(QString taskname);
    void task_date(QString taskname, QString date);
    void task_priority(QString taskname, QString pr);
    void task_deadline(QString taskname, QString date);
void select(QString param,QString value);

private:

QSqlDatabase db;
QSqlQuery *query;

};

#endif // AGILE_H
