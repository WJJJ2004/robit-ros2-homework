#ifndef keypad_QNODE_HPP_
#define keypad_QNODE_HPP_

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

  void publishCommand(const std::string &command);  // 문자열 명령을 퍼블리시

protected:
  void run();

private:
  std::shared_ptr<rclcpp::Node> node;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;  // 퍼블리셔 추가

Q_SIGNALS:
  void rosShutDown();
};

#endif /* keypad_QNODE_HPP_ */

