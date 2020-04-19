#include <QCoreApplication>
#include "AgileServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
AServer my;
my.startServer();
    return a.exec();
}
