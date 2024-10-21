#ifndef gameplay_MAIN_WINDOW_H
#define gameplay_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QMainWindow>
#include "QIcon"
#include "qnode.hpp"
#include "ui_mainwindow.h"
#include <QPixmap>   // QPixmap 사용
#include <QLabel>    // QLabel 사용
#include <QTimer>    // QTimer 사용

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);  // 생성자
    ~MainWindow();  // 소멸자
    QNode* qnode;   // QNode 객체

protected:
    void resizeEvent(QResizeEvent* event) override;  // 창 크기 변경 시 호출

private:
    Ui::MainWindowDesign* ui;         // UI 핸들러
    QPixmap background;               // 배경 이미지
    QLabel* backgroundLabel;          // 배경을 표시하는 라벨
    QLabel* characterLabel;           // 캐릭터를 표시하는 라벨
    QTimer* animationTimer;           // 애니메이션 타이머
    QString currentAnimation;         // 현재 애니메이션 이름
    int currentFrameIndex;            // 현재 애니메이션 프레임 인덱스

    void closeEvent(QCloseEvent* event) override;  // 창 닫기 이벤트
    void onCommandReceived(const QString &command);  // ROS 명령 수신 처리
    void updateAnimation();  // 애니메이션 업데이트 처리
};

#endif  // gameplay_MAIN_WINDOW_H
