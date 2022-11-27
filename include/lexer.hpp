#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <string>
#include <unordered_map>

// Small lexer for select
namespace task {
    enum class eToken : int {
        T_DESC, T_DATE, T_CATEGORY, T_QUOT,
        T_WHERE, T_AND, T_LIKE, T_ERROR, T_WORD, T_MORE, 
        T_LESS, T_LESS_OR_EQ, T_MORE_OR_EQ, T_EQUAL
    };

    inline std::unordered_map<std::string, eToken> g_tokens = {
        {"\"", eToken::T_QUOT},
        {"where", eToken::T_WHERE},
        {"and", eToken::T_AND},
        {"like", eToken::T_LIKE},
        {"date", eToken::T_DATE},
        {"category", eToken::T_CATEGORY},
        {"description", eToken::T_DESC},
        {">", eToken::T_MORE},
        {"<", eToken::T_LESS},
        {"<=", eToken::T_LESS_OR_EQ},
        {">=", eToken::T_MORE_OR_EQ},
        {"=", eToken::T_EQUAL}
    };
        
    struct Lexer {
        auto getToken(const std::string& t_str) -> const eToken;

        auto getData() const noexcept -> const std::string&;
    public:
        static inline std::size_t ptr = 0;
    private:
        std::string m_data;
    };
}

#endif // LEXER_HPP_