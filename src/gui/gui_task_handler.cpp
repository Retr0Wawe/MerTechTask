#include "gui/gui_task_handler.hpp"

GuiTaskHandler::GuiTaskHandler(QStandardItemModel* model) noexcept: m_model(model)
{   }

auto GuiTaskHandler::insertTaskInModel(QStandardItemModel* t_model, QStringView t_name) noexcept -> void
{
    t_model->insertRow(g_rows_counter);
    m_rows.insert(t_name.toString(), g_rows_counter);

    // Set data from task to model
    t_model->setData(t_model->index(g_rows_counter, 0), t_name.toString());
    for (int j = 0, i = 1; i < def::ALL + 1; i++, j++) {
        t_model->setData(t_model->index(g_rows_counter, i), QString::fromStdString(m_tasks.at(t_name.toString().toStdString()).m_data[j]));
    } g_rows_counter++;

//    for (const auto& a : m_rows.toStdMap()) {
//        std::cout << a.first.toStdString() << " " << a.second << std::endl;
//    }
}

auto GuiTaskHandler::deleteTaskFromModel(QStandardItemModel* t_model, QStringView t_name) noexcept -> void
{
    const auto val = m_rows.find(t_name.toString());

    if (val != m_rows.end()) {
        t_model->takeRow(val.value()).removeFirst();
        m_rows.erase(val);
        g_rows_counter--;
    }
}

auto GuiTaskHandler::addTask(std::string_view t_data) -> std::string
{
    auto task_name = TaskHandler::addTask(t_data);

    if (!task_name.empty()) {
        insertTaskInModel(m_model, QString::fromStdString(task_name));
    }

    return task_name;
}

// Test data
// add task guys kekov entry
// add task2 mols hello sukably
// add task3 boys someworld sukably
// add task4 lower kysol mega
// add task5 graph kekov sukably

auto GuiTaskHandler::deleteTask(std::string_view t_data) noexcept -> bool
{
    if (t_data.empty()|| !TaskHandler::deleteTask(t_data)) {
        return false;
    }

    deleteTaskFromModel(m_model, QString::fromStdString(std::string(t_data)));
    return true;
}
