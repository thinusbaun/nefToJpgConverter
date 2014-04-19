#include <QApplication>
#include <QDebug>
#include "mainWindow.hpp"
#include "dwarf.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *window = new MainWindow();
    window->show();
    return app.exec();
}
