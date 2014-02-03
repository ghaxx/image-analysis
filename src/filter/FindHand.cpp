//
// Created by Kuba Sławiński on 25/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include "FindHand.h"
#include "Util.h"

using namespace cv;

// From image to black and white
void FindHand::extractShapesInBinary(Mat &image, Mat &thresh) {
    Mat hsv;
    cvtColor(image, hsv, CV_RGB2HSV);
    inRange(hsv, Scalar(minHue, minSaturation, minValue), Scalar(maxHue, maxSaturation, maxValue), thresh);
    Util::pictureInPicture(thresh, result, 0, rows / 2, cols / 2, rows / 2);

    if (blurRadius > 0) {
//        GaussianBlur(thresh, thresh, cv::Size(0, 0), 9);
//        addWeighted(thresh, 1.5, thresh, -0.5, 0, thresh);
//        GaussianBlur(thresh, thresh, cv::Size(0, 0), 9);
//        addWeighted(thresh, 1.5, thresh, -0.5, 0, thresh);

        GaussianBlur(thresh, thresh, cv::Size(0, 0), blurRadius);
    }
    threshold(thresh, thresh, 0, 255, CV_THRESH_BINARY | THRESH_OTSU);

    //dilate with larger element so make sure object is nicely visible

    Mat erodeElement = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    erode(thresh, thresh, erodeElement, Point(-1, -1), 3);

    Mat dilateElement = getStructuringElement(MORPH_ELLIPSE, Size(6, 6));
    dilate(thresh, thresh, dilateElement, Point(-1, -1), 1);

    morphologyEx(thresh, thresh, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(7, 7)));
}

void FindHand::drawObject(int x, int y, Mat &frame) {
    circle(frame, Point(x, y), 10, Scalar(0, 255, 0), 1);
    if (y - 25 > 0)
        line(frame, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 1);
    else line(frame, Point(x, y), Point(x, 0), Scalar(0, 255, 0), 2);
    if (y + 25 < rows)
        line(frame, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 1);
    else line(frame, Point(x, y), Point(x, rows), Scalar(0, 255, 0), 1);
    if (x - 25 > 0)
        line(frame, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 1);
    else line(frame, Point(x, y), Point(0, y), Scalar(0, 255, 0), 1);
    if (x + 25 < cols)
        line(frame, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 1);
    else line(frame, Point(x, y), Point(cols, y), Scalar(0, 255, 0), 1);

//    putText(frame, intToString(x) + "," + intToString(y), Point(x, y + 30), CV_FONT_NORMAL, 0.2, Scalar(0, 255, 0), 2);
}

void FindHand::findCenterOfObject(vector<Point> &contour, Mat &dest) {
    double refArea = 0;

    Moments moment = moments((Mat) contour);
    double area = moment.m00;
    center_x = (int) (moment.m10 / area);
    center_y = (int) (moment.m01 / area);

    center.x = center_x;
    center.y = center_y;

    if (drawAll) {
        circle(dest, center, 10, Scalar(100, 0, 0), -1);
        circle(dest, center, 10, Scalar(250, 150, 150), -1);
//        drawObject(center_x, center_y, dest);
    }
}

void FindHand::addBoundingBox(vector<Point> &contour, Mat &dest) {
    /// Approximate contours to polygons + get bounding rects and circles
    vector<Point> contours_poly;
    Rect boundRect;
    Point2f center;
    float radius;

    Mat drawing = Mat::zeros(dest.size(), CV_8UC3);

    approxPolyDP(Mat(contour), contours_poly, 3, true);
    boundRect = boundingRect(Mat(contours_poly));
    minEnclosingCircle((Mat) contours_poly, center, radius);
//    drawObject(center.x, center.y, dest);
    rectangle(drawing, boundRect.tl(), boundRect.br(), Scalar(100, 255, 255), 1, 8, 0);
    circle(drawing, center, (int) radius, Scalar(255, 255, 100), 1, 8, 0);

    RotatedRect box = minAreaRect(contour);
    Point2f vertices[4];
    box.points(vertices);
    for (int i = 0; i < 4; ++i)
        cv::line(drawing, vertices[i], vertices[(i + 1) % 4], cv::Scalar(255, 100, 100), 1, 0);


    Util::addAlphaMat(drawing, dest, 0.4);
}

bool FindHand::sortConvDef(Vec4i &p1, Vec4i &p2) {
    return p1[3] > p2[3];
}

void FindHand::findHull(vector<Point> &contour, Mat &dest) {
    vector<vector<Point> > hull(1);
    cv::vector<cv::vector<int> > hull_i(1);

    Mat drawing = Mat::zeros(dest.size(), CV_8UC3);

    convexHull(Mat(contour), hull[0], false);
    convexHull(Mat(contour), hull_i[0], false);
    if (drawAll) {
        drawContours(drawing, hull, 0, Scalar(5, 5, 20), 2, 8, vector<Vec4i>(), 0, Point());
        drawContours(drawing, hull, 0, Scalar(200, 200, 255), 1, 8, vector<Vec4i>(), 0, Point());
    }
    Util::addAlphaMat(drawing, dest, 0.7);
    drawing = Mat::zeros(dest.size(), CV_8UC3);

    std::vector<Vec4i> convDef;
    if (hull_i[0].size() > 0) {
        convexityDefects(contour, hull_i[0], convDef);
        float minDistance = shapeRadius * handScale / 100;
        int fingertipRadius = 0.1 * shapeRadius;
//        if (convDef.size() > 0)
            for (int k = 0; k < convDef.size(); k++) {
                if (convDef[k][3] > shapeRadius * 0.77) {
                    int ind_0 = convDef[k][0];
                    int ind_1 = convDef[k][1];
                    int ind_2 = convDef[k][2];
                    int widthsDebug[2] = {8, 7};
                    int widths[2] = {2, 1};
                    Scalar colors[2] = {Scalar(1, 25, 5), Scalar(200, 255, 200)};
                    for (int i = 0; i < 2; i++) {
                        if (drawAll) {
                            if (Util::distance(center, contour[ind_0]) > minDistance)
                                cv::line(drawing, contour[ind_2], contour[ind_0], colors[i], widths[i]);
                            if (Util::distance(center, contour[ind_1]) > minDistance)
                                cv::line(drawing, contour[ind_2], contour[ind_1], colors[i], widths[i]);
                        }
                        if (Util::distance(center, contour[ind_0]) > minDistance)
                            cv::line(drawing, contour[ind_0], Point(center_x, center_y), colors[i], widths[i]);
                        if (Util::distance(center, contour[ind_1]) > minDistance)
                            cv::line(drawing, contour[ind_1], Point(center_x, center_y), colors[i], widths[i]);
                    }
                    if (!drawAll) {
                        circle(drawing, contour[ind_0], fingertipRadius, Scalar(0, 0, 0), -1);
                        circle(drawing, contour[ind_1], fingertipRadius, Scalar(0, 0, 0), -1);
                    }
                    for (int i = 0; i < 2; i++) {
                        if (drawAll) {
                            circle(drawing, contour[ind_0], widthsDebug[i], colors[i], -1);
                            circle(drawing, contour[ind_1], widthsDebug[i], colors[i], -1);
                            circle(drawing, contour[ind_2], widthsDebug[i], colors[i], -1);
                        }
                        if (Util::distance(center, contour[ind_0]) > minDistance)
                            circle(drawing, contour[ind_0], fingertipRadius, colors[i], widths[i]);
                        if (Util::distance(center, contour[ind_1]) > minDistance)
                            circle(drawing, contour[ind_1], fingertipRadius, colors[i], widths[i]);
                    }
                }
//            if (ind_1 > maxc)
//                maxc = ind_1;
            }
//        cv::circle(drawing, contour[maxc], 11, Scalar(1, 255, 25), -1);
//        cv::circle(drawing, contour[maxc], 9, Scalar(1, 255, 255), -1);
    }
    Util::addAlphaMat(drawing, dest, 0.7);
}


void FindHand::addContours(Mat &source, Mat &dest) {
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using canny
    Canny(source, canny_output, 10, 100 * 2, 3);
    findContours(canny_output, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

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
//        if (&(contours[i]) != 0) {
//            drawContours(drawing, contours, i, Scalar(20, rows / 2, 20), 1, 8, hierarchy, 0, Point());
//            drawContours(drawing, contours, i, Scalar(2, 20, 2), 2, 8, hierarchy, 0, Point());
//            Util::addAlphaMat(drawing, dest, 0.4);
//
//            findCenterOfObject(contours[i], dest);
//            findHull(contours[i], dest);
////            addBoundingBox(contours[max], dest);
//        }
    }
    if (&(contours[max]) != 0) {

        Mat drawing = Mat::zeros(dest.size(), CV_8UC3);
        Point2f center;

        minEnclosingCircle((Mat) contours[max], center, shapeRadius);
//        cvApproxPoly(contours[max], 0, <#(CvMemStorage*)storage#>, <#(int)method#>, <#(double)eps#>, <#(int)recursive#>)
        approxPolyDP(contours[max], contours[max], shapeRadius / 6, true);
        if (drawAll) {
            drawContours(drawing, contours, max, Scalar(2, 20, 2), 2, 8, hierarchy, 0, Point());
            drawContours(drawing, contours, max, Scalar(200, 255, 200), 1, 8, hierarchy, 0, Point());
        }
        Util::addAlphaMat(drawing, dest, 0.7);

        findCenterOfObject(contours[max], dest);
        findHull(contours[max], dest);
        if (drawAll)
            addBoundingBox(contours[max], dest);
    }
}

Mat FindHand::transform(Mat image) {
    cols = image.cols;
    rows = image.rows;
    result = Mat::zeros(image.rows, image.cols * 3 / 2, image.type());
//    result = image.clone();
    Scalar color = Scalar(0, 0, 0);
//        image = imread(AppConfig::inputDir + "/h.jpg", CV_LOAD_IMAGE_COLOR);
//    image = motionDetection->transform(image);

    Mat thresholdMat;

    extractShapesInBinary(image, thresholdMat);

    Util::resizeCanvas(image, image, 10, color);
    Util::resizeCanvas(thresholdMat, thresholdMat, 10, color);

    addContours(thresholdMat, image);

    Util::pictureInPicture(thresholdMat, result, 0, 0, cols / 2, rows / 2, 10, 10, cols, rows);
    Util::pictureInPicture(image, result, cols / 2, 0, cols, rows, 10, 10, cols, rows);

    thresholdMat.release();
    return result;
//    return this->image;
}

void onMouse(int event, int x, int y, int c, void *p) {
    FindHand *w = (FindHand *) p;
    Mat image = w->getResult();
    if (event == 1) { //click
        cvtColor(image, image, CV_RGB2HSV);
        int h = (int) image.at<Vec3b>(y, x)[0];
        int s = (int) image.at<Vec3b>(y, x)[1];
        int v = (int) image.at<Vec3b>(y, x)[2];
        w->setMinHue(h - 4);
        w->setMaxHue(h + 4);
//        w->setMinSaturation(s - 10);
//        w->setMaxSaturation(s + 10);
//        w->setMinValue(v - 10);
//        w->setMaxValue(v + 10);
    }
}


FindHand::FindHand() {
    record = false;
    minHue = 99;
    maxHue = 125;
    minSaturation = 0;
    maxSaturation = 255;
    minValue = 0;
    maxValue = 255;

    blurRadius = 5;
    approxPolyEpsilon = 15.0;
    drawAll = false;
    handScale = 87;

    motionDetection = new OpticalFlowMotionDetection();
}

void FindHand::createControls(const std::string &windowTitle) {
    string suffix = " - controls";
    namedWindow(windowTitle + suffix);
    imshow(windowTitle + suffix, Mat::zeros(1, 500, CV_8UC1));

    createTrackbar("Hue - min", windowTitle + suffix, &minHue, 180);
    createTrackbar("Hue - max", windowTitle + suffix, &maxHue, 180);

    createTrackbar("saturation - min", windowTitle + suffix, &minSaturation, 255);
    createTrackbar("saturation - max", windowTitle + suffix, &maxSaturation, 255);

    createTrackbar("value - min", windowTitle + suffix, &minValue, 255);
    createTrackbar("value - max", windowTitle + suffix, &maxValue, 255);

    createTrackbar("Blur radius", windowTitle + suffix, &blurRadius, 30);
    createTrackbar("Draw all?", windowTitle + suffix, &drawAll, 1);
    createTrackbar("Hand scale", windowTitle + suffix, &handScale, 100);
    setMouseCallback(windowTitle, onMouse, this);
    motionDetection->createControls(windowTitle);

    title = windowTitle + suffix;
}

cv::Mat const &FindHand::getResult() const {
    return result;
}

int FindHand::getMinHue() const {
    return minHue;
}

void FindHand::setMinHue(int minHue) {
    this->minHue = min(255, max(0, minHue));
    setTrackbarPos("Hue - min", getTitle(), this->minHue);
}

int FindHand::getMaxHue() const {
    return maxHue;
}

void FindHand::setMaxHue(int maxHue) {
    this->maxHue = min(255, max(0, maxHue));
    setTrackbarPos("Hue - max", getTitle(), this->maxHue);
}

int FindHand::getBlurRadius() const {
    return blurRadius;
}

void FindHand::setBlurRadius(int blurRadius) {
    if (blurRadius >= 0) {
        this->blurRadius = blurRadius;
        setTrackbarPos("Blur radius", getTitle(), blurRadius);
    }
}

std::string FindHand::getTitle() {
    return title;
}

int FindHand::getMinSaturation() const {
    return minSaturation;
}

void FindHand::setMinSaturation(int minSaturation) {
    this->minSaturation = min(255, max(0, minSaturation));
    setTrackbarPos("saturation - min", getTitle(), this->minSaturation);
}

int FindHand::getMaxSaturation() const {
    return maxSaturation;
}

void FindHand::setMaxSaturation(int maxSaturation) {
    this->maxSaturation = min(255, max(0, maxSaturation));
    setTrackbarPos("saturation - max", getTitle(), this->maxSaturation);
}

int FindHand::getMinValue() const {
    return minValue;
}

void FindHand::setMinValue(int minValue) {
    this->minValue = min(255, max(0, minValue));
    setTrackbarPos("value - min", getTitle(), this->minValue);
}

int FindHand::getMaxValue() const {
    return maxValue;
}

void FindHand::setMaxValue(int maxValue) {
    this->maxValue = min(255, max(0, maxValue));
    setTrackbarPos("max - value", getTitle(), this->maxValue);
}