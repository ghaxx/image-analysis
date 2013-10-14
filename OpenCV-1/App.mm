//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "App.h"
#import "ImageWindow.h"
#import "Negative.h"

using namespace cv;

App::App() {
    this->done = false;
    t = new LinearTransformation();
}

void App::run() {
    Mat image;
    VideoCapture cap;
    for (int i = 0; i < 1500; i++) {
        if (cap.open(i)) {
            std::cout << "Found camera " << i << "\n";
            break;
        }
    }
    if (!cap.isOpened())
        return;
//    ImageWindow *w = new ImageWindow("Image");
//    ImageWindow *g = new ImageWindow("Grayscale");
    registerWindow(new filterWindow::Negative("Negative"));

    do {
        try {
            cap >> image;
//            image = imread("/Users/ghaxx/image.jpg");
//            w->show(image);
//            g->show(filterGrayScale(image));
            for(std::vector<ImageWindow>::iterator it = windows.begin(); it != windows.end(); ++it) {
                (it)->show(filterNegative(image));
            }
        } catch (Exception ignore) {}
        this->catchAction();
    } while (!this->done);
}

void App::catchAction() {
    int key = waitKey(34);
//    std::cout << "Pressed " << key << "\n";
    if (key == 'a')
        t->mult -= 0.1;
    if (key == 'q')
        t->mult += 0.1;
    if (key == 'w')
        t->add += 5;
    if (key == 's')
        t->add -= 5;
    if (key == 'r')
        reset();
    if (key == 27)
        done = true;
}

void App::registerWindow(ImageWindow *window) {
    windows.push_back(*window);
}


Mat App::filterGrayScale(Mat image) {
    Mat grayscale;
    cvtColor(image, grayscale, CV_RGB2GRAY);
    return grayscale;
}

void App::reset() {
    t->mult = 1;
    t->add = 0;
}

Mat App::filterNegative(Mat image) {
//    Mat grayScale = filterGrayScale(image);
//    for (int x = 0; x < grayScale.cols; x++) {
//        for (int y = 0; y < grayScale.rows; y++) {
//            grayScale.at<Vec3b>(y, x)[0] = max(0.0f, min(mult * (255 + additive - grayScale.at<Vec3b>(y, x)[0]), 255.0f));
//        }
//    }
//    char a[100];
//    sprintf(a, "Multiply by %.2f", mult);
//    putText(grayScale, a, cvPoint(10,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
//    sprintf(a, "Add: %d", mult, additive);
//    putText(grayScale, a, cvPoint(10,70), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
//    return grayScale;

    image = t->transform(image);
    char a[100];
    sprintf(a, "Multiply by %.2f", t->mult);
    putText(image, a, cvPoint(10,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
    sprintf(a, "Add: %d", t->add);
    putText(image, a, cvPoint(10,70), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
    return image;
//    Mat negative;
//    bitwise_not(grayScale, negative);
//    return negative;
}