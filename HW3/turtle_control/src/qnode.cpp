/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central between ROS2 and Qt!
 *
 * @date August 2024, Edited October 2024
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/turtle_control/qnode.hpp"
#include <geometry_msgs/msg/twist.hpp>  // TurtleSim에 필요한 메시지 타입

/*****************************************************************************
** QNode Class Implementation
*****************************************************************************/

QNode::QNode() {
    int argc = 0;
    char** argv = nullptr;
    rclcpp::init(argc, argv);  // ROS2 초기화

    node = rclcpp::Node::make_shared("turtle_control");

    // TurtleSim에 대한 퍼블리셔 설정 (/turtle1/cmd_vel 토픽으로 메시지 전송)
    velocity_publisher = node->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);

    // QThread 시작 (run 함수가 호출됨)
    this->start();
}

QNode::~QNode() {
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
}

void QNode::run() {
    rclcpp::WallRate loop_rate(20);  // 20Hz로 루프 실행
    while (rclcpp::ok()) {
        rclcpp::spin_some(node);  // 메시지 처리
        loop_rate.sleep();        // 루프 속도 조절
    }
    rclcpp::shutdown();
    Q_EMIT rosShutDown();  // ROS 종료 시 Qt 시그널 발생
}

void QNode::publishVelocity(double linear, double angular) {
    // 속도 메시지 생성
    geometry_msgs::msg::Twist msg;
    msg.linear.x = linear;      // 선속도
    msg.angular.z = angular;    // 각속도

    // 퍼블리시
    velocity_publisher->publish(msg);
}
