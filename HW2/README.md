# ROS2_HW2

### How to run

1. Move to workspace and build
```
cd ~/robot_ws
colcon build --packages-select my_custom_interfaces
colcon build --packages-select my_publisher
colcon build --packages-select my_subscriber
```

2. Setting environment variables
```
source install/setup.bash
```

3. Run publisher and subscriber nodes
```
ros2 run my_publisher publisher_node
ros2 run my_subscriber subscriber_node
```
