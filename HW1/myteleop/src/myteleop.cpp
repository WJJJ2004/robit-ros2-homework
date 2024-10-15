#include "rclcpp/rclcpp.hpp" // ROS2 RCLCPP 라이브러리 포함
#include "geometry_msgs/msg/twist.hpp" // Twist 메시지 포함
#include <termios.h> // 터미널 입출력 제어를 위한 라이브러리 포함
#include <unistd.h> // 유닉스 표준 함수들 포함
#include <chrono> // 시간 관련 라이브러리 포함

using namespace std::chrono_literals; // 시간을 쉽게 사용하기 위한 네임스페이스

class MyTeleop : public rclcpp::Node 
{
public:
    MyTeleop() : Node("myteleop_node") // 노드 생성자
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10); // 퍼블리셔 생성
        timer_ = this->create_wall_timer(100ms, std::bind(&MyTeleop::publish_command, this)); // 타이머 생성
        init_msg(); // 메시지 초기화 
    }
    
    void publish_command() // 키 입력을 받아 명령을 퍼블리시하는 메소드
    {
        char key = get_key(); // 키 입력 받기

        switch (key) 
        {
            case 'U':  // 앞으로 이동
                msg.linear.x = 1.0;
                break;
            case 'D':  // 뒤로 이동
                msg.linear.x = -1.0;
                break;
            case 'L':  // 좌회전
                msg.angular.z = 1.0;
                break;
            case 'R':  // 우회전
                msg.angular.z = -1.0;
                break;
            case 'r':  // 초기 위치로 이동 
                system("ros2 service call /turtle1/teleport_absolute turtlesim/srv/TeleportAbsolute \"{x: 5.5, y: 5.5, theta: 0.0}\"");
                return;
            case 'q':  // 종료
                rclcpp::shutdown(); // ROS 노드 종료
                return;
            case 's': // 정사각형 그리기
                Draw_square();
                break;
            case 'c': // 원 그리기
                Draw_circle();
                break;    
            case 't': // 삼각형 그리기
                Draw_triangle();
                break;
            default:
                break; // 그 외 키는 무시
        }

        publisher_->publish(msg); // 메시지 퍼블리시
        
        init_msg(); // 메시지 초기화
    }

private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_; // 퍼블리셔 포인터
    rclcpp::TimerBase::SharedPtr timer_; // 타이머 포인터
    geometry_msgs::msg::Twist msg; // 메시지 객체

    void init_msg() // 메시지 초기화 메소드
    {
        msg.linear.x = 0.0;  // 선속도 초기화
        msg.angular.z = 0.0; // 각속도 초기화
    }

    char get_key() // 키보드 입력을 받아오는 메소드
    {
        struct termios oldt, newt; // 터미널 속성 구조체
        char ch; // 입력 문자
        tcgetattr(STDIN_FILENO, &oldt); // 현재 터미널 속성 가져오기
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // 캐논 모드와 에코 비활성화
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); // 새로운 속성 적용

        ch = getchar(); // 문자 입력

        if (ch == '\x1b') // Escape 시퀀스 시작 (방향키 감지)
        {
            char seq[2]; // 방향키 시퀀스 저장 배열
            seq[0] = getchar(); // '[' 문자
            seq[1] = getchar(); // 방향키 문자

            if (seq[0] == '[') 
            {
                switch (seq[1]) 
                {
                    case 'A':
                        ch = 'U'; // 위쪽 방향키
                        break;
                    case 'B':
                        ch = 'D'; // 아래쪽 방향키
                        break;
                    case 'C':
                        ch = 'R'; // 오른쪽 방향키
                        break;
                    case 'D':
                        ch = 'L'; // 왼쪽 방향키
                        break;
                    default:
                        ch = 0; // 알 수 없는 키
                        break;
                }
            }
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 원래 터미널 설정 복원
        return ch; // 입력 문자 반환
    }

    void Draw_triangle() // 삼각형 그리기 메소드
    {
        for(int i = 0; i < 3; i++) // 3번 반복
        {
            msg.linear.x = 1.0; // 앞으로 이동
            msg.angular.z = 0; // 회전 없음
            publisher_->publish(msg); // 메시지 퍼블리시
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1초 대기
		
            msg.linear.x = 0; // 정지
            msg.angular.z = 2.0944; // 회전 각속도 설정 (60도)
            publisher_->publish(msg); // 메시지 퍼블리시
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1초 대기
        }
        init_msg(); // 메시지 초기화
    }

    void Draw_square() // 정사각형 그리기 메소드
    {
        for (int i = 0; i < 4; ++i) // 4번 반복
        {
            msg.linear.x = 2.0; // 앞으로 이동
            msg.angular.z = 0; // 회전 없음
            publisher_->publish(msg); // 메시지 퍼블리시
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1초 대기

            msg.linear.x = 0; // 정지
            msg.angular.z = 1.5708; // 회전 각속도 설정 (90도)
            publisher_->publish(msg); // 메시지 퍼블리시
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1초 대기
        }

        init_msg(); // 메시지 초기화
    }

    void Draw_circle() // 원 그리기 메소드
    {   
        for(int i = 0; i < 4; i++) // 4번 반복
        {
            msg.linear.x = 2.0; // 선속도 설정
            msg.angular.z = 1.6; // 각속도 설정
            publisher_->publish(msg); // 메시지 퍼블리시
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1초 대기
        }

        init_msg(); // 메시지 초기화
    }
};

int main(int argc, char *argv[]) 
{
    rclcpp::init(argc, argv); // ROS 초기화
    rclcpp::spin(std::make_shared<MyTeleop>()); // 노드 실행
    rclcpp::shutdown(); // ROS 종료
    return 0;
}



