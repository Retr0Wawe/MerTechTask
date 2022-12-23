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
