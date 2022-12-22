#ifdef GUI

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

#else

#include "task_handler.hpp"

#include <string>

int main() {
    TaskHandler handler;
    std::string string;
    // Entry point
    do {
        std::cout << std::endl << ">> ";
        std::getline(std::cin, string);
        std::cout << std::endl;
    } while (handler.parseCommand(string) != def::eCode::STOP);
}

#endif

/* TODO

1) Сделать разграничение на Gui и Console версию через
   define в Cmake(-DCONSOLE, по умолчанию Gui)

2) Поправить ошибки в deleteTaskInModel, подумать как сделать лучше

3) Попробовать реализовать сортировку строк(Gui)

*/
