#include "include/task_handler.hpp"

using namespace task;

int main() {
    TaskHandler handler;

    std::pair<std::string, block_of_task> test = {};

    test.first = "test_task1";

    // DESC, DATE, CATEGORY
    test.second.m_data[DESC] = "test_task";

    test.second.m_data[DATE] = "2020-12-12 00:20";

    test.second.m_data[CATEGORY] = "kekov";

    std::pair<std::string, block_of_task> test1 = {};

    // -------------------------

    test1.first = "test_task2";

    test1.second.m_data[DESC] = "test_task2";

    test1.second.m_data[DATE] = "2022-12-12 00:20";

    test1.second.m_data[CATEGORY] = "lol";

    handler.getStorage().insert(test);
    handler.getStorage().insert(test1);

    try {
        std::string string;

        do {
            //std::getline(std::cin, string);
        } while (
            handler.parseCommand("select * where category like \"lol\"") !=
            eCode::STOP);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
    }
    // select * where date < \"2020-12-12-00:00\"
    // "select * where date < \"2020-12-12 00:00\" and category=\"lol\""
    // "select * where category like \"lol\""
}
