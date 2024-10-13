#include "rclcpp/rclcpp.hpp"
#include "my_custom_interfaces/msg/my_custom_message.hpp"

class MySubscriber : public rclcpp::Node 
{
public:
    MySubscriber() : Node("my_subscriber") // 구독자 노스 생성 및 콜백함수 세팅하기 
    {
        subscription_ = this->create_subscription<my_custom_interfaces::msg::MyCustomMessage>("custom_topic", 10, std::bind(&MySubscriber::receive_message, this, std::placeholders::_1));
    }

    // create_subscription 함수를 사용하여 구독자를 생성
    // "custom_topic" 토픽을 구독하며, 큐 크기는 10
    // 메시지를 수신할 때마다 receive_message 콜백 함수가 호출됨

private:
    void receive_message(const my_custom_interfaces::msg::MyCustomMessage::SharedPtr msg) 
    {
        RCLCPP_INFO(this->get_logger(), "Received: '%s'", msg->data.c_str());
    }
    
    rclcpp::Subscription<my_custom_interfaces::msg::MyCustomMessage>::SharedPtr subscription_;  // create_subscription을 저장할 구독자 변수를 선언함
};

int main(int argc, char *argv[]) 
{
    rclcpp::init(argc, argv); //시스템 초기화
    rclcpp::spin(std::make_shared<MySubscriber>()); // MySubscriber 노드를 실행하고, 콜백이 발생할 때까지 기다림
    rclcpp::shutdown(); // 시스템 종료
    return 0;
}

