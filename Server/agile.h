#ifndef AGILE_H
#define AGILE_H

#include "Header.h"

class DateBase{
   public:
   DateBase();
  ~DateBase();
   void check_user (QString name,QString password);
   void createUser(QString name, QString password);
   void create(QString obj, QString name, int owner);
   void delete_(QString obj, int id);
   void set_(QString param, int id, QString value);
   void get_all(QString param, int id);
   void get_tasklist(QString param, int id);
   void get_task_info(int id);
   QString  returndata();
   private:
   void exec();// проверка
QJsonArray lists(QString list, QString param,int id);
private:
   QSqlQuery *query;
   QString data;
   QSqlDatabase db;
};

#endif // AGILE_H
