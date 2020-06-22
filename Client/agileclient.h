#ifndef AGILECLIENT_H
#define AGILECLIENT_H

#include "Header.h"

struct _task{
  int id;
  QString name;
  int done;
  int importance;
  int prior;
  QString comment;
};

struct _project{
    int id;
    QString name;
    QMap <int, QString> task;// Хранятся id-name
    QList <QString> names;
    QList <QString> important;// Хранятся список важных задач
    QList <QString> done0;
    QList <QString> done1;
    QList <QString> done2;
    // Хранятся список задач по приоритетам
    QList <QString> pr0;
    QList <QString> pr1;
    QList <QString> pr2;
    QList <QString> pr3;
    QList <QString> pr4;
};

struct _user{
    int id;
    QString name;
    QString pass;
    QMap <int, QString> proj;// Хранятся id-name
    QList <QString> names;// хранит только список имен
};


class client : public QObject
{
    Q_OBJECT
public:
    explicit client(QHostAddress ip, qint32 port, QObject *parent = nullptr);

    _user currentUser;
    _project currentProject;
    _task currentTask;

signals:
    void updatelist();
    void updateTaskview();
    void disconnected();
public slots:
    void start();
    void write(QString data);

private slots:
    void read();
    void connected();
    void disconnect();

private:
    QTcpSocket* socket;
    QHostAddress _ip;
    qint32 _port;
};

#endif // AGILECLIENT_H
/*


  */
