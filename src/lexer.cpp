#include "lexer.hpp"

namespace task {
    auto Lexer::getToken(const std::string& t_str) -> const Token
    {
        std::string temp;
        temp.reserve(30);

        static std::size_t i = 0;
        for (; i < t_str.size(); i++) {
            if (std::isspace(t_str.at(i))) {
                continue;
            }

            if (auto it = g_tokens.find(temp); it != g_tokens.end()) {
                m_data = std::move(temp);
                return it->second;
            }
            
            if (t_str.at(i) != '\"') {
                temp.push_back(t_str.at(i));
            } else {
                m_data = temp;
            }
        }
        
        return Token::T_ERROR;
    }

    auto Lexer::getData() const noexcept -> const std::string&
    {
        return m_data;
    }
}