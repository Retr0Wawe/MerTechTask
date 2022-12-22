#ifndef TASK_HPP_
#define TASK_HPP_

#include <iostream>
#include <string>
#include <unordered_map>

#include "defines.hpp"
#include "lexer.hpp"

/* INSTRUCTIONS:
    1) add task_name description date(like: 2020-12-12-00:00) category - adds a task
    2) done task_name - marks the task as finished
    3) update task_name (and you shuold be enter your new date) - updates the task with your data
    4) delete task_name - removes a task from the list
    5) select * where {predicate} - provides output filtering by given parameters and keywords
*/

// Class for handle tasks
class TaskHandler {
    using storage =
        std::unordered_map<std::string, def::block_of_task, def::string_hash, def::string_equal>;
    using block_task = def::block_of_task;

  public:
    TaskHandler() = default;

    TaskHandler(TaskHandler&&) = default;

    TaskHandler(const TaskHandler&) = default;

    virtual ~TaskHandler() = default;

  public:
    TaskHandler& operator=(const TaskHandler&) = default;

    TaskHandler& operator=(TaskHandler&&) = default;

  public:
    // Functions for work with tasks
    virtual auto addTask(std::string_view t_data) -> std::string;

    virtual auto doneTask(std::string_view t_data) noexcept -> void;

    virtual auto updateTask(std::string_view t_data) noexcept -> void;

    virtual auto deleteTask(std::string_view t_data) noexcept -> bool;

    virtual auto selectTask(std::string_view t_data) -> void;

  protected:
    // Handle parse tokens
    virtual auto handleTokens(block_task& t_task, const eToken t_tok) noexcept -> bool;

    virtual auto handleDate(block_task& t_task) noexcept -> void;

    virtual auto handleParam(block_task& t_task, const eToken t_tok) noexcept -> void;

    virtual auto handleSubStr(block_task& t_task, const eToken t_tok) noexcept -> bool;

  public:
    // Print tasks
    virtual auto printTasks() const noexcept -> void;

    virtual auto printTask(std::string_view t_name, const block_task& t_task) const noexcept
        -> void;

    virtual auto printSort(Lexer& t_lex) noexcept -> void;

    virtual auto parseCommand(std::string_view t_expr) -> const def::eCode;
    // Get data
    auto getStorage() const noexcept -> const storage&;

  protected:
    std::string m_str_format;
    storage m_tasks;
    Lexer m_lex;
};

#endif // TASK_HPP_
