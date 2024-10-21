#include "../include/gameplay/main_window.hpp"
#include <QDebug>
#include <QLabel>
#include <QResizeEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign), currentFrameIndex(0)
{
    ui->setupUi(this);

    QIcon icon("://ros-icon.png");
    this->setWindowIcon(icon);

    qnode = new QNode();  // QNode 객체 생성 및 초기화

    QObject::connect(qnode, &QNode::commandReceived, this, &MainWindow::onCommandReceived);

    // 배경 이미지 설정
    background = QPixmap(":/images/background.png");
    if (background.isNull()) 
    {
        qDebug() << "Failed to load background image!";
    } 
    else 
    {
        qDebug() << "Background image loaded successfully!";
    }

    // QLabel을 사용하여 배경 이미지 설정
    backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(background);
    backgroundLabel->setGeometry(0, 0, this->width(), this->height());
    backgroundLabel->lower();  // 다른 위젯들 뒤로 배치

    characterLabel = new QLabel(this);
    characterLabel->setGeometry(450, 400, 100, 100);  // 초기 캐릭터 위치 설정
    characterLabel->setStyleSheet("background-color: rgba(0, 0, 0, 0);");  

    // 캐릭터 이미지 로드 및 설정
    QPixmap characterImage(":/images/front1.png");
    if (characterImage.isNull()) 
    {
        qDebug() << "Failed to load character image!";
    } 
    else 
    {
        characterLabel->setPixmap(characterImage);  // 캐릭터 이미지 설정
        characterLabel->raise();  // 배경보다 앞으로 설정
    }

    // 타이머 설정: 일정 간격마다 애니메이션을 갱신
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &MainWindow::updateAnimation);  // 타이머가 호출되면 updateAnimation() 실행
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    backgroundLabel->setPixmap(background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));  // 창 크기에 맞춰 배경 이미지 크기를 조정
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QMainWindow::closeEvent(event);  // 기본 창 닫기 이벤트 처리
}

void MainWindow::onCommandReceived(const QString &command)
{
    animationTimer->stop();  
    currentFrameIndex = 0;   // 프레임 인덱스 초기화

    if (command == "jump") 
    {
        currentAnimation = "jump";   
        animationTimer->start(100);  
    }
    else if (command == "left") 
    {
        currentAnimation = "left";   // 좌측 이동 애니메이션 실행
        currentFrameIndex = 1;       
        int newX = characterLabel->x() - 50;  
        qDebug() << "Moving character left. New X position: " << newX;

        // 좌측 이동 모션 시작
        characterLabel->move(newX, characterLabel->y());
        characterLabel->update();  
        animationTimer->start(100);  
    }
    else if (command == "right") 
    {
        currentAnimation = "right";  // 우측 이동 애니메이션 실행
        currentFrameIndex = 1;       
        int newX = characterLabel->x() + 50;  // 캐릭터를 오른쪽으로 50만큼 이동
        qDebug() << "Moving character right. New X position: " << newX;

        // 우측 이동 모션 시작
        characterLabel->move(newX, characterLabel->y());
        characterLabel->update();  // UI 강제 갱신
        animationTimer->start(100);  // 100ms 간격으로 애니메이션 업데이트
    }
}

void MainWindow::updateAnimation()
{
    QString framePath = QString(":/images/%1%2.png").arg(currentAnimation).arg(currentFrameIndex);
    QPixmap frame(framePath);

    if (frame.isNull()) 
    {
        qDebug() << "Failed to load animation frame: " << framePath;
        animationTimer->stop();
        return;
    }

    // 캐릭터 QLabel에 프레임 이미지 설정
    characterLabel->setPixmap(frame);
    currentFrameIndex++;

    // 점프 애니메이션 종료 후 기본 상태로 되돌림 (front1.png)
    if (currentAnimation == "jump" && currentFrameIndex > 4) 
    {
        animationTimer->stop();
        characterLabel->setPixmap(QPixmap(":/images/front1.png")); 
    }
 // 기본 설정값으로 리턴하기 
    else if (currentAnimation == "left" && currentFrameIndex > 5) 
    {
        animationTimer->stop();  // 애니메이션 타이머 종료
        characterLabel->setPixmap(QPixmap(":/images/front1.png"));  
    }
    // 기본 설정값으로 리턴하기 
    else if (currentAnimation == "right" && currentFrameIndex > 5) 
    {
        animationTimer->stop();  // 애니메이션 타이머 종료
        characterLabel->setPixmap(QPixmap(":/images/front1.png")); 
    }
}

