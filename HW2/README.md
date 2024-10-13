# ROS2_HW2

### 테스트 하는 방법

1. 프로젝트 빌드하기 
```
cd ~/robot_ws
colcon build --packages-select my_custom_interfaces
colcon build --packages-select my_publisher
colcon build --packages-select my_subscriber
```

2. 노드 생성하기

 새로운 터미널 창을 키고 해당 명령어를 입력한다.

 Pub 노드 생성하기 
```
cd ~/robot_ws
source install/setup.bash
ros2 run my_publisher publisher_node
```

 Sub 노드 생성하기
```
cd ~/robot_ws
source install/setup.bash
ros2 run my_subscriber subscriber_node
```
