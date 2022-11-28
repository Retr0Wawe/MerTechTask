#include "include/task_handler.hpp"

using namespace task;

int main() {
    // Тестовые входные данные

    TaskHandler handler;

    std::pair<std::string, block_of_task> test = {};

    test.first = "test_task1";

    // DESC, DATE, CATEGORY
    test.second.m_data[DESC] = "test_task";

    test.second.m_data[DATE] = "2023-12-12 20:20";

    test.second.m_data[CATEGORY] = "kekov";

    // -------------------------

    std::pair<std::string, block_of_task> test1 = {};

    test1.first = "test_task2";

    test1.second.m_data[DESC] = "test";

    test1.second.m_data[DATE] = "2022-11-12 00:29";

    test1.second.m_data[CATEGORY] = "kekov";
    // ------------------------
    std::pair<std::string, block_of_task> test2 = {};

    test2.first = "test_task3";

    test2.second.m_data[DESC] = "test23";

    test2.second.m_data[DATE] = "2022-12-11 10:20";

    test2.second.m_data[CATEGORY] = "lower";
    // ------------------------
    std::pair<std::string, block_of_task> test3 = {};

    test3.first = "test_task4";

    test3.second.m_data[DESC] = "test23";

    test3.second.m_data[DATE] = "2022-12-11 10:20";

    test3.second.m_data[CATEGORY] = "lower";
    // ------------------------
    std::pair<std::string, block_of_task> test4 = {};

    test4.first = "test_task5";

    test4.second.m_data[DESC] = "23954test";

    test4.second.m_data[DATE] = "1998-07-12 10:20";

    test4.second.m_data[CATEGORY] = "slower";

    handler.getStorage().insert(test);
    handler.getStorage().insert(test1);
    handler.getStorage().insert(test2);
    handler.getStorage().insert(test3);
    handler.getStorage().insert(test4);

    std::string string;

    do {
        std::cout << std::endl << ">> ";
        std::getline(std::cin, string);
    } while (handler.parseCommand(string) != eCode::STOP);

    // select * where date < \"2020-12-12-00:00\"
    // "select * where date < \"2020-12-12 00:00\" and category=\"lol\""
    // "select * where category like \"lol\""
    // select * where category="kekov"
}
