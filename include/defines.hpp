#ifndef DEFINES_HPP_
#define DEFINES_HPP_

#include <array>

namespace task {
// Different codes for handle functions
enum class eCode : int { EMPTY, NOT_FOUND, NOT_VALID, STOP, UNRECOGNIZED_STRING, SUCCES };

// Enum of parms
enum eDataType : int { DESC, DATE, CATEGORY, ALL };

// Struct of task
struct block_of_task {
  public:
    friend bool operator<(const block_of_task& t_task, const std::string& t_data) noexcept {
        return t_task.m_data[DATE] < t_data;
    }

    friend bool operator>(const block_of_task& t_task, const std::string& t_data) noexcept {
        return t_task.m_data[DATE] > t_data;
    }

    friend bool operator<=(const block_of_task& t_task, const std::string& t_data) noexcept {}

    friend bool operator>=(const block_of_task& t_task, const std::string& t_data) noexcept {}

    friend bool operator==(const block_of_task& t_task, const std::string& t_data) noexcept {}

  public:
    std::array<std::string, eDataType::ALL> m_data;
    std::array<bool, eDataType::ALL> m_criteria = {0};
    std::array<bool, eDataType::ALL> m_sub_str = {0};
    bool m_is_done = 0;
};
} // namespace task

#endif // !DEFINES_HPP_
