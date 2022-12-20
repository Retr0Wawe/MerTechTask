#ifndef GUI_TASK_HANDLER_H
#define GUI_TASK_HANDLER_H

#include <QStandardItemModel>
#include <QMap>

#include "task_handler.hpp"

class GuiTaskHandler : public TaskHandler
{
    using rows_storage = QMap<QString, int>;
public:
    GuiTaskHandler(QStandardItemModel* t_model) noexcept;

private:
    auto insertTaskInModel(QStandardItemModel* t_model, QStringView t_name) noexcept -> void;

    auto deleteTaskFromModel(QStandardItemModel* t_model, QStringView t_name) noexcept ->void;
public:
    virtual auto addTask(std::string_view t_data) -> std::string override;

    virtual auto deleteTask(std::string_view t_data) noexcept -> bool override;

protected:
    QStandardItemModel* m_model;
    rows_storage m_rows;
public:
    int g_rows_counter = 0;
};

#endif //!GUI_TASK_HANDLER_H
