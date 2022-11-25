#include "task.hpp"

#include <algorithm>

namespace task {
    auto TaskHandler::addTask(const std::string& t_data) -> void
    {
        std::pair<std::string, task> block = {};
        
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

    auto TaskHandler::validateCommand(const std::string& t_data) const -> bool
    {
        return std::count_if(t_data.begin(), t_data.end(), [](char c) {
            return c == ' ';
        }) <= 4 ? true : false;
    }

    auto TaskHandler::parseCommand(const std::string& t_expr) -> const Code
    {
        if (t_expr.empty()) {
            return Code::EMPTY;
        }

        std::size_t pos = t_expr.find_first_of(' ');
        auto result = t_expr.substr(0, pos);

        if (!validateCommand(t_expr)) {
            return Code::UNRECOGNIZED_STRING;
        }

        if (result == "add") {
            addTask(t_expr.substr(pos + 1));
        } else if (result == "done") {
            doneTask(t_expr.substr(pos + 1));
        } else if (result == "update") {
            updateTask(t_expr.substr(pos + 1));
        } else if (result == "delete") {
            //deleteTask(t_expr.substr(pos + 1));
        } else if (result == "select") {
            //selectTask()
        } else if (t_expr == "print") {
            printTasks();
        } else if (t_expr == "stop") {
            return Code::STOP;
        } else {
            return Code::NOT_FOUND;
        }

        return Code::SUCCES;
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