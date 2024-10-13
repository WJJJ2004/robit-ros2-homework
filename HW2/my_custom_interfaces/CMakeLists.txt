# 최소 CMake 버전을 3.8로 설정
cmake_minimum_required(VERSION 3.8)

# 프로젝트 이름 설정
project(my_custom_interfaces)

# GNU C++ 또는 Clang 컴파일러를 사용할 경우 컴파일 옵션 설정
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # 모든 경고를 활성화
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 의존성 패키지 찾기
find_package(ament_cmake REQUIRED) # ament_cmake 패키지 필수
find_package(rosidl_default_generators REQUIRED) # rosidl_default_generators 패키지 필수

# 메시지 파일 빌드 설정
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/MyCustomMessage.msg" # 생성할 메시지 파일 지정
)

# 테스트 빌드를 위한 설정
if(BUILD_TESTING) # 테스트 빌드가 활성화된 경우
  find_package(ament_lint_auto REQUIRED) # 자동 코드 검사 도구를 찾음
  set(ament_cmake_copyright_FOUND TRUE) # 저작권 검사 활성화
  set(ament_cmake_cpplint_FOUND TRUE) # C++ 코드 스타일 검사 활성화
  ament_lint_auto_find_test_dependencies() # 테스트 의존성 자동 검색
endif()

# ament 환경 후크 설정 추가
ament_environment_hooks() # ament 환경 후크 추가

# ament 패키지 설정
ament_package() # 패키지 설정 완료

