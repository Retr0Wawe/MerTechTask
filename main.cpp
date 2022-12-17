#include "gui/mainwindow.hpp"

#include <QStandardItemModel>
#include <QApplication>
#include <QString>

/* TODO

1) Сделать разграничение на Gui и Console версию через
   define в Cmake(-DCONSOLE, по умолчанию Gui)

2) Поправить ошибки в deleteTaskInModel, подумать как сделать лучше

3) Попробовать реализовать сортировку строк(Gui)

*/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    window.show();
    return a.exec();
}
