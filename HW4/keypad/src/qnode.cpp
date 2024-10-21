/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date August 2024
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/keypad/qnode.hpp"
#include <std_msgs/msg/string.hpp>  // std_msgs 메시지 추가

QNode::QNode()
{
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("keypad");

  // 퍼블리셔 생성
  publisher_ = node->create_publisher<std_msgs::msg::String>("keypad_topic", 10);

  this->start();  // 스레드를 시작해 노드 스핀
}

QNode::~QNode()
{
  if (rclcpp::ok())
  {
    rclcpp::shutdown();
  }
}

void QNode::run()
{
  rclcpp::WallRate loop_rate(20);  // 루프 속도 설정 (20Hz)
  while (rclcpp::ok())
  {
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
  rclcpp::shutdown();
  Q_EMIT rosShutDown();  // ROS 종료 시그널 발생
}

// 퍼블리셔를 통해 명령을 발행하는 함수
void QNode::publishCommand(const std::string &command)
{
  std_msgs::msg::String msg;
  msg.data = command;
  publisher_->publish(msg);
}

