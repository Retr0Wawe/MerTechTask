#include "include/task_handler.hpp"

using namespace task;

/* INSTRUCTIONS:
    1) add task_name description date(like: 2020-12-12-00:00) category - adds a task
    
    2) done task_name - marks the task as finished

    3) update task_name (and you shuold be enter your new date) - updates the task with your data

    4) delete task_name - removes a task from the list
*/

int main() {
    TaskHandler handler, handler2;
    std::string string;
    // Entry point
    do {
        std::cout << std::endl << ">> ";
        std::getline(std::cin, string);
        std::cout << std::endl;
    } while (handler.parseCommand(string) != eCode::STOP);
}
