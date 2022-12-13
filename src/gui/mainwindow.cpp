#include "gui/mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "defines.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(NAME SPACE VERSION);
}

MainWindow::~MainWindow()
{
    delete ui;
}
