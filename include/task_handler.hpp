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
    using storage = std::unordered_map<std::string, block_of_task>;

  public:
    TaskHandler() = default;

    TaskHandler(TaskHandler&&) = default;

    TaskHandler(const TaskHandler&) = default;

    virtual ~TaskHandler() = default;

  public:
    TaskHandler& operator=(const TaskHandler&) = default;

    TaskHandler& operator=(TaskHandler&&) = default;

  protected:
    virtual auto addTask(const std::string& t_data) -> void;

    virtual auto doneTask(const std::string& t_data) noexcept -> void;

    virtual auto updateTask(const std::string& t_data) noexcept -> void;

    virtual auto deleteTask(const std::string& t_data) noexcept -> void;

    virtual auto selectTask(const std::string& t_data) -> void;

    virtual auto handleTokens(block_of_task& t_task, const eToken t_tok) noexcept -> bool;

    virtual auto handleDate(block_of_task& t_task) noexcept -> void;

    virtual auto handleParam(block_of_task& t_task, const eToken t_tok) noexcept -> void;

    virtual auto handleSubStr(block_of_task& t_task, const eToken t_tok) noexcept -> bool;

  public:
    virtual auto printTasks() const noexcept -> void;

    virtual auto printSort() const noexcept -> void;

    virtual auto parseCommand(const std::string& t_expr) -> const eCode;
    // Потом поменять на const!
    auto getStorage() noexcept -> storage&;

  private:
    std::string m_str_format;
    storage m_tasks;
    Lexer m_lex;
};
} // namespace task

#endif // TASK_HPP_