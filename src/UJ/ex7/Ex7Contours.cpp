//
// Created by Kuba Sławiński on 29/11/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "Ex7Contours.h"
#include "Util.h"

using namespace cv;

Mat orientationMap(const cv::Mat &mag, const cv::Mat &orientation, double thresh = 1.0) {
    Mat orientationMap = Mat::zeros(orientation.size(), CV_8UC3);
    Vec3b red(0, 0, 255);
    Vec3b cyan(255, 255, 0);
    Vec3b green(0, 255, 0);
    Vec3b yellow(0, 255, 255);
    for (int i = 0; i < mag.rows * mag.cols; i++) {
        uchar *magPixel = reinterpret_cast<uchar *>(mag.data + i * sizeof(uchar));
        if (*magPixel > thresh) {
            float *oriPixel = reinterpret_cast<float *>(orientation.data + i * sizeof(float));
            Vec3b *mapPixel = reinterpret_cast<Vec3b *>(orientationMap.data + i * 3 * sizeof(char));
            if (*oriPixel < 45.0)
                *mapPixel = red;
            else if (*oriPixel >= 45.0 && *oriPixel < 135.0)
                *mapPixel = cyan;
            else if (*oriPixel >= 135.0 && *oriPixel < 2225.0)
                *mapPixel = green;
            else if (*oriPixel >= 225.0 && *oriPixel < 315.0)
                *mapPixel = yellow;
        }
    }

    return orientationMap;
}

void Ex7Contours::show() {
    Mat cameraImage;
    capture->read(cameraImage);
    flip(cameraImage, cameraImage, 2);
    Mat result = Mat::zeros(480, 960, cameraImage.type());

//    Util::pictureInPicture(cameraImage, result, 0, 0, 320, 240);

    // Gauss
    Mat gaussian_output;
    if (blurRadius > 0 )
        GaussianBlur(cameraImage, gaussian_output, cv::Size(0, 0), blurRadius);
    else
        cameraImage.copyTo(gaussian_output);
    Util::pictureInPicture(gaussian_output, result, 0, 0, 320, 240);

    // Canny
    Mat canny_output;
    Canny(gaussian_output, canny_output, minThreshold, maxThreshold, 5);
    Util::pictureInPicture(canny_output, result, 320, 0, 320, 240);

    // Sobel
    Mat src, src_gray;
    cvtColor(gaussian_output, src_gray, CV_RGB2GRAY);
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    int scale = 1;
    int delta = 0;
    int dDepth = CV_32F;

    int maskSizeValue = maskSize == 0 ? 0 : maskSize * 2 - 1; // 0 - 0; 1 - 1; 2 - 3; 3 - 5; 4 - 7
    /// Gradient X
    Sobel(src_gray, grad_x, dDepth, 1, 0, maskSizeValue, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    int binaryType = CV_THRESH_BINARY;// | THRESH_OTSU;
    threshold(abs_grad_x, abs_grad_x, minThreshold, 255, binaryType);
    Util::pictureInPicture(abs_grad_x, result, 0, 240, 320, 240);

    /// Gradient Y
    Sobel(src_gray, grad_y, dDepth, 0, 1, maskSizeValue, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);
    threshold(abs_grad_y, abs_grad_y, minThreshold, 255, binaryType);
    Util::pictureInPicture(abs_grad_y, result, 320, 240, 320, 240);
//E1E7 257E 6F31 AFE9 1129 11FA D9
    Mat mag, ori;
    magnitude(grad_x, grad_y, mag);
    phase(grad_x, grad_y, ori, true);
//    cartToPolar(grad_x, grad_y, mag, ori, true);

    convertScaleAbs(mag, mag);
    threshold(mag, mag, minThreshold, 255, binaryType);
    Mat oriMap = orientationMap(mag, ori);
    Util::pictureInPicture(oriMap, result, 640, 0, 320, 240);
    Util::pictureInPicture(mag, result, 640, 240, 320, 240);

    imshow(getTitle(), result);
}

Ex7Contours::Ex7Contours(std::string title):DisplayWindow(title) {
    capture = SynchronizedVideoCapture::getInstance();
    minThreshold = 50;
    maxThreshold = 150;
    blurRadius = 1;
    maskSize = 2;

    createTrackbar("Threshold - min", title, &minThreshold, 300);
    createTrackbar("Threshold - max", title, &maxThreshold, 300);
    createTrackbar("Blur radius", title, &blurRadius, 30);
    createTrackbar("Mask size", title, &maskSize, 6);
}