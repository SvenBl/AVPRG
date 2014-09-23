#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "cvmattoqimage.h"

using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_ffnen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",  tr("Images (*.png *.xpm *.jpg)"));
    Mat image = imread(fileName.toStdString());



    //Konsolenausgabe
    int width = image.cols;
    int height = image.rows;
    std::cout << "Aufgabe 1:\nWidth: "<< width<< " Height: "<< height << " Channels: " << image.channels() << " Depth: " << image.depth() << " | " <<endl;
    Vec3b pixel1 = image.at<Vec3b>(0,0);
    Vec3b pixel2 = image.at<Vec3b>(1,0);
    Vec3b pixel3 = image.at<Vec3b>((height-1),0);
    Vec3b pixel4 = image.at<Vec3b>(height/2,width/2);
    std::cout <<"\nAufgabe 2:\nTopRight: Red: " << (int)pixel1[2] << " Green: " <<  (int)pixel1[1] << " Blue: " << (int)pixel1[0] <<
        " \n2ndRow: Red: " << (int)pixel2[2] << " Green: " <<  (int)pixel2[1] << " Blue: " << (int)pixel2[0] <<
        " \nBottomLeft: Red: " << (int)pixel3[2] << " Green: " <<  (int)pixel3[1] << " Blue: " << (int)pixel3[0] <<
        " \nCenter: Red: " << (int)pixel4[2] << " Green: " <<  (int)pixel4[1] << " Blue: " << (int)pixel4[0] << "\n";


    //+10
    Mat hell;
    image.copyTo(hell);
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            hell.at<Vec3b>(y,x)[0] = image.at<Vec3b>(y,x)[0] + 10;
            hell.at<Vec3b>(y,x)[1] = image.at<Vec3b>(y,x)[1] + 10;
            hell.at<Vec3b>(y,x)[2] = image.at<Vec3b>(y,x)[2] + 10;
        }
    }

    //Graustufen
    Mat grey(height, width, CV_8UC1);
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            int red = image.at<Vec3b>(y,x)[2];
            int green = image.at<Vec3b>(y,x)[1];
            int blue = image.at<Vec3b>(y,x)[0];
            grey.at<uchar>(y,x) = (red + green + blue) /3;
        }
    }

    Mat redgrey(height, width, CV_8UC1);
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            int red = image.at<Vec3b>(y,x)[2];
            redgrey.at<uchar>(y,x) = red;
        }
    }

    Mat bluegrey(height, width, CV_8UC1);
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            int blue = image.at<Vec3b>(y,x)[0];
            bluegrey.at<uchar>(y,x) = blue;
        }
    }

    Mat greengrey(height, width, CV_8UC1);
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            int green = image.at<Vec3b>(y,x)[1];
            greengrey.at<uchar>(y,x) = green;
        }
    }



    ui->imageLabel->setPixmap(cvMatToQPixmap(rescale(redgrey)));
}

Mat MainWindow::rescale(Mat &mat){
    // Skalierungsfaktor bestimmen
    float labelWidth = ui->imageLabel->width();
    float labelHeight = ui->imageLabel->height();
    float imageWidth = mat.cols;
    float imageHeight = mat.rows;
    float scale = labelWidth / imageWidth;
    if (labelHeight/imageHeight < scale){
        scale = labelHeight / imageHeight;
    }

    // neue Bildbreite berechnen
    float scaledImageWidth = imageWidth * scale;
    float scaledImageHeight = imageHeight * scale;

    // skaliertes Mat-Objekt erzeugen
    Mat scaledImage (scaledImageHeight, scaledImageWidth, mat.type());
    cv::resize(mat, scaledImage, Size(scaledImageWidth, scaledImageHeight));
    return scaledImage;
}
