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

#include "../include/gameplay/qnode.hpp"
#include <std_msgs/msg/string.hpp>  // std_msgs 메시지 추가

QNode::QNode()
{
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("gameplay");

  // 구독자 생성 및 초기화
  subscription_ = node->create_subscription<std_msgs::msg::String>(
      "keypad_topic", 10,
      std::bind(&QNode::topicCallback, this, std::placeholders::_1));

  this->start();
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
  rclcpp::WallRate loop_rate(20);
  while (rclcpp::ok())
  {
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
  rclcpp::shutdown();
  Q_EMIT rosShutDown();
}

// 구독자 콜백 함수 구현
void QNode::topicCallback(const std_msgs::msg::String::SharedPtr msg)
{
  QString command = QString::fromStdString(msg->data);
  Q_EMIT commandReceived(command);  // 수신된 명령을 UI로 전달
}

