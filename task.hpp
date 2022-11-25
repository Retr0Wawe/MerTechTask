#ifndef TASK_HPP_
#define TASK_HPP_

#include <unordered_map>
#include <iostream>
#include <string>
#include <array>

namespace task {
    enum class Code : int {
        EMPTY, NOT_FOUND, NOT_VALID, STOP,
        UNRECOGNIZED_STRING, SUCCES
    };

    class TaskHandler {  
        enum DataType : int {
            DESC, DATE, CATEGORY, ALL
        };

        struct task {
            std::array<std::string, ALL> data;
            bool is_done;
        };

        using storage = std::unordered_map<std::string, task>;
    public:
        TaskHandler() = default;

        virtual ~TaskHandler() = default;
    private:
        virtual auto addTask(const std::string& t_data) -> void;

        virtual auto doneTask(const std::string& t_data) noexcept -> void;

        virtual auto updateTask(const std::string& t_data) noexcept -> void;

        virtual auto deleteTask(const std::string& t_data) noexcept -> void;
        
        //virtual auto selectTask(std::function<>) noexcept -> void;
    public:
        auto printTasks() const noexcept -> void;

        auto validateCommand(const std::string& t_data) const -> bool;

        auto parseCommand(const std::string& t_expr) -> const Code;

        auto getStorage() const noexcept -> const storage&;
    private:
        storage m_tasks;
    };
}

#endif // TASK_HPP_