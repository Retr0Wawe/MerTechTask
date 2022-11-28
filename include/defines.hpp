#ifndef DEFINES_HPP_
#define DEFINES_HPP_

#include <array>
#include <iostream>
#include <sstream>
#include <tuple>

namespace task {
// Different codes for handle functions
enum class eCode : int { EMPTY, NOT_FOUND, NOT_VALID, STOP, UNRECOGNIZED_STRING, SUCCES };

// Enum of parms
enum eDataType : int { DESC, DATE, CATEGORY, ALL };

// Struct for parse date(example: "2020-12-12 00:00")

// Date input format: 2020-12-12-00:00 (need delimeter!)
// Date output format: 2020-12-12 00:00 (as in the original)
struct date {
    date() : m_year(0), m_month(0), m_day(0), m_hour(0), m_minute(0) {}

  public:
      friend std::ostream& operator<<(std::ostream& t_stream, const date& t_date);

    // Parse string and get values in date
      static auto getDateFromStr(const std::string& t_data)->date;

  public:
    unsigned int m_year;
    unsigned int m_month;
    unsigned int m_day;
    unsigned int m_hour;
    unsigned int m_minute;
};

// Struct of task
struct block_of_task {
  public:
    // Comparison operators that work with std::tuple recursively calling the overloaded operators for each type
    friend bool operator<(const block_of_task& t_task, const std::string& t_data) noexcept;

    friend bool operator>(const block_of_task& t_task, const std::string& t_data) noexcept;

    friend bool operator<=(const block_of_task& t_task, const std::string& t_data) noexcept;

    friend bool operator>=(const block_of_task& t_task, const std::string& t_data) noexcept;

    friend bool operator==(const block_of_task& t_task, const std::string& t_data) noexcept;

  public:
    std::array<std::string, eDataType::ALL> m_data;
    std::array<bool, eDataType::ALL> m_criteria = {0};
    std::array<bool, eDataType::ALL> m_sub_str = {0};
    bool m_is_done = 0;
};
} // namespace task

#endif // !DEFINES_HPP_
