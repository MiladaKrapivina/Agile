#include "agile.h"


void user::debug()
{
    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
}

void user::  create_user(QString name,QString email,QString password)
{
    query->prepare("INSERT INTO user ( user_name, user_project, user_email, user_password) "
                   "VALUES ( :user_name, :user_project, :user_email, :user_password);");
    query->bindValue(":user_name",name);
    query->bindValue(":user_project","NULL");
    query->bindValue(":user_email",email);
    query->bindValue(":user_password",password);
    debug();
}

void user::check_user(QString name, QString password)
{
    query->prepare("SELECT user_id from user WHERE user_name =:name AND user_password=:pass;");
    query->bindValue(":name",name);
    query->bindValue(":pass",password);
    debug();
        get_all_project(name);

}

void project::  create_project(QString name,QString owner,QString tasks)
{
    query->prepare("INSERT INTO project ( project_name, project_owner, project_tasks) "
                   "VALUES ( :project_name, :project_owner, :project_tasks);");
    query->bindValue(":project_name",name);
    query->bindValue(":project_owner",owner);
    query->bindValue(":project_tasks",tasks);
    debug();
}

void task::get_task_info(QString name, QString project)
{
    query->prepare("SELECT  task_deadline, task_is_done, task_is_important, task_priority from task WHERE belong_to_project=:project AND task_name= :name;");
        query->bindValue(":project",project);
        query->bindValue(":name",name);
        debug();
        query->next();
         data="{ \"method\" : \"3\",";
            data+="\"deadline\":\""+ query->value(0).toString()+"\",";
            data+="\"done\":\""+ query->value(1).toString()+"\",";
            data+="\"important\":\""+ query->value(2).toString()+"\",";
            data+="\"priority\":\""+ query->value(3).toString()+"\"";
            qDebug() <<query->value(0).toString()<<"-"<<query->value(3).toString()<<endl; // работает


            data+="}";
    }


void task::debug()
{
    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
}

void task:: create_task(QString name, QString project, QString time)
{
    query->prepare("INSERT INTO task ( task_name, belong_to_project, task_create_time)"
                   "VALUES ( :task_name, :belong_to_project, :task_create_time);");
    query->bindValue(":task_name", name);
    query->bindValue(":belong_to_project", project);
    query->bindValue(":task_create_time", time);
    debug();
}

// посмотреть правильность каскадного удаления
void user::delete_user(QString name)
{
    query->exec("DELETE FROM user WHERE user_name=\""+name+"\";");
    query->exec("SELECT FROM project WHERE project_owner=\""+name+"\";");
    while (query->next())
    {
        QString d=query->value(2).toString();
        query->exec("DELETE FROM task WHERE belong_to_project=\""+d+"\";");
    }
    query->exec("DELETE FROM project WHERE project_owner=\""+name+"\";");
    debug();
}

void user::get_all_project(QString user)
{
    query->prepare("SELECT project_id, project_name from project WHERE project_owner =:user;");
    query->bindValue(":user",user);
    debug();
    qDebug() << "found: " << endl;

    data="{ \"method\" : \"1\",\"project\":[";
    while(query->next()){
        data+="\""+ query->value(1).toString()+"\",";
        qDebug() <<query->value(0).toString()<<"-"<<query->value(1).toString()<<endl; // работает
    }
    data.remove(data.size()-2,2);
    data+="\"]}";
    qDebug() <<data;
}

void project:: get_all_tasks (QString project ){

    query->prepare("SELECT task_id, task_name from task WHERE belong_to_project=:project;");
    query->bindValue(":project",project);
    debug();

    data="{ \"method\" : \"2\",\"tasks\":[";
    while(query->next()){
        data+="\""+ query->value(1).toString()+"\",";
        qDebug() <<query->value(0).toString()<<"-"<<query->value(1).toString()<<endl; // работает
    }
    data.remove(data.size()-2,2);
    data+="\"]}";
}


void project::debug()
{
    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
}

void project::delete_project(QString name)
{
    query->exec("DELETE FROM project WHERE project_name=\""+name+"\";");
    query->exec("DELETE FROM task WHERE belong_to_project=\""+name+"\";");
    debug();
}

void task::delete_task(QString name)
{
    query->exec("DELETE FROM task WHERE task_name=\""+name+"\";");
    debug();
}
//////////////////////////////
void task::set_done(QString taskname, QString i)
{
    query->prepare("UPDATE task SET  task_is_done=:i WHERE task_name=:taskname;");
    query->bindValue(":i",i);
    query->bindValue(":taskname",taskname);
    debug();
    if(query->isValid()){
        qDebug()<<"Done oke";
    }
}

void task::set_important(QString taskname,int i)
{
    query->prepare("UPDATE task SET  task_is_important=:i WHERE task_name=:taskname;");
    query->bindValue(":i",i);
    query->bindValue(":taskname",taskname);
    debug();
    if(query->isValid()){
        qDebug()<<"IMPORT oke";
    }
}
//////////////////////////////
void task:: set_date(QString taskname, QString date)
{
    query->exec("UPDATE task SET  task_create_time=\""+date+"\" WHERE task_name=\""+taskname+"\";");
    debug();
}

void user:: change_user_password(QString name, QString newpassword)
{
    query->exec("UPDATE user SET  user_password=\""+newpassword+"\" WHERE user_name=\""+name+"\";");
    debug();
}

void task:: set_priority(QString taskname, QString pr)
{
    query->exec("UPDATE task SET  task_priority=\""+pr+"\" WHERE task_name=\""+taskname+"\";");
    debug();
}

void task:: set_deadline(QString taskname, QString date)
{
    query->exec("UPDATE task SET  task_deadline=\""+date+"\" WHERE task_name=\""+taskname+"\";");
    debug();
}


void project:: get_done_tasks (QString project ){
    query->prepare("SELECT task_id, task_name from task WHERE belong_to_project=:project AND task_is_done=:i;");
    query->bindValue(":project",project);
    query->bindValue(":i",0);
    debug();
    qDebug() << "found: " << endl;
    data="{ \"method\" : \"5\",\"tasks\":[";
    while(query->next()){
        data+="\""+ query->value(1).toString()+"\",";
        qDebug() <<query->value(0).toString()<<"-"<<query->value(1).toString()<<endl; // работает
    }
    data.remove(data.size()-2,2);
    data+="\"]}";
}

void project:: get_imp_tasks (QString project){
    query->prepare("SELECT task_id, task_name from task WHERE belong_to_project=:project AND task_is_important=1;");
    query->bindValue(":project",project);
    debug();
    data="{ \"method\" : \"4\",\"tasks\":[";
    while(query->next()){
        data+="\""+ query->value(1).toString()+"\",";
        qDebug() <<query->value(0).toString()<<"-"<<query->value(1).toString()<<endl; // работает
    }
    data.remove(data.size()-2,2);
    data+="\"]}";

}

void project:: get_prior_tasks (QString project, int prior){
    query->prepare("SELECT task_id, task_name from task WHERE belong_to_project=:project AND task_priority=:prior;");
    query->bindValue(":project",project);
    query->bindValue(":prior",prior);
    debug();
    qDebug() << "found: " << endl;
    while(query->next()){
        qDebug() <<query->value("task_id").toString()<<"-"<<query->value("task_name").toString()<<endl; // работает
    }
}

base::base()
{
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("D:\\Project\\untitled2\\Agile.db");
    db.open();
    if(!db.isOpen()){
        qDebug() << "Wrong ";
    }else{
        qDebug() << "--------------------Ok";
    }
    query=new QSqlQuery(db);
}


QString  base::returndata()
{
    return data;
}


