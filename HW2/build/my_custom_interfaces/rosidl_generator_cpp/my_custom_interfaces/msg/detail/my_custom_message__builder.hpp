// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_custom_interfaces:msg/MyCustomMessage.idl
// generated code does not contain a copyright notice

#ifndef MY_CUSTOM_INTERFACES__MSG__DETAIL__MY_CUSTOM_MESSAGE__BUILDER_HPP_
#define MY_CUSTOM_INTERFACES__MSG__DETAIL__MY_CUSTOM_MESSAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_custom_interfaces/msg/detail/my_custom_message__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_custom_interfaces
{

namespace msg
{

namespace builder
{

class Init_MyCustomMessage_data
{
public:
  Init_MyCustomMessage_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::my_custom_interfaces::msg::MyCustomMessage data(::my_custom_interfaces::msg::MyCustomMessage::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_custom_interfaces::msg::MyCustomMessage msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_custom_interfaces::msg::MyCustomMessage>()
{
  return my_custom_interfaces::msg::builder::Init_MyCustomMessage_data();
}

}  // namespace my_custom_interfaces

#endif  // MY_CUSTOM_INTERFACES__MSG__DETAIL__MY_CUSTOM_MESSAGE__BUILDER_HPP_
