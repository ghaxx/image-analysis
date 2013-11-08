//
// Created by Kuba Sławiński on 01/11/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "Window5.h"
#include "AppConfig.h"

const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;

using namespace cv;

string Window5::intToString(int number) {
    std::stringstream ss;
    ss << number;
    return ss.str();
}

void Window5::pictureInPicture(Mat &source, Mat &destination, int x, int y, int w, int h) {
    Mat small;
    resize(source, small, Size(w, h));
    Mat subView = destination(Rect(x, y, small.cols, small.rows));
    if (small.type() != destination.type())
        cvtColor(small, small, CV_GRAY2RGB);
    small.copyTo(subView);
}

void Window5::addAlphaMat(Mat &src, Mat &dst, double alpha) {
    for (int x = 0; x < dst.cols; x++) {
        for (int y = 0; y < dst.rows; y++) {
            if (src.at<Vec3b>(y, x)[0] != 0)
                for (int c = 0; c < dst.channels(); c++) {
                    double v = ((1 - alpha) * dst.at<Vec3b>(y, x)[c]) + ((alpha) * src.at<Vec3b>(y, x)[c]);
                    dst.at<Vec3b>(y, x)[c] = max(0.0, min(v, 255.0));
                }
        }
    }
}

void Window5::addAlphaMat(Mat &src, Mat &dst) {
    for (int x = 0; x < dst.cols; x++) {
        for (int y = 0; y < dst.rows; y++) {
            if (src.at<Vec3b>(y, x)[3] != 0)
                for (int c = 0; c < dst.channels(); c++) {
                    double alpha = (double) src.at<Vec4b>(y, x)[3] / 255;
                    double v = ((1.0 - alpha) * dst.at<Vec3b>(y, x)[c]) + ((alpha) * src.at<Vec4b>(y, x)[c]);
                    dst.at<Vec3b>(y, x)[c] = max(0.0, min(v, 255.0));
                }
        }
    }
}

// From image to black and white
void Window5::extractShapesInBinaryByDifference(Mat &image, Mat &thresh) {
    absdiff(image, background, thresh);
    pictureInPicture(thresh, result, 0, 240, 320, 240);
    cvtColor(thresh, thresh, CV_RGB2GRAY);
    if (blurRadius > 0)
        cv::GaussianBlur(thresh, thresh, cv::Size(0, 0), blurRadius);

    threshold(thresh, thresh, thresholdMin, 255, CV_THRESH_BINARY | THRESH_OTSU);

    Mat erodeElement = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    erode(thresh, thresh, erodeElement, Point(-1, -1), 3);

    Mat dilateElement = getStructuringElement(MORPH_ELLIPSE, Size(6, 6));
    dilate(thresh, thresh, dilateElement);

    morphologyEx(thresh, thresh, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(7, 7)));
}

void Window5::findHull(vector<Point> &contour, Mat &dest) {
    vector<vector<Point> > hull(1);
    cv::vector<cv::vector<int> > hull_i(1);

    Mat drawing = Mat::zeros(dest.size(), CV_8UC3);

    convexHull(Mat(contour), hull[0], false);
    convexHull(Mat(contour), hull_i[0], false);
    drawContours(drawing, hull, 0, Scalar(1, 1, 50), 2, 8, vector<Vec4i>(), 0, Point());
    drawContours(drawing, hull, 0, Scalar(20, 20, 200), 1, 8, vector<Vec4i>(), 0, Point());

    addAlphaMat(drawing, dest, 0.4);
    drawing = Mat::zeros(dest.size(), CV_8UC3);

    std::vector<Vec4i> convDef;

    if (hull_i[0].size() > 3) {
        convexityDefects(contour, hull_i[0], convDef);

        int max4[convDef.size()];
        int max4p[convDef.size()];
        for (int k = 0; k < convDef.size(); k++) {
            int ind_0 = convDef[k][0];
            int ind_1 = convDef[k][1];
            int ind_2 = convDef[k][2];
            max4[k] = convDef[k][3];
            max4p[k] = convDef[k][2];
            cv::line(drawing, contour[ind_2], contour[ind_0], Scalar(1, 0, 25), 2);
            cv::line(drawing, contour[ind_2], contour[ind_1], Scalar(1, 0, 25), 2);
            cv::circle(drawing, contour[ind_0], 3, Scalar(1, 25, 0), -1);
            cv::circle(drawing, contour[ind_1], 3, Scalar(1, 25, 0), -1);
            cv::circle(drawing, contour[ind_2], 3, Scalar(1, 0, 25), -1);

            cv::line(drawing, contour[ind_2], contour[ind_0], Scalar(1, 0, 255), 1);
            cv::line(drawing, contour[ind_2], contour[ind_1], Scalar(1, 0, 255), 1);
            cv::circle(drawing, contour[ind_0], 2, Scalar(1, 255, 0), -1);
            cv::circle(drawing, contour[ind_1], 2, Scalar(1, 255, 0), -1);
            cv::circle(drawing, contour[ind_2], 2, Scalar(1, 0, 255), -1);
        }
//        std::sort(convDef.begin(), convDef.end(), sortConvDef);
//        int maxc = 0;
        double average = 0;
        for (int k = 0; k < 4 && k < convDef.size(); k++) {
            average += convDef[k][3];
        }
        average = average / convDef.size();

//        for (int k = 0; k < 4 && k < convDef.size(); k++) {
        for (int k = 0; k < convDef.size(); k++) {
//            if (convDef[k][3] > 20 * average) {
            if (convDef[k][3] > 3000) {
                int ind_0 = convDef[k][0];
                int ind_1 = convDef[k][1];
                int ind_2 = convDef[k][2];
                cv::circle(drawing, contour[ind_0], 11, Scalar(1, 255, 25), -1);
                cv::circle(drawing, contour[ind_0], 9, Scalar(1, 255, 255), -1);
                cv::circle(drawing, contour[ind_1], 11, Scalar(1, 255, 25), -1);
                cv::circle(drawing, contour[ind_1], 9, Scalar(1, 255, 255), -1);
                cv::circle(drawing, contour[ind_2], 11, Scalar(1, 255, 25), -1);
                cv::circle(drawing, contour[ind_2], 9, Scalar(1, 255, 255), -1);
            }
//            if (ind_1 > maxc)
//                maxc = ind_1;
        }
//        cv::circle(drawing, contour[maxc], 11, Scalar(1, 255, 25), -1);
//        cv::circle(drawing, contour[maxc], 9, Scalar(1, 255, 255), -1);
    }
    addAlphaMat(drawing, dest, 0.4);
}


void Window5::addContours(Mat &source, Mat &dest) {
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using canny
    Canny(source, canny_output, 10, 100 * 2, 3);
    findContours(canny_output, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    /// Find contours
//    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//    findContours(source, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    /// Draw contours
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    int max = 0;
    double maxArea = 0;
    for (int i = 0; i < contours.size(); i++) {
        Moments moment = moments((cv::Mat) contours[i]);
        double area = moment.m00;
        if (area > maxArea) {
            maxArea = area;
            max = i;
        }
//        findCenterOfObject(contours[i], dest);
//        findHull(contours[i], dest);
    }
    drawContours(drawing, contours, max, Scalar(20, 240, 20), 1, 8, hierarchy, 0, Point());
    drawContours(drawing, contours, max, Scalar(2, 20, 2), 2, 8, hierarchy, 0, Point());
    addAlphaMat(drawing, dest, 0.4);

    findHull(contours[max], dest);
//    addBoundingBox(contours[max], dest);
}

void Window5::show() {
    try {
        result = Mat::zeros(480, 640 + 320, image.type());
        capture->read(image);
        Mat tmp;
        resize(image, image, Size(640, 480));
        image.copyTo(tmp);
//        image = imread(AppConfig::inputDir + "/h.jpg", CV_LOAD_IMAGE_COLOR);
        Mat thresholdMat;


        if (morph) {
            extractShapesInBinaryByDifference(image, thresholdMat);
        }

//        trackFilteredObject(x, y, thresholdMat, image);

        //        cvtColor(thresholdMat, thresholdMat, CV_GRAY2RGB);
        //        multiply(thresholdMat, image, image, 1.0/255); // show only found objects
        addContours(thresholdMat, image);

        pictureInPicture(thresholdMat, result, 0, 0, 320, 240);
        pictureInPicture(image, result, 320, 0, 640, 480);

        if (record) {
            writer->write(result);
        }
        imshow(getTitle(), result);

        thresholdMat.release();
        if (diffWithPrevious) {
//            capture->read(background);
            tmp.copyTo(background);
//            resize(background, background, Size(640, 480));
        }
//        result.release();
    } catch(...) {}
}


Window5::Window5(std::string title):DisplayWindow(title) {
    capture = new VideoCapture(AppConfig::inputDir + "/4.avi");
    writer = new VideoWriter();

    result = Mat::zeros(480, 640 + 320, 16);
    background = Mat::zeros(480, 640, 16);
    thresholdMin = 50;

    diffWithPrevious = true;
    record = false;
    morph = true;
    blurRadius = 5;

    createTrackbar("Threshold - min", title, &thresholdMin, 255);
    createTrackbar("Blur radius", title, &blurRadius, 30);
}

Window5::~Window5() {
}

void Window5::control(char key) {
    if (key == 'q') setThresholdMin(thresholdMin + 1);
    if (key == 'a') setThresholdMin(thresholdMin - 1);

    if (key == 'r') setBlurRadius(blurRadius + 1);
    if (key == 'f') setBlurRadius(blurRadius - 1);

    if (key == 'm') morph = !morph;
    if (key == 'x') diffWithPrevious = true;

    if (key == 'c') {
        diffWithPrevious = false;
        capture->read(background);
        resize(background, background, Size(640, 480));
    }

    if (key == ' ') {
        record = !record;
        if (record) {
            char name[100];
            sprintf(name, (AppConfig::outputDir + "/camera_%li.avi").c_str(), time(0));
            printf("Recording to file %s started\n", name);
            writer->open(name, CV_FOURCC('M', 'J', 'P', 'G'), 10.0, Size(640 + 320, 480), true);
        } else {
            printf("Recording ended\n");
            writer->release();
        }
    }
}

cv::Mat const &Window5::getResult() const {
    return result;
}

int Window5::getBlurRadius() const {
    return blurRadius;
}

void Window5::setBlurRadius(int blurRadius) {
    if (blurRadius >= 0) {
        this->blurRadius = blurRadius;
        setTrackbarPos("Blur radius", getTitle(), blurRadius);
    }
}

int Window5::getThresholdMin() const {
    return thresholdMin;
}

void Window5::setThresholdMin(int thresholdMin) {
    if (thresholdMin >= 0 && thresholdMin <= 255) {
        Window5::thresholdMin = thresholdMin;
        cv::setTrackbarPos("Threshold - min", getTitle(), thresholdMin);
    }
}