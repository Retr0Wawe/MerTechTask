#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QSortFilterProxyModel;
class QStandardItemModel;
class QTreeView;
class QString;
QT_END_NAMESPACE

namespace task {class QTaskHandler; };

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

    virtual ~MainWindow();
public:
    QStandardItemModel* getModel() const noexcept;
private slots:
    void on_AddTaskButton_clicked();

    void on_RegularLineEdit_editingFinished();
private:
   virtual void createTaskModel(QObject *parent, const QVector<QString>& headers) noexcept;
private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QTreeView * sourceView;
    std::unique_ptr<task::QTaskHandler> m_handler;
};

#endif // MAINWINDOW_H
