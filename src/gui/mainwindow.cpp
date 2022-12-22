#include "gui/mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "defines.hpp"

#include <QMessageBox>
#include <QVector>
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle(NAME SPACE VERSION);

    sourceView = new QTreeView;
    sourceView->setRootIsDecorated(false);
    sourceView->setAlternatingRowColors(true);

    QHBoxLayout* sourceLayout = new QHBoxLayout;
    sourceLayout->addWidget(sourceView);
    ui->MainBox->setLayout(sourceLayout);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(ui->MainBox);

    // Create headers for GroupBox
    createTaskModel(parent, {"Name", "Description", "Date", "Category"});
    sourceView->setModel(model);

    m_handler = std::make_unique<GuiTaskHandler>(model);
}

QStandardItemModel* MainWindow::getModel() const noexcept { return model; }

void MainWindow::createTaskModel(QObject* parent, const QVector<QString>& headers) noexcept {
    model = new QStandardItemModel(0, headers.size(), parent);

    for (int i = 0; i < headers.size(); i++) {
        model->setHeaderData(i, Qt::Horizontal, headers.at(i));
    }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_AddTaskButton_clicked() {
    // create dialog window
}

void MainWindow::on_RegularLineEdit_editingFinished() {
    if (m_handler->parseCommand(ui->RegularLineEdit->text().toStdString()) == def::eCode::SUCCES) {
        ui->RegularLineEdit->clear();
    } else {
        QMessageBox box;
        box.setIcon(QMessageBox::Information);
        box.setDefaultButton(QMessageBox::Ok);
        box.setText("Unrecognized expression!");
        box.exec();
    }
}
