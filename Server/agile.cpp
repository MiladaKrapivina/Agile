#include "agile.h"

void user::  create_user(QString name,QString email,QString password)
{
    query->prepare("INSERT INTO user ( user_name, user_project, user_email, user_password) "
                   "VALUES ( :user_name, :user_project, :user_email, :user_password);");
    query->bindValue(":user_name",name);
    query->bindValue(":user_project","NULL");
    query->bindValue(":user_email",email);
    query->bindValue(":user_password",password);

    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }

}

void project::  create_project(QString name,QString owner,QString tasks)
{

    query->prepare("INSERT INTO project ( project_name, project_owner, project_tasks) "
                   "VALUES ( :project_name, :project_owner, :project_tasks);");
    query->bindValue(":project_name",name);
    query->bindValue(":project_owner",owner);
    query->bindValue(":project_tasks",tasks);

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

    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
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


    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
}

void user::get_all_project(QString user)
{
    query->prepare("SELECT project_id, project_name from project WHERE project_owner =:user;");
    query->bindValue(":user",user);

    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
    qDebug() << "found: " << endl;

    while(query->next()){
        qDebug() <<query->value(0).toString()<<"-"<<query->value(1).toString()<<endl; // работает
    }
}

void project::delete_project(QString name)
{
    query->exec("DELETE FROM project WHERE project_name=\""+name+"\";");
    query->exec("DELETE FROM task WHERE belong_to_project=\""+name+"\";");
    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }

}

void task::delete_task(QString name)
{
    query->exec("DELETE FROM task WHERE task_name=\""+name+"\";");

    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }

}

void task::set_done(QString taskname)
{
    query->exec("UPDATE task SET  task_is_done=\"1\" WHERE task_name=\""+taskname+"\";");

    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
}

void task::set_important(QString taskname)
{
    query->exec("UPDATE task SET  task_is_important=\"1\" WHERE task_name=\""+taskname+"\";");

    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
}

void task:: set_date(QString taskname, QString date)
{
    query->exec("UPDATE task SET  task_create_time=\""+date+"\" WHERE task_name=\""+taskname+"\";");

    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
}

void user:: change_user_password(QString name, QString newpassword)
{
    query->exec("UPDATE user SET  user_password=\""+newpassword+"\" WHERE user_name=\""+name+"\";");

    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
}

void task:: set_priority(QString taskname, QString pr)
{
    query->exec("UPDATE task SET  task_priority=\""+pr+"\" WHERE task_name=\""+taskname+"\";");

    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
}

void task:: set_deadline(QString taskname, QString date)
{
    query->exec("UPDATE task SET  task_deadline=\""+date+"\" WHERE task_name=\""+taskname+"\";");

    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
}

void project:: get_all_tasks (QString project ){

    query->prepare("SELECT task_id, task_name from task WHERE belong_to_project=:project;");
    query->bindValue(":project",project);

    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
    qDebug() << "found: " << endl;

    while(query->next()){

        qDebug() <<query->value("task_id").toString()<<"-"<<query->value("task_name").toString()<<endl; // работает

    }
}

void project:: get_done_tasks (QString project,int done ){
    query->prepare("SELECT task_id, task_name from task WHERE belong_to_project=:project AND task_is_done=:done;");
    query->bindValue(":project",project);
    query->bindValue(":done",done);

    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
    qDebug() << "found: " << endl;

    while(query->next()){

        qDebug() <<query->value("task_id").toString()<<"-"<<query->value("task_name").toString()<<endl; // работает
    }
}
void project:: get_imp_tasks (QString project){
    query->prepare("SELECT task_id, task_name from task WHERE belong_to_project=:project AND task_is_important=1;");
    query->bindValue(":project",project);

    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
    qDebug() << "found: " << endl;

    while(query->next()){

        qDebug() <<query->value("task_id").toString()<<"-"<<query->value("task_name").toString()<<endl; // работает
    }
}

void project:: get_prior_tasks (QString project, int prior){
    query->prepare("SELECT task_id, task_name from task WHERE belong_to_project=:project AND task_priority=:prior;");
    query->bindValue(":project",project);
    query->bindValue(":prior",prior);

    if(query->exec()){
        qDebug() << "insert ok";
    }else{
        qDebug() << "insert failed";
    }
    qDebug() << "found: " << endl;

    while(query->next()){

        qDebug() <<query->value("task_id").toString()<<"-"<<query->value("task_name").toString()<<endl; // работает
    }

}
