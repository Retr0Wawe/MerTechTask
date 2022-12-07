#ifndef TASK_HPP_
#define TASK_HPP_

#include <iostream>
#include <string>
#include <unordered_map>

#include "defines.hpp"
#include "lexer.hpp"

namespace task {

// Class for handler all tasks
class TaskHandler {
    using storage = std::unordered_map<std::string, block_of_task, string_hash, string_equal>;

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
    virtual auto addTask(std::string_view t_data) -> void;

    virtual auto doneTask(std::string_view t_data) noexcept -> void;

    virtual auto updateTask(std::string_view t_data) noexcept -> void;

    virtual auto deleteTask(std::string_view t_data) noexcept -> void;

    virtual auto selectTask(std::string_view t_data) -> void;

  protected:
    // Handle parse tokens
    virtual auto handleTokens(block_of_task& t_task, const eToken t_tok) noexcept -> bool;

    virtual auto handleDate(block_of_task& t_task) noexcept -> void;

    virtual auto handleParam(block_of_task& t_task, const eToken t_tok) noexcept -> void;

    virtual auto handleSubStr(block_of_task& t_task, const eToken t_tok) noexcept -> bool;

  public:
    // Print tasks
    virtual auto printTasks() const noexcept -> void;

    virtual auto printTask(std::string_view t_name, const block_of_task& t_task) const noexcept
        -> void;

    virtual auto printSort(Lexer& t_lex) noexcept -> void;

    virtual auto parseCommand(std::string_view t_expr) -> const eCode;
    // Get data
    auto getStorage() const noexcept -> const storage&;

  private:
    std::string m_str_format;
    storage m_tasks;
    Lexer m_lex;
};
} // namespace task

#endif // TASK_HPP_