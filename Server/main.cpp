#include <QCoreApplication>
#include "AgileServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    server_comp main_serv;
    main_serv.start(4242);


    return a.exec();
}

