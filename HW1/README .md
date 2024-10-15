# ROS2_HW1 

# 1. 작업공간으로 이동 후 빌드
cd ~/robot_ws
colcon build --packages-select myteleop

# 2. 환경 변수 설정
source ~/robot_ws/install/setup.bash

# 3. Turtlesim 노드 실행
ros2 run turtlesim turtlesim_node

# 4. Teleop 노드 실행
ros2 run myteleop myteleop_node

# 사용법:
# - 방향키: 방향에 따라 거북이가 움직임 
# - C: 거북이가 원을 그리며 움직임
# - S: 거북이가 정사각형을 그리며 움직임 
# - T: 거북이가 정삼각형을 그리며 움직임
# - R: 거북이가 초기 위치로 이동함

