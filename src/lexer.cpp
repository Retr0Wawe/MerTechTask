#include "lexer.hpp"

namespace task {
auto Lexer::getToken(const std::string& t_str) -> const eToken {
    std::string temp;

    temp.reserve(25);
    for (; ptr < t_str.size(); ptr++) {
        if (std::isspace(t_str.at(ptr))) {
            continue;
        }

        if (auto it = g_tokens.find(temp); it != g_tokens.end()) {
            setBoolIfFind(it->second);
            return (m_tok = it->second);
        }

        if (t_str.at(ptr) == '\"') {
            m_data.clear();
            char ch = 0;
            while ((ch = t_str.at(++ptr)) != '\"') {
                temp.push_back(t_str.at(ptr));
            }
            ptr++;
            m_data = std::move(temp);
            return eToken::T_WORD;
        } else {
            temp.push_back(t_str.at(ptr));
        }
    }
    return eToken::T_ERROR;
}

auto Lexer::setBoolIfFind(const eToken t_tok) noexcept -> void {
    auto new_tok = static_cast<eDataType>(getLastToken());
    switch (t_tok) {
    case eToken::T_DESC:
    case eToken::T_DATE:
    case eToken::T_CATEGORY:
        all_bool.first[static_cast<eDataType>(t_tok)] = 1;
        break;
    }
}

auto Lexer::getData() const noexcept -> const std::string& { return m_data; }

auto Lexer::getLastToken() const noexcept -> const eToken { return m_tok; }

auto Lexer::getBools() noexcept -> std::pair<array<bool>, array<bool>>& { return all_bool; }
} // namespace task