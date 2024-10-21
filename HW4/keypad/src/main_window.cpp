/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date August 2024
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/keypad/main_window.hpp"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
    ui->setupUi(this);

    QIcon icon("://ros-icon.png");
    this->setWindowIcon(icon);

    qnode = new QNode();

    QObject::connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));

    // 버튼 클릭 시 메시지 퍼블리시
    connect(ui->jump_button, &QPushButton::clicked, this, &MainWindow::on_jump_button_clicked);
    connect(ui->right_button, &QPushButton::clicked, this, &MainWindow::on_right_button_clicked);
    connect(ui->left_button, &QPushButton::clicked, this, &MainWindow::on_left_button_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QMainWindow::closeEvent(event);
}

// 점프 버튼 클릭 시
void MainWindow::on_jump_button_clicked()
{
    qnode->publishCommand("jump");  // 점프 명령 발행
}

// 오른쪽 버튼 클릭 시
void MainWindow::on_right_button_clicked()
{
    qnode->publishCommand("right");  // 오른쪽 명령 발행
}

// 왼쪽 버튼 클릭 시
void MainWindow::on_left_button_clicked()
{
    qnode->publishCommand("left");  // 왼쪽 명령 발행
}

