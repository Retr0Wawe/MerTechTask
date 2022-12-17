#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <string>
#include <unordered_map>
#include <string_view>

#include "defines.hpp"

// Small lexer for select
enum class eToken : int {
    T_DESC,
    T_DATE,
    T_CATEGORY,
    T_QUOT,
    T_WHERE,
    T_AND,
    T_LIKE,
    T_ERROR,
    T_WORD,
    T_MORE,
    T_LESS,
    T_LESS_OR_EQ,
    T_MORE_OR_EQ,
    T_EQUAL
};

// Map for storage tokens
inline const std::unordered_map<std::string, eToken> g_tokens = {
    {"\"", eToken::T_QUOT},          {"where", eToken::T_WHERE},   {"and", eToken::T_AND},
    {"like", eToken::T_LIKE},        {"date", eToken::T_DATE},     {"category", eToken::T_CATEGORY},
    {"description", eToken::T_DESC}, {">", eToken::T_MORE},        {"<", eToken::T_LESS},
    {"<=", eToken::T_LESS_OR_EQ},    {">=", eToken::T_MORE_OR_EQ}, {"=", eToken::T_EQUAL}};

// Struct for storage bools
struct boolStorage {
    // An array for storage result from find sub string
    std::array<bool, def::ALL> m_sub_str;
    // An array to store matching criteria and parameters
    std::array<bool, def::ALL> m_criteria;
};

// Struct of lexer 
struct Lexer {
    auto setBoolIfFind(const eToken t_tok) noexcept -> void;

    auto getToken(std::string_view t_str) -> const eToken;

    auto getData() const noexcept -> const std::string&;
    // Get last token
    auto getLastToken() const noexcept -> const eToken;

  public:
    // Pointer to current symbol
    static inline std::size_t ptr = 0;

  private:
    // First array for set Tokens, second for set if substr find
    boolStorage m_all_bool;
    std::string m_data;
    eToken m_tok = {};

  public:
    auto getBools() noexcept -> boolStorage&;
};

#endif // LEXER_HPP_
