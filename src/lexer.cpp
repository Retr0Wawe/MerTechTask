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
            if (!all_bool.first[(int)it->second]) {
                all_bool.first[(int)it->second] = 1;
            }
            return it->second;
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

auto Lexer::getData() const noexcept -> const std::string& { return m_data; }

auto Lexer::getBools() noexcept -> decltype(all_bool)& { return all_bool; }
} // namespace task