cmake_minimum_required(VERSION 3.5)
project(turtle_control)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 의존성 찾기
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)  # std_msgs 추가
find_package(geometry_msgs REQUIRED)  # geometry_msgs 추가
find_package(Boost 1.71.0 REQUIRED COMPONENTS thread)
find_package(Qt5 COMPONENTS Widgets Core Gui Network REQUIRED)
find_package(rosidl_default_generators REQUIRED)  # rosidl_default_generators 추가
find_package(rosidl_default_runtime REQUIRED)  # rosidl_default_runtime 추가

# 파일 경로 정의
file(GLOB PRO_SOURCE_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)
file(GLOB PRO_UI_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS ui/*.ui)
file(GLOB PRO_INCLUDE_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS include/${PROJECT_NAME}/*.h include/${PROJECT_NAME}/*.hpp)
file(GLOB PRO_RESOURCE_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS resource/*.qrc)

# Qt 처리
qt5_wrap_ui(QT_UI_HPP ${PRO_UI_DIR})
qt5_wrap_cpp(QT_MOC_HPP ${PRO_INCLUDE_DIR})
qt5_add_resources(QT_RESOURCE_HPP ${PRO_RESOURCE_DIR})  # 변수 이름 수정

include_directories(
  include/
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(${PROJECT_NAME}
    ${PRO_SOURCE_DIR}
    ${PRO_INCLUDE_DIR}
    ${PRO_UI_DIR}
    ${QT_MOC_HPP}
    ${QT_RESOURCE_HPP}  # 수정된 변수 이름 사용
    ${QT_UI_HPP} 
)

# 타겟 의존성 추가
ament_target_dependencies(${PROJECT_NAME} rclcpp std_msgs geometry_msgs Boost)

# Qt 라이브러리 링크
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network)

# 설치 설정
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# 테스트 빌드 설정
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

# 패키지 정보 설정
ament_package()



