/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date August 2024, Edited October 2024
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/turtle_control/main_window.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
    ui->setupUi(this);

    QIcon icon("://ros-icon.png");
    this->setWindowIcon(icon);

    qnode = new QNode();

    // ROS 종료 시 창을 닫음
    QObject::connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));

    // 화살표 버튼 클릭 이벤트 연결
    connect(ui->button_up, SIGNAL(clicked()), this, SLOT(on_button_up_clicked()));
    connect(ui->button_down, SIGNAL(clicked()), this, SLOT(on_button_down_clicked()));
    connect(ui->button_left, SIGNAL(clicked()), this, SLOT(on_button_left_clicked()));
    connect(ui->button_right, SIGNAL(clicked()), this, SLOT(on_button_right_clicked()));


    // 버튼 크기 설정 (필요에 따라 크기 조정)
    ui->button_up->setFixedSize(200, 200);     // 위쪽 버튼 크기 설정
    ui->button_down->setFixedSize(200, 200);    // 아래쪽 버튼 크기 설정
    ui->button_left->setFixedSize(200, 200);     // 왼쪽 버튼 크기 설정
    ui->button_right->setFixedSize(200, 200);    // 오른쪽 버튼 크기 설정

    // 아이콘 크기 설정 (버튼 크기에 맞춰 조정)
    QSize iconSize(80, 80); // 아이콘 크기 설정
    ui->button_up->setIconSize(iconSize);
    ui->button_down->setIconSize(iconSize);
    ui->button_left->setIconSize(iconSize);
    ui->button_right->setIconSize(iconSize);
    
    // 리소스 파일의 아이콘 설정 (버튼에 아이콘 추가)
    ui->button_up->setIcon(QIcon(":/arrow_up.png"));         // 위쪽 버튼 아이콘
    ui->button_down->setIcon(QIcon(":/arrow_down.png"));  // 아래쪽 버튼 아이콘
    ui->button_left->setIcon(QIcon(":/arrow_left.png"));    // 왼쪽 버튼 아이콘
    ui->button_right->setIcon(QIcon(":/arrow_right.png"));  // 오른쪽 버튼 아이콘
}



void MainWindow::closeEvent(QCloseEvent* event)
{
    QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete qnode;
}

// 위쪽 화살표 버튼 클릭 시 TurtleSim 앞으로 이동
void MainWindow::on_button_up_clicked()
{
    qnode->publishVelocity(2.0, 0.0);  // 선속도: 2.0, 각속도: 0.0
}

// 아래쪽 화살표 버튼 클릭 시 TurtleSim 뒤로 이동
void MainWindow::on_button_down_clicked()
{
    qnode->publishVelocity(-2.0, 0.0);  // 선속도: -2.0, 각속도: 0.0
}

// 왼쪽 화살표 버튼 클릭 시 TurtleSim 왼쪽으로 회전
void MainWindow::on_button_left_clicked()
{
    qnode->publishVelocity(0.0, 2.0);  // 선속도: 0.0, 각속도: 2.0 (좌회전)
}

// 오른쪽 화살표 버튼 클릭 시 TurtleSim 오른쪽으로 회전
void MainWindow::on_button_right_clicked()
{
    qnode->publishVelocity(0.0, -2.0);  // 선속도: 0.0, 각속도: -2.0 (우회전)
}

