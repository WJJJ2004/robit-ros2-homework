# ROS2_HW4

# 1. 작업공간으로 이동 후 빌드
```
cd ~/robot_ws
colcon build --packages-select keypad
colcon build --packages-select gameplay
```

# 2. 환경 변수 설정
```
source ~/robot_ws/install/setup.bash
```
# 3. Gameplay ui 노드 실행
```
ros2 run gameplay gameplay
```
# 4. keypad 노드 실행
```
ros2 run keypad keypad
```
