#include "task.hpp"

#include <algorithm>
#include <sstream>
#include <deque>

namespace task {
    bool operator<(const block_of_task& t_task, const std::string& t_data)
    {
        //return t_task.data[DATE] < t_data;
        return true;
    }

    auto TaskHandler::addTask(const std::string& t_data) -> void
    {
        std::pair<std::string, block_of_task> block = {};
        
        // Check string for valid
        if (std::count_if(t_data.begin(), t_data.end(), [](char c) 
            { return c == ' '; }) > 3) {
            std::cout << "Command add: invalid string" << std::endl;
            return;
        }

        auto word = t_data.find_first_of(' ');
        block.first = t_data.substr(0, word);
        auto str = t_data.substr(word + 1);
        
        std::size_t prev = 0, next = 0, delta = 1;

        std::size_t i = 0;
        while (i < block.second.data.size() && 
        (next = str.find(' ', prev)) != std::string::npos) {
            block.second.data.at(i++) = str.substr(prev, next - prev);
            prev = next + delta;
        }

        block.second.data.at(i) = str.substr(prev);
        m_tasks.insert(block);
    }

    auto TaskHandler::doneTask(const std::string& t_data) noexcept -> void
    {
        auto it = m_tasks.find(t_data);

        if (it == m_tasks.end()) {
            std::cout << "Command done: task not found" << std::endl;
            return;
        }

        it->second.is_done = true;
    }

    auto TaskHandler::updateTask(const std::string& t_data) noexcept -> void
    {
        auto it = m_tasks.find(t_data);

        if (it == m_tasks.end()) {
            std::cout << "Command update: task not found" << std::endl;
            return;
        }

        for (auto& str : it->second.data) {
            std::getline(std::cin, str);
        }
    }

    auto TaskHandler::deleteTask(const std::string& t_data) noexcept -> void
    {
        auto it = m_tasks.find(t_data);

        if (it == m_tasks.end()) {
            std::cout << "Command delete: task not found" << std::endl;
            return;
        }

        m_tasks.erase(it);
    }

    auto TaskHandler::selectTask(const std::string& t_data) -> void
    {
        if (t_data == "*") {
            printTasks();
            return;
        }

        auto str = t_data.substr(t_data.find(' ') + 1);

        std::cout << "TEST STR " << str << "d" << std::endl;

        Lexer lex;
        for (Token it; (it = lex.getToken(str)) != Token::T_ERROR; ) {
            if (it == Token::T_WHERE) {
                if (lex.getToken(str) == Token::T_DATE) {
                    it = lex.getToken(str);
                    if (it == Token::T_MORE || it == Token::T_LESS
                       || it == Token::T_LESS_OR_EQ || it == Token::T_MORE_OR_EQ
                       || it == Token::T_EQUAL) {
                        lex.getToken(str);
                        std::string temp = lex.getData();
                        for (auto& task : m_tasks) {
                            bool res = handleDate(task.second, temp, it);

                            if (res) {
                                std::cout << "Done!" << std::endl;
                            }
                        }
                    }
                }
            } else {
                std::cout << "Command select: unrecognized string" << std::endl;
            }
        }
    }

    auto TaskHandler::parseCommand(const std::string& t_expr) -> const Code
    {
        if (t_expr.empty()) {
            return Code::EMPTY;
        }

        std::size_t pos = t_expr.find_first_of(' ');
        auto result = t_expr.substr(0, pos);

        if (result == "add") {
            addTask(t_expr.substr(pos + 1));
        } else if (result == "done") {
            doneTask(t_expr.substr(pos + 1));
        } else if (result == "update") {
            updateTask(t_expr.substr(pos + 1));
        } else if (result == "delete") {
            deleteTask(t_expr.substr(pos + 1));
        } else if (result == "select") {
            selectTask(t_expr.substr(pos + 1));
        } else if (t_expr == "print") {
            printTasks();
        } else if (t_expr == "stop") {
            return Code::STOP;
        } else {
            return Code::NOT_FOUND;
        }

        return Code::SUCCES;
    }

    auto TaskHandler::getStorage() noexcept -> storage&
    {
        return m_tasks;
    }

    auto TaskHandler::handleDate(const block_of_task& t_task, const std::string& t_data, const Token t_tok) -> bool
    {
        switch (t_tok) {
        case Token::T_MORE:

            break;

        case Token::T_LESS:
            return t_task < t_data;
            break;
        }

        return false;
    }

    auto TaskHandler::printTasks() const noexcept -> void
    {
        for (const auto& task : m_tasks) {
            std::cout << "Task: " << task.first << std::endl;
            if (!task.second.is_done) {
                std::cout << "Description: " << task.second.data[DataType::DESC] << std::endl;
                std::cout << "Date: " << task.second.data[DataType::DATE] << std::endl;
                std::cout << "Category: " << task.second.data[DataType::CATEGORY] << std::endl;
            } else {
                std::cout << "Task done" << std::endl << std::endl;
            }
            std::cout << std::endl;
        }
    }
}