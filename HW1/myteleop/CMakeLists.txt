cmake_minimum_required(VERSION 3.8)  # CMake 최소 버전 설정
project(myteleop)  # 프로젝트 이름 설정

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)  
endif()

# 의존성 찾기
find_package(ament_cmake REQUIRED)  # ament_cmake 패키지 찾기
find_package(rclcpp REQUIRED)  # rclcpp 패키지 찾기
find_package(geometry_msgs REQUIRED)  # geometry_msgs 패키지 찾기
find_package(turtlesim REQUIRED)  # turtlesim 패키지 찾기

# 테스트 빌드가 활성화된 경우
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)  # ament_lint_auto 패키지 찾기
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()  # 테스트 의존성 찾기
endif()

# 실행 파일 추가 및 의존성 지정
add_executable(myteleop_node src/myteleop.cpp)  # 실행 파일 생성

# 패키지 의존성 지정 (turtlesim 포함)
ament_target_dependencies(myteleop_node rclcpp geometry_msgs turtlesim)

# 실행 파일 설치
install(TARGETS
  myteleop_node  # 설치할 대상
  DESTINATION lib/${PROJECT_NAME})  # 설치할 위치
)

ament_package()  # ament 패키지 메타데이터 설정

