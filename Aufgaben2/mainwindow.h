#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_action_ffnen_triggered();


private:
    cv::Mat MainWindow::rescale(cv::Mat &mat);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
