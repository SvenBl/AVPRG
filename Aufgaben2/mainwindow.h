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
    void on_actionZweites_Bild_triggered();
    void on_actionHelligkeit_Kontrast_triggered();
    void on_actionGraustufen_Bin_r_triggered();
    void on_actionRGB_Komponenten_triggered();
    void on_actionBlendfunktion_triggered();


    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_4_valueChanged(int value);

private:
    cv::Mat MainWindow::rescale(cv::Mat &mat);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
