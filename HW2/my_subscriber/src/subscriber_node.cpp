#include "rclcpp/rclcpp.hpp"
#include "my_custom_interfaces/msg/my_custom_message.hpp"

class MySubscriber : public rclcpp::Node 
{
public:
    MySubscriber() : Node("my_subscriber") 
    {
        subscription_ = this->create_subscription<my_custom_interfaces::msg::MyCustomMessage>("custom_topic", 10, std::bind(&MySubscriber::receive_message, this, std::placeholders::_1));
    }

private:
    void receive_message(const my_custom_interfaces::msg::MyCustomMessage::SharedPtr msg) 
    {
        RCLCPP_INFO(this->get_logger(), "Received: '%s'", msg->data.c_str());
    }
    
    rclcpp::Subscription<my_custom_interfaces::msg::MyCustomMessage>::SharedPtr subscription_;
};

int main(int argc, char *argv[]) 
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MySubscriber>()); 
    rclcpp::shutdown();
    return 0;
}

