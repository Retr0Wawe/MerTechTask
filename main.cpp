#include "gui/mainwindow.hpp"

#include <QStandardItemModel>
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    window.show();
    return a.exec();
}
