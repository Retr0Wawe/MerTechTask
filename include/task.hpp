#ifndef TASK_HPP_
#define TASK_HPP_

#include <unordered_map>
#include <iostream>
#include <string>
#include <array>

#include "lexer.hpp"

namespace task {
    enum class Code : int {
        EMPTY, NOT_FOUND, NOT_VALID, STOP,
        UNRECOGNIZED_STRING, SUCCES
    };

    enum DataType : int {
        DESC, DATE, CATEGORY, ALL
    };

    // Struct of task
    struct block_of_task {
        friend bool operator<(const block_of_task&, const std::string&);

        // friend bool operator<=(const std::string&, const std::string&) noexcept;

        // friend bool operator>=(const std::string&, const std::string&) noexcept;

        // friend bool operator>(const std::string&, const std::string&) noexcept;

        // friend bool operator==(const std::string&, const std::string&) noexcept;
    public:
        std::array<std::string, ALL> data;
        bool is_done;
    };

    // Class for handler all tasks
    class TaskHandler {  
        using storage = std::unordered_map<std::string, block_of_task>;
    public:
        TaskHandler() = default;

        TaskHandler(TaskHandler&&) = default;

        TaskHandler(const TaskHandler&) = default;

        virtual ~TaskHandler() = default;
    private:
        virtual auto addTask(const std::string& t_data) -> void;

        virtual auto doneTask(const std::string& t_data) noexcept -> void;

        virtual auto updateTask(const std::string& t_data) noexcept -> void;

        virtual auto deleteTask(const std::string& t_data) noexcept -> void;
        
        virtual auto selectTask(const std::string& t_data) -> void;
    public:
        auto printTasks() const noexcept -> void;

        auto parseCommand(const std::string& t_expr) -> const Code;

        // Потом поменять на const!
        auto getStorage() noexcept -> storage&;

        auto handleDate(const block_of_task& t_task, const std::string& t_data, const Token t_tok) -> bool;
    public:
        TaskHandler& operator=(const TaskHandler&) = default;

        TaskHandler& operator=(TaskHandler&&) = default;
    private:
        storage m_tasks;
    };
}

#endif // TASK_HPP_