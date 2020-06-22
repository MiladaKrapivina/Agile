#include "agile.h"

DateBase::DateBase()
{
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("D://Agile.db");
    db.open();
    if(!db.isOpen()){
        qDebug() << "Connect to database-Fail";
    }else{
        qDebug() << "Connect to database-OK";
    }
    query=new QSqlQuery(db);
}

DateBase::~DateBase()
{
    delete query;
    db.close();
    db.removeDatabase("D://Agile.db");
}

void DateBase::exec()
{
    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
}


void DateBase::createUser(QString name, QString password)
{
    query->prepare("INSERT INTO user ( name, password) "
                   "VALUES ( :name, :password);");
    query->bindValue(":name",name);
    query->bindValue(":password",password);
    exec();// заносим данные в БД
    query->prepare("SELECT user_id from user WHERE name=:name;");
    query->bindValue(":name",name);
    exec();
    query->next();
    QJsonObject obj;
    obj["meth"]="1";
    obj["id"]=query->value(0).toString();//извлекаем id пользователя
    QJsonDocument    doc(obj);
    data=doc.toJson();
    // отправить
}

void DateBase::create(QString obj,QString name, int owner)
{
    if(obj=="project"){
        query->prepare("INSERT INTO project (name, owner)" "VALUES (:name, :owner);");
    }else if(obj=="task"){
        query->prepare("INSERT INTO task (name, owner)" "VALUES ( :name, :owner);");
    }else{//subtask
        query->prepare("INSERT INTO subtask (text, task)"
                       "VALUES (:name, :owner);");
    }
    query->bindValue(":name",name);
    query->bindValue(":owner",owner);
    exec();
}

// посмотреть позже ///////////////////////////////////////////
void DateBase::delete_(QString obj, int id)
{
    if(obj=="user"){
        query->prepare("DELETE FROM user WHERE user_id=:id;");
        query->bindValue(":id",id);
        exec();
        query->prepare("SELECT project_id FROM project WHERE owner=:id;");
        query->bindValue(":id",id);
        exec();
        while (query->next())
        {
            QString d=query->value(0).toString();
            query->prepare("DELETE FROM task WHERE owner=:d;");
            query->bindValue(":d",d);
        }
        query->prepare("DELETE FROM project WHERE owner=:id;");
        query->bindValue(":id",id);
    }else
        if(obj=="project"){
            query->prepare("DELETE FROM project WHERE project_id=:id;");
            query->bindValue(":id",id);
            exec();
            query->prepare("DELETE FROM task WHERE owner=:id;");
            query->bindValue(":id",id);
        }else
            if(obj=="task"){
            query->prepare("DELETE FROM task WHERE task_id=:id;");
            query->bindValue(":id",id);
            exec();
            query->exec("DELETE FROM subtask WHERE task=:id;");
            query->bindValue(":id",id);
        }else{//subtask
            query->prepare("DELETE FROM subtask WHERE id=:id;");
            query->bindValue(":id",id);
        }
    exec();
}
////////////////////////////////////////////////////////////
void DateBase::set_(QString param, int id, QString value)
{
    if(param=="done"){
        query->prepare("UPDATE task SET  done=:value WHERE task_id=:id;");
    }else
        if(param=="important"){
            query->prepare("UPDATE task SET  important=:value WHERE task_id=:id;");
        }else
            if(param=="priority"){
                query->prepare("UPDATE task SET  priority=:value WHERE task_id=:id;");
            }else
                if(param=="comm"){
                    query->prepare("UPDATE task SET  comm=:value WHERE task_id=:id;");
                  }else{
                        query->prepare("UPDATE subtask SET  done=:value WHERE id=:id;");
                    }
    query->bindValue(":value",value);
    query->bindValue(":id",id);
    exec();
}

void DateBase::get_all(QString param, int id)
{
    if(param=="project"){
        query->prepare("SELECT project_id, name from project WHERE owner=:id;");
    }else
    {
        query->prepare("SELECT task_id, name from task WHERE owner=:id;");
    }
    query->bindValue(":id",id);
    exec();
    ///запрос выполнился
    QJsonArray valArr;
    QJsonObject temp;
    while(query->next()){
        temp["id"]=query->value(0).toString();
        temp["name"]=query->value(1).toString();
        valArr.append(temp);
    }
    QJsonObject obj;
    obj["meth"]="2";
    obj["param"]=param;
    obj["id"]=id;
    obj["values"]=valArr;
   QJsonDocument    doc(obj);
   qDebug() << "UUUUUUUUU"<<doc;
   data=doc.toJson();
}

QJsonArray DateBase::lists(QString list, QString param,int id)
{
    if(list=="done"){
    query->prepare("SELECT task_id, name from task WHERE owner=:id AND done=:value;");
    }
    else
    {
    query->prepare("SELECT task_id, name from task WHERE owner=:id AND priority=:value;");
    }
    query->bindValue(":id",id);
    query->bindValue(":value",param);
    exec();

    QJsonArray ar;
    while(query->next()){
        qDebug()<<"))))))))"<<query->value(1).toString();
        ar.append(query->value(1).toString());
    }
    return ar;
}

void DateBase::get_tasklist(QString param, int id)
{
    QJsonObject obj;

    if(param=="done"){
        obj["done_0"]=lists("done","0",id);
        obj["done_1"]=lists("done","1",id);
        obj["done_2"]=lists("done","2",id);
    }else
        if(param=="important"){
            query->prepare("SELECT task_id, name from task WHERE owner=:id AND important=:value;");
            query->bindValue(":id",id);
            query->bindValue(":value","1");
            exec();
            QJsonArray ar;
            while(query->next()){
                 ar.append(query->value(1).toString());
            }
            obj["imp"]=ar;
        }else
            if(param=="priority"){
                obj["pr0"]=lists ("prior","0",id);
                obj["pr1"]=lists ("prior","1",id);
                obj["pr2"]=lists ("prior","2",id);
                obj["pr3"]=lists ("prior","3",id);
                obj["pr4"]=lists ("prior","4",id);
            }
    obj["meth"]="4";// метод
    obj["param"]=param;
   QJsonDocument    doc(obj);
   qDebug() << "UUUUUUUUU"<<doc;
   data=doc.toJson();

}

void DateBase::get_task_info(int id )
{
    query->prepare("SELECT task_id, name, done, important, comm, priority  from task WHERE task_id=:id;");
    query->bindValue(":id",id);
    exec();
    query->next();
    QJsonObject val;
    QString t=query->value(0).toString();
    val["meth"]="3";
    val["done"]=query->value(2).toInt();
    val["important"]=query->value(3).toInt();
    val["comm"]=query->value(4).toString();
    val["priority"]=query->value(5).toInt();
    query->prepare("SELECT id, text  from subtask WHERE task=:task;");
    query->bindValue(":task",t);
    exec();
    QJsonArray valArr;
    QJsonObject temp;
    while(query->next()){
        temp["id"]=query->value(0).toString();
        temp["text"]=query->value(1).toString();
        valArr.append(temp);
    }
    val["subtasks"]=valArr;
    QJsonDocument    doc(val);
    data=doc.toJson();
}

QString  DateBase::returndata()
{
    return data;
}

void DateBase::check_user(QString name, QString password)
{
    query->prepare("SELECT user_id from user WHERE name =:name AND password=:pass;");
        query->bindValue(":name",name);
        query->bindValue(":pass",password);
        exec();
        query->next();
if( !query->value(0).toString().isEmpty()){
    get_all("project",query->value(0).toInt());
}
}

