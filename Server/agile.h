#ifndef AGILE_H
#define AGILE_H

#include "AgileServer.h"


class user: public AServer{

   public:
      void create_user(QString name,QString email,QString password);
      void change_user_password(QString name, QString password);
      void delete_user(QString name);
};

class project: public AServer{
     public:
    void delete_project(QString name);
    void create_project(QString name,QString owner,QString tasks);
};

class task: public AServer{
    bool check_pass(QString pass);

public:
    void create_task(QString name,QString project,QString time);
    void delete_task(QString name);

     void set_done(QString taskname);
     void set_important(QString taskname);
     void set_date(QString taskname, QString date);
     void set_priority(QString taskname, QString pr);
     void set_deadline(QString taskname, QString date);
void select(QString param,QString value);
};

#endif // AGILE_H
