/**
 * @file /include/turtle_control/qnode.hpp
 *
 * @brief Communications central between ROS2 and Qt.
 *
 * @date February 2011, Edited October 2024
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef turtle_control_QNODE_HPP_
#define turtle_control_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>  // ROS2 메시지 타입
#endif
#include <QThread>
#include <memory>

/*****************************************************************************
** Class
*****************************************************************************/
class QNode : public QThread
{
    Q_OBJECT
public:
    QNode();
    ~QNode();

    // 메시지 퍼블리시 함수
    void publishVelocity(double linear, double angular);

protected:
    void run();

private:
    std::shared_ptr<rclcpp::Node> node;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher;  // TurtleSim에 보낼 퍼블리셔

Q_SIGNALS:
    void rosShutDown();  // ROS2가 종료될 때 보내는 시그널
};

#endif /* turtle_control_QNODE_HPP_ */

