#include "gui/mainwindow.hpp"
#include "defines.hpp"
#include "task_handler.hpp"

#include <QStandardItemModel>
#include <QApplication>
#include <QString>

/* TODO

1) Переделать все std::string_view под QString
2) Переделать std::unordered_map под QMap
3) Попробовать реализовать собственный механизм сортировки строк
*/

void addTask(QAbstractItemModel *model, const QString& name,
             const QString& desc, const QString& date, const QString& category)
{
    model->insertRow(0);
    model->setData(model->index(0, 0), name);
    model->setData(model->index(0, 1), desc);
    model->setData(model->index(0, 2), date);
    model->setData(model->index(0, 3), category);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    window.show();
    return a.exec();
}
