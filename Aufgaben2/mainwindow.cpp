#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "cvmattoqimage.h"

using namespace cv;
Mat picture;
Mat picture2;
double shift;
double scale=1;

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


void MainWindow::on_actionZweites_Bild_triggered(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",  tr("Images (*.png *.xpm *.jpg)"));
    Mat image = imread(fileName.toStdString());

    Mat resizedImage;
    Size resizedImageSize(picture.cols,picture.rows);
    cv::resize(image,resizedImage, resizedImageSize,0,0);
    resizedImage.copyTo(picture2);

}

void MainWindow::on_action_ffnen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",  tr("Images (*.png *.xpm *.jpg)"));
    Mat image = imread(fileName.toStdString());

    image.copyTo(picture);

    //Konsolenausgabe
    int width = image.cols;
    int height = image.rows;
    std::cout << "Aufgabe 1:\nWidth: "<< width<< " Height: "<< height << " Channels: " << image.channels() << " Depth: " << image.depth() << " | ";
    Vec3b pixel1 = image.at<Vec3b>(0,0);
    Vec3b pixel2 = image.at<Vec3b>(1,0);
    Vec3b pixel3 = image.at<Vec3b>((height-1),0);
    Vec3b pixel4 = image.at<Vec3b>(height/2,width/2);
    std::cout <<"\nAufgabe 2:\nTopRight: Red: " << (int)pixel1[2] << " Green: " <<  (int)pixel1[1] << " Blue: " << (int)pixel1[0] <<
        " \n2ndRow: Red: " << (int)pixel2[2] << " Green: " <<  (int)pixel2[1] << " Blue: " << (int)pixel2[0] <<
        " \nBottomLeft: Red: " << (int)pixel3[2] << " Green: " <<  (int)pixel3[1] << " Blue: " << (int)pixel3[0] <<
        " \nCenter: Red: " << (int)pixel4[2] << " Green: " <<  (int)pixel4[1] << " Blue: " << (int)pixel4[0] << "\n" <<endl;


    ui->imageLabel1->setPixmap(cvMatToQPixmap(rescale(picture)));
}


void MainWindow::on_actionHelligkeit_Kontrast_triggered(){

    ui->imageLabel1->setPixmap(cvMatToQPixmap(rescale(picture)));
    ui->imageLabel2->setPixmap(cvMatToQPixmap(rescale(picture)));


}

void MainWindow::on_actionGraustufen_Bin_r_triggered(){

    //Graustufen
    Mat grey(picture.rows, picture.cols, CV_8UC1);
    for(int x = 0; x < picture.cols; x++){
        for(int y = 0; y < picture.rows; y++){
            int red = picture.at<Vec3b>(y,x)[2];
            int green = picture.at<Vec3b>(y,x)[1];
            int blue = picture.at<Vec3b>(y,x)[0];
            grey.at<uchar>(y,x) = (red + green + blue) /3;
        }
    }

    Mat binary(picture.rows, picture.cols, CV_THRESH_BINARY);
    for(int x = 0; x < picture.cols; x++){
        for(int y = 0; y < picture.rows; y++){
            int red = picture.at<Vec3b>(y,x)[2];
            int green = picture.at<Vec3b>(y,x)[1];
            int blue = picture.at<Vec3b>(y,x)[0];
            if(((red + green + blue) /3) >127){
                binary.at<uchar>(y,x) = 255;
            }
            else{
                binary.at<uchar>(y,x) = 0;
            }
        }
    }


    ui->imageLabel1->setPixmap(cvMatToQPixmap(rescale(picture)));
    ui->imageLabel2->setPixmap(cvMatToQPixmap(rescale(grey)));
    ui->imageLabel3->setPixmap(cvMatToQPixmap(rescale(binary)));
}

void MainWindow::on_actionRGB_Komponenten_triggered(){

    int height = picture.rows;
    int width = picture.cols;
    Mat redgrey(height, width, CV_8UC1);
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            int red = picture.at<Vec3b>(y,x)[2];
            redgrey.at<uchar>(y,x) = red;
        }
    }

    Mat bluegrey(height, width, CV_8UC1);
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            int blue = picture.at<Vec3b>(y,x)[0];
            bluegrey.at<uchar>(y,x) = blue;
        }
    }

    Mat greengrey(height, width, CV_8UC1);
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            int green = picture.at<Vec3b>(y,x)[1];
            greengrey.at<uchar>(y,x) = green;
        }
    }

    ui->imageLabel1->setPixmap(cvMatToQPixmap(rescale(picture)));
    ui->imageLabel2->setPixmap(cvMatToQPixmap(rescale(redgrey)));
    ui->imageLabel3->setPixmap(cvMatToQPixmap(rescale(greengrey)));
    ui->imageLabel4->setPixmap(cvMatToQPixmap(rescale(bluegrey)));
}


void MainWindow::on_actionBlendfunktion_triggered(){

    ui->imageLabel1->setPixmap(cvMatToQPixmap(rescale(picture)));
    ui->imageLabel2->setPixmap(cvMatToQPixmap(rescale(picture2)));
    ui->imageLabel3->setPixmap(cvMatToQPixmap(rescale(picture)));
}

Mat MainWindow::rescale(Mat &mat){
    // Skalierungsfaktor bestimmen
    float labelWidth = ui->imageLabel1->width();
    float labelHeight = ui->imageLabel1->height();
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

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    scale = (double)value / 100;
    Mat contrast;
    picture.copyTo(contrast);
    for(int x = 0; x < picture.cols; x++){
        for(int y = 0; y < picture.rows; y++){
            contrast.at<Vec3b>(y,x)[0] = picture.at<Vec3b>(y,x)[0] * scale + shift;
            contrast.at<Vec3b>(y,x)[1] = picture.at<Vec3b>(y,x)[1] * scale + shift;
            contrast.at<Vec3b>(y,x)[2] = picture.at<Vec3b>(y,x)[2] * scale + shift;
        }
    }
    ui->imageLabel2->setPixmap(cvMatToQPixmap(rescale(contrast)));
}



void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    Mat blend;
    picture.copyTo(blend);
    for(int x = 0; x < picture.cols; x++){
        for(int y = 0; y < picture.rows; y++){
            double blue1 = picture.at<Vec3b>(y,x)[0];
            double blue2 = picture2.at<Vec3b>(y,x)[0];
            double green1 = picture.at<Vec3b>(y,x)[1];
            double green2 = picture2.at<Vec3b>(y,x)[1];
            double red1 = picture.at<Vec3b>(y,x)[2];
            double red2 = picture2.at<Vec3b>(y,x)[2];

            double reddiff = red1 - red2;
            double greendiff = green1 - green2;
            double bluediff = blue1 - blue2;

            double rednew = red1 -(reddiff /100 * value);
            double greennew = green1 -(greendiff /100 * value);
            double bluenew = blue1 -(bluediff /100 * value);

            blend.at<Vec3b>(y,x)[0] = bluenew;
            blend.at<Vec3b>(y,x)[1] = greennew;
            blend.at<Vec3b>(y,x)[2] = rednew;
        }
    }
    ui->imageLabel3->setPixmap(cvMatToQPixmap(rescale(blend)));
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    Mat binary(picture.rows, picture.cols, CV_THRESH_BINARY);
    for(int x = 0; x < picture.cols; x++){
        for(int y = 0; y < picture.rows; y++){
            double red = picture.at<Vec3b>(y,x)[2];
            double green = picture.at<Vec3b>(y,x)[1];
            double blue = picture.at<Vec3b>(y,x)[0];
            if(((red + green + blue) /3) >= value){
                binary.at<uchar>(y,x) = 255;
            }
            else{
                binary.at<uchar>(y,x) = 0;
            }
        }
    }
    ui->imageLabel3->setPixmap(cvMatToQPixmap(rescale(binary)));
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    shift = value;
    Mat contrast;
    picture.copyTo(contrast);
    for(int x = 0; x < picture.cols; x++){
        for(int y = 0; y < picture.rows; y++){
            contrast.at<Vec3b>(y,x)[0] = picture.at<Vec3b>(y,x)[0] * scale + shift;
            contrast.at<Vec3b>(y,x)[1] = picture.at<Vec3b>(y,x)[1] * scale + shift;
            contrast.at<Vec3b>(y,x)[2] = picture.at<Vec3b>(y,x)[2] * scale + shift;

        }
    }
    ui->imageLabel2->setPixmap(cvMatToQPixmap(rescale(contrast)));
}
