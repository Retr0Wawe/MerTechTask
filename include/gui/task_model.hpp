#ifndef QTASKMODEL_HPP
#define QTASKMODEL_HPP

#include "task_handler.hpp"

#include <QAbstractListModel>
#include <QSize>

class TaskModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TaskModel(QObject* parent = nullptr) noexcept;

    // Return the number of elements from TaskHandler
    //int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    // Return an element from TaskHandler
    //QVariant data(const QModelIndex& index, int role = Qt::DisplayRole);
    // Save new element value
    //bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::ImReadOnly) override;
    // Return editability options
    //Qt::ItemFlags flags(const QModelIndex& index) const override;
protected:
    task::TaskHandler m_handler;
};

#endif // QTASKMODEL_HPP
