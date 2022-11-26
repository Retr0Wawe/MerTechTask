#include "include/task.hpp"

using namespace task;

int main()
{
    TaskHandler handler;

    std::pair<std::string, block_of_task> test = {};

    test.first = "test_task1";

    // DESC, DATE, CATEGORY
    test.second.data[DESC] = "test_task";

    test.second.data[DATE] = "2020-12-12-00:20";

    test.second.data[CATEGORY] = "test_category";

    handler.getStorage().insert(test);

    try {
        std::string string;

        do {
            std::getline(std::cin, string);
        } while (handler.parseCommand(string) != Code::STOP);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
    }
    // select * where date < \"2020-12-12-00:00\"
}
