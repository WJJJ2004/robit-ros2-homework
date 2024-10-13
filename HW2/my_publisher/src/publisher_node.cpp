#include "rclcpp/rclcpp.hpp"  
#include "my_custom_interfaces/msg/my_custom_message.hpp"  

class MyPublisher : public rclcpp::Node {
public:
    MyPublisher() : Node("my_publisher") 
    {
        
        publisher_ = this->create_publisher<my_custom_interfaces::msg::MyCustomMessage>("custom_topic", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&MyPublisher::publish_message, this));   // 1초마다 publish_message() 함수를 호출하는 타이머 설정
    }

private:
    void publish_message() 
    {
        auto message = my_custom_interfaces::msg::MyCustomMessage();

        std::cout << "Enter a message to publish: ";
        std::getline(std::cin, message.data);        
        publisher_->publish(message); // 퍼블리셔를 사용하여 메시지 발행
    }
    
    rclcpp::Publisher<my_custom_interfaces::msg::MyCustomMessage>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) 
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MyPublisher>());
    rclcpp::shutdown();
    return 0;
}

