#include <QApplication>
#include <QDebug>
#include "dwarf.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Dwarf *d = new Dwarf(QString("/tmp"), QString("/tmp"), QString("SGC_0001.NEF"), 0);
    d->start();
    return app.exec();
}
