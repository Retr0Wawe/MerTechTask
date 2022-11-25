#include "task.hpp"

using namespace task;

int main()
{
    TaskHandler handler;

    try {
        std::string string;
        do {
            std::getline(std::cin, string);
        } while (handler.parseCommand(string) != Code::STOP);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
    }
}