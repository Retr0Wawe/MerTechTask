#include "task_handler.hpp"

#include <algorithm>

namespace task {
auto TaskHandler::addTask(const std::string& t_data) -> void {
    std::pair<std::string, block_of_task> block = {};

    // Check string for valid
    auto c = std::count_if(t_data.begin(), t_data.end(), [](char c) { return c == ' '; });

    if (c > 3 || c <= 1) {
        std::cout << "Command add: invalid string" << std::endl << std::endl;
        return;
    }

    auto word = t_data.find_first_of(' ');
    block.first = t_data.substr(0, word);
    auto str = t_data.substr(word + 1);

    std::size_t prev = 0, next = 0, delta = 1;

    std::size_t i = 0; // Split strings by spaces
    while (i < block.second.m_data.size() && (next = str.find(' ', prev)) != std::string::npos) {
        block.second.m_data.at(i++) = str.substr(prev, next - prev);
        prev = next + delta;
    }

    block.second.m_data.at(i) = str.substr(prev);
    m_tasks.insert(block);
}

auto TaskHandler::doneTask(const std::string& t_data) noexcept -> void {
    auto it = m_tasks.find(t_data);

    if (it == m_tasks.end()) {
        std::cout << "Command done: task not found" << std::endl << std::endl;
        return;
    }

    it->second.m_is_done = true;
}

auto TaskHandler::updateTask(const std::string& t_data) noexcept -> void {
    auto it = m_tasks.find(t_data);

    if (it == m_tasks.end()) {
        std::cout << "Command update: task not found" << std::endl << std::endl;
        return;
    }

    std::cout << "Enter your data: " << std::endl;
    for (auto& str : it->second.m_data) {
        std::getline(std::cin, str);
    }
}

auto TaskHandler::deleteTask(const std::string& t_data) noexcept -> void {
    auto it = m_tasks.find(t_data);

    if (it == m_tasks.end()) {
        std::cout << "Command delete: task not found" << std::endl << std::endl;
        return;
    }

    m_tasks.erase(it);
}

auto TaskHandler::selectTask(const std::string& t_data) -> void {
    if (t_data == "*") {
        printTasks();
        return;
    }

    m_str_format = t_data.substr(t_data.find(' ') + 1);
    auto tok = m_lex.getToken(m_str_format);

    if (tok == eToken::T_WHERE) {
        while ((tok = m_lex.getToken(m_str_format)) != eToken::T_ERROR) {
            auto pos = m_lex.ptr; // Save position for parse each token
            for (auto& task : m_tasks) {
                if (!handleTokens(task.second, tok)) {
                    break;
                }
                m_lex.ptr = pos;
            }
            m_lex.getToken(m_str_format);
        }
    } else {
        std::cout << "Command select: unrecognized expression" << std::endl << std::endl;
        m_lex.ptr = 0;
        return;
    }

    printSort(m_lex);

    // Null value for parse other string
    m_lex.ptr = 0;
}

auto TaskHandler::handleTokens(block_of_task& t_task, const eToken t_tok) noexcept -> bool {
    eToken new_tok;

    switch (t_tok) {
    case eToken::T_DATE:
        handleDate(t_task);
        break;
    case eToken::T_CATEGORY:
    case eToken::T_DESC:
        handleParam(t_task, t_tok);
        break;
    case eToken::T_AND:
        new_tok = m_lex.getToken(m_str_format);
        if (new_tok == eToken::T_DATE) {
            handleDate(t_task);
        } else {
            handleParam(t_task, new_tok);
        }
        break;
    default:
        return false;
    }

    return true;
}

auto TaskHandler::handleDate(block_of_task& t_task) noexcept -> void {
    auto new_tok = m_lex.getToken(m_str_format);
    m_lex.getToken(m_str_format);
    auto data = m_lex.getData();

    switch (new_tok) {
    case eToken::T_MORE:
        t_task.m_criteria[DATE] = t_task > data;
        break;

    case eToken::T_LESS:
        t_task.m_criteria[DATE] = t_task < data;
        break;

    case eToken::T_MORE_OR_EQ:
        t_task.m_criteria[DATE] = t_task <= data;
        break;

    case eToken::T_LESS_OR_EQ:
        t_task.m_criteria[DATE] = t_task >= data;
        break;

    case eToken::T_EQUAL:
        t_task.m_criteria[DATE] = t_task == data;
    }
}

auto TaskHandler::handleParam(block_of_task& t_task, const eToken t_tok) noexcept -> void {
    auto tok = m_lex.getToken(m_str_format);

    if (tok != eToken::T_EQUAL && tok != eToken::T_LIKE) {
        return;
    }

    if (tok == eToken::T_LIKE) {
        if (handleSubStr(t_task, t_tok)) {
            return;
        }
    }

    auto old_tok = static_cast<eDataType>(t_tok);

    tok = m_lex.getToken(m_str_format);

    if (tok != eToken::T_WORD) {
        std::cout << "Command select: invalid string in param" << std::endl << std::endl;
        return;
    }

    auto temp = m_lex.getData();

    switch (t_tok) {
    case eToken::T_CATEGORY:
    case eToken::T_DESC:
        if (t_task.m_data[old_tok] == temp) {
            t_task.m_criteria[old_tok] = 1;
        }
        break;
    }
}

auto TaskHandler::handleSubStr(block_of_task& t_task, const eToken t_tok) noexcept -> bool {
    auto new_tok = static_cast<eDataType>(t_tok);

    if (m_lex.getToken(m_str_format) != eToken::T_WORD) {
        return false;
    }

    auto temp = m_lex.getData();

    switch (t_tok) {
    case eToken::T_CATEGORY:
    case eToken::T_DESC:
        if (t_task.m_data[new_tok].find(temp) != std::string::npos) {
            t_task.m_sub_str[new_tok] = 1; // Set all flags if find substr in token
            t_task.m_criteria[new_tok] = 1;
            m_lex.getBools().second[new_tok] = 1;
        }
        break;
    }
    return true;
}

auto TaskHandler::parseCommand(const std::string& t_expr) -> const eCode {
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

auto TaskHandler::getStorage() const noexcept -> const storage& { return m_tasks; }

auto TaskHandler::printTasks() const noexcept -> void {
    for (const auto& task : m_tasks) {
        printTask(task.first, task.second);
    }
}

auto TaskHandler::printTask(const std::string& t_name, const block_of_task& t_task) const noexcept
    -> void {
    std::cout << std::endl;
    std::cout << "Task: " << t_name << std::endl;
    if (!t_task.m_is_done) {
        std::cout << "Description: " << t_task.m_data[eDataType::DESC] << std::endl;
        std::cout << "Date: " << t_task.m_data[eDataType::DATE] << std::endl;
        std::cout << "Category: " << t_task.m_data[eDataType::CATEGORY] << std::endl;
    } else {
        std::cout << "Task done" << std::endl << std::endl;
    }
    std::cout << std::endl;
}

// Counts the number of true values ​​and compares with the number of installed tokens
auto TaskHandler::printSort(Lexer& t_lex) noexcept -> void {
    auto& bools_cr = t_lex.getBools().first;
    auto& bools_sub_str = t_lex.getBools().second;

    auto b_cr_count = std::count(bools_cr.begin(), bools_cr.end(), true);
    auto b_sub_str_count = std::count(bools_sub_str.begin(), bools_sub_str.end(), true);

    for (auto& task : m_tasks) {
        auto& cr = task.second.m_criteria;
        auto& sub_str = task.second.m_sub_str;

        auto cr_count = std::count(cr.begin(), cr.end(), 1);
        auto sub_str_count = std::count(sub_str.begin(), sub_str.end(), 1);

        if (b_cr_count == cr_count && b_sub_str_count == sub_str_count) {
            printTask(task.first, task.second);
        }

        cr = {0};
        sub_str = {0};
    }

    bools_cr = {0};
    bools_sub_str = {0};
}

} // namespace task