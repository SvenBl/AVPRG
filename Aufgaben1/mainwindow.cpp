#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include <string>
using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    testImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testImage(){

}


void MainWindow::showMat(const Mat &mat){
    // convert Mat object to QImage object
    QImage image( mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888 );
    image = image.rgbSwapped();

    // convert QImage object to QPixmap object
    QPixmap pixmap = QPixmap::fromImage(image);

    // set QPixmap object for QLabel
    ui->imageLabel->setPixmap(pixmap);
}

void MainWindow::on_pushButton_clicked()
{
    Scalar grey = Scalar(200, 200, 200);
    Scalar white = Scalar(256,256,256);
    Scalar black = Scalar(0,0,0);

    Mat image(400, 400, CV_8UC3, grey);

    circle(image,Point(199,200),200, white, -1);
    for(int i = 1; i<=10; i++){
     circle(image, Point(199,200),i*20,black,1);
    }
    showMat(image);
}

void MainWindow::on_pushButton_2_clicked()
{
    Scalar randomColor;
    Scalar grey = Scalar(200, 200, 200);
    Mat image(400,400, CV_8UC3,grey);
    for(int i = 0; i < 1000; i++){
        randomColor = Scalar(rand() % 257, rand() % 257, rand() % 257);
        circle(image, Point(rand() % 401,rand() % 401), 10, randomColor, -1);
    }
    showMat(image);
}

void MainWindow::on_pushButton_3_clicked()
{
    Scalar white = Scalar(256,256,256);
    Scalar black = Scalar(0,0,0);

    Mat image(400, 400, CV_8UC3, white);

    for(int i = 0; i < 380; i = i +40){
        rectangle(image, Point(i,0), Point(20 +i,400), black, -1);
    }
    showMat(image);
}

void MainWindow::on_pushButton_4_clicked()
{
    Scalar white = Scalar(256,256,256);
    Scalar black = Scalar(0,0,0);

    Mat image(400, 400, CV_8UC3, white);

    for(int x = 0; x < 400; x = x +40){
        for(int y = 0; y < 400; y = y +40){
                if(x % 80 == 0 && y % 80 == 0){
                    rectangle(image, Point(0 + x,0 +y), Point(40 + x,40 + y), black, -1);
                }
                if(x % 80  == 40 && y % 80   ==  40){
                    rectangle(image, Point(0 + x,0 +y), Point(40 + x,40 + y), black, -1);
                }

        }
    }
    showMat(image);
}

void MainWindow::on_pushButton_5_clicked()
{
    Scalar random;
    Scalar black = Scalar(0,0,0);
    Mat image(400, 400, CV_8UC3, Scalar(0,0,0));

    for(int x = 0; x < 400; x = x +40){
        for(int y = 0; y < 400; y = y +40){
                    random = Scalar(rand() % 257, rand() % 257, rand() % 257);
                    rectangle(image, Point(0 + x,0 +y), Point(40 + x,40 + y), random, -1);
        }
    }
    for(int x = 40; x < 400; x = x + 40){
        line(image,Point(x,0),Point(x,400),black,1);
    }
    for(int y = 40; y < 400; y = y + 40){
        line(image,Point(0,y),Point(400,y),black,1);
    }
    showMat(image);
}

void MainWindow::on_pushButton_6_clicked()
{
    QString img =  QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.xpm *.jpg)"));
    std::string test = img.toStdString();
    Mat mat = imread(test);
    int width = mat.cols;
    int height = mat.rows;
    if(width >=400 || height >= 400){
        if(width >= height){
            double scaling = width / height;
            int newHeight = (int)(400 /scaling);
            Mat scaledImage(height,width,mat.type());
            cv::resize(mat,scaledImage,Size(400,newHeight));
            showMat(scaledImage);
        }
        else{
            double scaling = height / width;
            int newWidth = 400 /scaling;
            Mat scaledImage(height,width,mat.type());
            cv::resize(mat,scaledImage,Size(newWidth,400));
            showMat(scaledImage);
        }
    }
    else{
        showMat(mat);
    }


}
