#ifndef gameplay_QNODE_HPP_
#define gameplay_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#endif
#include <QThread>
#include <std_msgs/msg/string.hpp>  // std_msgs 메시지 추가

/*****************************************************************************
** Class
*****************************************************************************/
class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();

protected:
  void run();

private:
  std::shared_ptr<rclcpp::Node> node;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;  // 구독자 추가

  // 메시지 수신 시 호출되는 콜백 함수
  void topicCallback(const std_msgs::msg::String::SharedPtr msg);

Q_SIGNALS:
  void rosShutDown();
  void commandReceived(const QString &command);  // 수신된 명령을 UI로 전달하기 위한 시그널
};

#endif /* gameplay_QNODE_HPP_ */

