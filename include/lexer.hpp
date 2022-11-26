#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <string>
#include <unordered_map>

// Small lexer for select
namespace task {
    enum class Token : int {
        T_QUOT, T_WHERE, T_AND, T_LIKE, T_DATE, T_ERROR, T_WORD,
        T_MORE, T_LESS, T_LESS_OR_EQ, T_MORE_OR_EQ, T_EQUAL
    };

    inline std::unordered_map<std::string, Token> g_tokens = {
        {"\"", Token::T_QUOT},
        {"where", Token::T_WHERE},
        {"and", Token::T_AND},
        {"like", Token::T_LIKE},
        {"date", Token::T_DATE},
        {">", Token::T_MORE},
        {"<", Token::T_LESS},
        {"<=", Token::T_LESS_OR_EQ},
        {">=", Token::T_MORE_OR_EQ},
        {"=", Token::T_EQUAL}
    };

    struct Lexer {
        auto getToken(const std::string& t_str) -> const Token;

        auto getData() const noexcept -> const std::string&;
    private:
        std::string m_data;
    };
}

#endif // LEXER_HPP_