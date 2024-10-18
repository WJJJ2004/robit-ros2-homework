# ROS2_HW1 

# 1. 작업공간으로 이동 후 빌드
cd ~/robot_ws
colcon build --packages-select turtle_control

# 2. 환경 변수 설정
source ~/robot_ws/install/setup.bash

# 3. Turtlesim 노드 실행
ros2 run turtlesim turtlesim_node

# 4. Teleop 노드 실행
ros2 run turtle_control turtle_control 

