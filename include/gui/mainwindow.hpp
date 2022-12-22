#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

#include "gui/gui_task_handler.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
class QStandardItemModel;
class QTreeView;

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    MainWindow(QWidget* parent = nullptr);

    virtual ~MainWindow();

  public:
    QStandardItemModel* getModel() const noexcept;

  private slots:
    void on_AddTaskButton_clicked();

    void on_RegularLineEdit_editingFinished();

  protected:
    void createTaskModel(QObject* parent, const QVector<QString>& headers) noexcept;

  private:
    Ui::MainWindow* ui;
    QStandardItemModel* model;
    QTreeView* sourceView;
    std::unique_ptr<TaskHandler> m_handler;
};

#endif // MAINWINDOW_H
