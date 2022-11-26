#include "task.hpp"

#include <algorithm>
#include <sstream>
#include <deque>

namespace task {
    bool operator<(const block_of_task& t_task, const std::string& t_data) noexcept
    {
        return t_task.m_data[DATE] < t_data;
    }

    bool operator>(const block_of_task& t_task, const std::string& t_data) noexcept
    {
        return t_task.m_data[DATE] > t_data;
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
        while (i < block.second.m_data.size() && 
        (next = str.find(' ', prev)) != std::string::npos) {
            block.second.m_data.at(i++) = str.substr(prev, next - prev);
            prev = next + delta;
        }

        block.second.m_data.at(i) = str.substr(prev);
        m_tasks.insert(block);
    }

    auto TaskHandler::doneTask(const std::string& t_data) noexcept -> void
    {
        auto it = m_tasks.find(t_data);

        if (it == m_tasks.end()) {
            std::cout << "Command done: task not found" << std::endl;
            return;
        }

        it->second.m_is_done = true;
    }

    auto TaskHandler::updateTask(const std::string& t_data) noexcept -> void
    {
        auto it = m_tasks.find(t_data);

        if (it == m_tasks.end()) {
            std::cout << "Command update: task not found" << std::endl;
            return;
        }

        for (auto& str : it->second.m_data) {
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

        m_str_format = t_data.substr(t_data.find(' ') + 1);

        for (eToken it; (it = m_lex.getToken(m_str_format)) != eToken::T_ERROR; ) {
            if (it == eToken::T_WHERE) {
                if (m_lex.getToken(m_str_format) == eToken::T_DATE) {
                    it = m_lex.getToken(m_str_format);
                    if (it == eToken::T_MORE || it == eToken::T_LESS
                       || it == eToken::T_LESS_OR_EQ || it == eToken::T_MORE_OR_EQ
                       || it == eToken::T_EQUAL) {
                        m_lex.getToken(m_str_format); auto temp = m_lex.getData();
                        
                        for (auto& task : m_tasks) {
                            handleDate(task.second, temp, it);
                        }

                        if (m_lex.getToken(m_str_format) == eToken::T_AND) {
                            it = m_lex.getToken(m_str_format); temp = m_lex.getData();
                            for (auto& task : m_tasks) {
                                if (!handleTokens(task.second, it)) {
                                   break;
                                }
                            }
                        }
                    }
                }
            } else {
                std::cout << "Command select: unrecognized string" << std::endl;
            }
        }
        m_lex.ptr = 0;
    }

    auto TaskHandler::parseCommand(const std::string& t_expr) -> const eCode
    {
        if (t_expr.empty()) {
            return eCode::EMPTY;
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
            return eCode::STOP;
        } else {
            return eCode::NOT_FOUND;
        }

        return eCode::SUCCES;
    }

    auto TaskHandler::getStorage() noexcept -> storage&
    {
        return m_tasks;
    }

    auto TaskHandler::handleDate(block_of_task& t_task, const std::string& t_data, const eToken t_tok) noexcept -> void
    {
        switch (t_tok) {
        case eToken::T_MORE:
            t_task.m_criteria[DATE] = t_task > t_data;
            break;

        case eToken::T_LESS:
            t_task.m_criteria[DATE] = t_task < t_data;
            break;
        }
    }

    auto TaskHandler::handleTokens(block_of_task& t_task, const eToken t_tok) -> bool
    {
        return true;
    }

    auto TaskHandler::printTasks() const noexcept -> void
    {
        std::cout << std::endl;
        for (const auto& task : m_tasks) {
            std::cout << "Task: " << task.first << std::endl;
            if (!task.second.m_is_done) {
                std::cout << "Description: " << task.second.m_data[eDataType::DESC] << std::endl;
                std::cout << "Date: " << task.second.m_data[eDataType::DATE] << std::endl;
                std::cout << "Category: " << task.second.m_data[eDataType::CATEGORY] << std::endl;
            } else {
                std::cout << "Task done" << std::endl << std::endl;
            }
            std::cout << std::endl;
        }
    }
}