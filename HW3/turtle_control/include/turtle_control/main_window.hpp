/**
 * @file /include/turtle_control/main_window.hpp
 *
 * @brief Qt based gui for %(package)s.
 *
 * @date August 2024
 **/

#ifndef turtle_control_MAIN_WINDOW_H
#define turtle_control_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QMainWindow>
#include "QIcon"
#include "qnode.hpp"
#include "ui_mainwindow.h"

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
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  QNode* qnode;

  private slots:
  void on_button_up_clicked();

      void on_button_down_clicked();

  void on_button_left_clicked();

      void on_button_right_clicked();

  private:
  Ui::MainWindowDesign* ui;
  void closeEvent(QCloseEvent* event);
};

#endif  // turtle_control_MAIN_WINDOW_H
