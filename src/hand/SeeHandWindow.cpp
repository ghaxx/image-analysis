//
// Created by Kuba Sławiński on 01/11/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "SeeHandWindow.h"
#include "AppConfig.h"

const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS = 50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 20 * 20;
const int MAX_OBJECT_AREA = FRAME_HEIGHT * FRAME_WIDTH / 1.5;

using namespace cv;
int x = 0, y = 0;

void SeeHandWindow::findObjects(Mat &thresh) {
    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle

    cv::GaussianBlur(thresh, thresh, cv::Size(0, 0), blurRadius);
//    cv::GaussianBlur(thresh, thresh, cv::Size(0, 0), blurRadius);
    threshold(thresh, thresh, 0, 255, CV_THRESH_BINARY | THRESH_OTSU);

    //dilate with larger element so make sure object is nicely visible

    Mat erodeElement = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    erode(thresh, thresh, erodeElement);
    erode(thresh, thresh, erodeElement);

    Mat dilateElement = getStructuringElement(MORPH_ELLIPSE, Size(6, 6));
    dilate(thresh, thresh, dilateElement);
    dilate(thresh, thresh, dilateElement);
}

string intToString(int number) {


    std::stringstream ss;
    ss << number;
    return ss.str();
}

void addAlphaMat(Mat &src, Mat &dst, double alpha) {
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

void addAlphaMat(Mat &src, Mat &dst) {
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

void drawObject(int x, int y, Mat &frame) {

    //use some of the openCV drawing functions to draw crosshairs
    //on your tracked image!

    //UPDATE:JUNE 18TH, 2013
    //added 'if' and 'else' statements to prevent
    //memory errors from writing off the screen (ie. (-25,-25) is not within the window!)

    circle(frame, Point(x, y), 20, Scalar(0, 255, 0), 1);
    if (y - 25 > 0)
        line(frame, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 1);
    else line(frame, Point(x, y), Point(x, 0), Scalar(0, 255, 0), 2);
    if (y + 25 < FRAME_HEIGHT)
        line(frame, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 1);
    else line(frame, Point(x, y), Point(x, FRAME_HEIGHT), Scalar(0, 255, 0), 1);
    if (x - 25 > 0)
        line(frame, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 1);
    else line(frame, Point(x, y), Point(0, y), Scalar(0, 255, 0), 1);
    if (x + 25 < FRAME_WIDTH)
        line(frame, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 1);
    else line(frame, Point(x, y), Point(FRAME_WIDTH, y), Scalar(0, 255, 0), 1);

//    putText(frame, intToString(x) + "," + intToString(y), Point(x, y + 30), CV_FONT_NORMAL, 0.2, Scalar(0, 255, 0), 2);
}

void findCenterOfObjects(vector< vector<Point> > contours, vector<Vec4i> hierarchy, Mat &dest) {
    double refArea = 0;
    bool objectFound = false;
    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if (numObjects < MAX_NUM_OBJECTS) {
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat) contours[index]);
                double area = moment.m00;

                //if the area is less than 20 px by 20px then it is probably just noise
                //if the area is the same as the 3/2 of the image size, probably just a bad filter
                //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                if (area > MIN_OBJECT_AREA && area < MAX_OBJECT_AREA && area > refArea) {
                    x = moment.m10 / area;
                    y = moment.m01 / area;
                    objectFound = true;
                    refArea = area;
                } else objectFound = false;

                if (objectFound == true) {
                    //draw object location on screen
                    drawObject(x, y, dest);
                }
            }

        }
    }
}

void findFingers(vector<vector<Point> > contours, vector<Vec4i> hierarchy, Mat &dest, int x, int y) {

}

void findCenterOfMaxObject(vector< vector<Point> > contours, vector<Vec4i> hierarchy, Mat &dest) {
    double refArea = 0;
    int x = 0;
    int y = 0;
    for (int i = 0; i < contours.size(); i++) {
        Moments moment = moments((cv::Mat) contours[i]);
        double area = moment.m00;
        if (area > refArea) {
            x = (int) (moment.m10 / area);
            y = (int) (moment.m01 / area);
            refArea = area;
        }
    }

    if (refArea != 0) {
        drawObject(x, y, dest);
        findFingers(contours, hierarchy, dest, x, y);
    }
}

void addBoundingBoxes(vector< vector<Point> > contours, vector<Vec4i> hierarchy, Mat &dest) {
    /// Approximate contours to polygons + get bounding rects and circles
    vector<vector<Point> > contours_poly(contours.size());
    Rect boundRect;
    Point2f center;
    float radius;

    Mat drawing = Mat::zeros(dest.size(), CV_8UC3);
    double refArea = 0;
    for (int i = 0; i >= 0; i = hierarchy[i][0]) {
        if (hierarchy[i][3] > -1)
            continue;
//    for (int i = 0; i < contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
        boundRect = boundingRect(Mat(contours_poly[i]));
        minEnclosingCircle((Mat) contours_poly[i], center, radius);
//        }
//        Moments moment = moments((cv::Mat) contours[i]);
//        double area = moment.m00;
//        if (area > MIN_OBJECT_AREA && area > refArea) {
//            x = moment.m10 / area;
//            y = moment.m01 / area;
        rectangle(drawing, boundRect.tl(), boundRect.br(), Scalar(200, 255, 255), 1, 8, 0);
        circle(drawing, center, (int) radius, Scalar(255, 255, 200), 1, 8, 0);
//            refArea = area;
//        }
    }

    addWeighted(drawing, 1, dest, 1, 1, dest); // add contours to color image
}

void addMaxBoundingBox(vector< vector<Point> > contours, vector<Vec4i> hierarchy, Mat &dest) {
    /// Approximate contours to polygons + get bounding rects and circles
    vector<Point> contours_poly;
    Rect boundRect;
    Point2f center;
    float radius;

    Mat drawing = Mat::zeros(dest.size(), CV_8UC3);
    double refArea = 0;
    int max = 0;
//    for (int i = 0; i >= 0; i = hierarchy[i][0]) {
    for (int i = 0; i < contours.size(); i++) {
        Moments moment = moments((cv::Mat) contours[i]);
        double area = moment.m00;
        if (area > refArea) {
            refArea = area;
            max = i;
        }
    }
    approxPolyDP(Mat(contours[max]), contours_poly, 3, true);
    boundRect = boundingRect(Mat(contours_poly));
    minEnclosingCircle((Mat) contours_poly, center, radius);
    drawObject(center.x, center.y, dest);
    rectangle(drawing, boundRect.tl(), boundRect.br(), Scalar(100, 255, 255), 1, 8, 0);
    circle(drawing, center, (int) radius, Scalar(255, 255, 100), 1, 8, 0);

//    addWeighted(drawing, 0.2, dest, 1, 1, dest); // add contours to color image
    addAlphaMat(drawing, dest, 0.4);
}

void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed) {

    Mat temp;
    threshold.copyTo(temp);
    //these two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    Mat drawing = Mat::zeros(threshold.size(), CV_8UC3);
//    for (int i = 0; i < contours.size(); i++) {
    for (int i = 0; i >= 0; i = hierarchy[i][0]) {
        Scalar color = Scalar(0, 0, 255);
        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
    }
    addWeighted(drawing, 1, cameraFeed, 1, 1, cameraFeed); // add contours to color image

    //use moments method to find our filtered object
    findCenterOfObjects(contours, hierarchy, cameraFeed);
}

void pictureInPicture(Mat &source, Mat &destination, int x, int y, int w, int h) {
    Mat small;
    resize(source, small, Size(w, h));
    Mat subView = destination(Rect(x, y, small.cols, small.rows));
    if (small.type() != destination.type())
        cvtColor(small, small, CV_GRAY2RGB);
    small.copyTo(subView);
}

void findHull(vector<vector<Point> > contours, vector<Vec4i> hierarchy, Mat &dest) {
    vector<vector<Point> > hull(contours.size());
    for (int i = 0; i >= 0; i = hierarchy[i][0]) {convexHull(Mat(contours[i]), hull[i], false);}

    Mat drawing = Mat::zeros(dest.size(), CV_8UC3);
    for (int i = 0; i >= 0; i = hierarchy[i][0]) {
        Scalar color = Scalar(255, 200, 200);
        drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
    }

    addWeighted(drawing, 1, dest, 1, 1, dest); // add contours to color image
}

bool sortConvDef(Vec4i &p1, Vec4i &p2) {
    return p1[3] > p2[3];
}

void findMaxHull(vector<vector<Point> > contours, vector<Vec4i> hierarchy, Mat &dest) {
    vector<vector<Point> > hull(1);
    cv::vector<cv::vector<int> > hull_i(1);

    Mat drawing = Mat::zeros(dest.size(), CV_8UC3);
    int max = 0;
    double maxArea = 0;
    for (int i = 0; i < contours.size(); i++) {
        Moments moment = moments((cv::Mat) contours[i]);
        double area = moment.m00;
        if (area > maxArea) {
            maxArea = area;
            max = i;
        }
    }
    convexHull(Mat(contours[max]), hull[0], false);
    convexHull(Mat(contours[max]), hull_i[0], false);
    drawContours(drawing, hull, 0, Scalar(1, 1, 50), 2, 8, vector<Vec4i>(), 0, Point());
    drawContours(drawing, hull, 0, Scalar(20, 20, 200), 1, 8, vector<Vec4i>(), 0, Point());


    std::vector<Vec4i> convDef;
    vector< vector<Point> > hull_points(1);
    vector< vector<Point> > defect_points(1);

    if (hull_i[0].size() > 3)
        convexityDefects(contours[max], hull_i[0], convDef);

    int max4[convDef.size()];
    int max4p[convDef.size()];
    for (int k = 0; k < convDef.size(); k++) {
        int ind_0 = convDef[k][0];
        int ind_1 = convDef[k][1];
        int ind_2 = convDef[k][2];
        max4[k] = convDef[k][3];
        max4p[k] = convDef[k][2];
        cv::line(drawing, contours[max][ind_2], contours[max][ind_0], Scalar(1, 0, 25), 2);
        cv::line(drawing, contours[max][ind_2], contours[max][ind_0], Scalar(1, 0, 255), 1);
        cv::line(drawing, contours[max][ind_2], contours[max][ind_1], Scalar(1, 0, 25), 2);
        cv::line(drawing, contours[max][ind_2], contours[max][ind_1], Scalar(1, 0, 255), 1);
        cv::circle(drawing, contours[max][ind_0], 7, Scalar(1, 25, 0), -1);
        cv::circle(drawing, contours[max][ind_1], 7, Scalar(1, 25, 0), -1);
        cv::circle(drawing, contours[max][ind_2], 7, Scalar(1, 0, 25), -1);
        cv::circle(drawing, contours[max][ind_0], 5, Scalar(1, 255, 0), -1);
        cv::circle(drawing, contours[max][ind_1], 5, Scalar(1, 255, 0), -1);
        cv::circle(drawing, contours[max][ind_2], 5, Scalar(1, 0, 255), -1);
    }
    std::sort(convDef.begin(), convDef.end(), sortConvDef);
    int maxc = 0;
    for (int k = 0; k < 4; k++) {
        int ind_0 = convDef[k][0];
        int ind_1 = convDef[k][1];
        int ind_2 = convDef[k][2];
        cv::circle(drawing, contours[max][ind_0], 11, Scalar(1, 255, 25), -1);
        cv::circle(drawing, contours[max][ind_0], 9, Scalar(1, 255, 255), -1);
        cv::circle(drawing, contours[max][ind_2], 11, Scalar(1, 255, 25), -1);
        cv::circle(drawing, contours[max][ind_2], 9, Scalar(1, 255, 255), -1);
        if (ind_1 > maxc)
            maxc = ind_1;
    }
    cv::circle(drawing, contours[max][maxc], 11, Scalar(1, 255, 25), -1);
    cv::circle(drawing, contours[max][maxc], 9, Scalar(1, 255, 255), -1);


    addAlphaMat(drawing, dest, 0.4);
}


void addContours(Mat source, Mat &dest) {
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using canny
    Canny(source, canny_output, 10, 100 * 2, 3);
    /// Find contours
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//    findContours(source, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    /// Draw contours
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (int i = 0; i < contours.size(); i++) {
        drawContours(drawing, contours, i, Scalar(2, 20, 2), 2, 8, hierarchy, 0, Point());
        drawContours(drawing, contours, i, Scalar(20, 240, 20), 1, 8, hierarchy, 0, Point());
    }
//    addWeighted(drawing, 0.8, dest, 1, 1, dest); // add contours to color image
    addAlphaMat(drawing, dest, 0.4);

    findCenterOfMaxObject(contours, hierarchy, dest);
    findMaxHull(contours, hierarchy, dest);
    addMaxBoundingBox(contours, hierarchy, dest);
}

void SeeHandWindow::show() {
    try {
        result = Mat::zeros(480, 640 + 320, image.type());
//        capture->read(image);
//        flip(image, image, 2);
        image = imread(AppConfig::inputDir + "/h.jpg", CV_LOAD_IMAGE_COLOR);
        Mat hsv;
        Mat thresholdMat;
        cvtColor(image, hsv, CV_RGB2HSV);

        inRange(hsv, Scalar(minHue, 0, 0), Scalar(maxHue, 255, 255), thresholdMat);

        pictureInPicture(thresholdMat, result, 0, 240, 320, 240);

        if (morph) {
            findObjects(thresholdMat);
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
//        result.release();
        hsv.release();
    } catch(...) {}
}

void onMouse(int event, int x, int y, int c, void *p) {
//    printf("%dx%d - %d\n", x, y, event);
    SeeHandWindow *w = (SeeHandWindow *) p;
    Mat image = w->getResult();
    if (event == 1) { //click
        cvtColor(image, image, CV_RGB2HSV);
        int h = (int) image.at<Vec3b>(y, x)[0];
        w->setMinHue(h);
        w->setMaxHue(h);
    }
}


SeeHandWindow::SeeHandWindow(std::string title):DisplayWindow(title) {
    capture = SynchronizedVideoCapture::getInstance();
    image = imread("/Users/ghaxx/h.jpg", CV_LOAD_IMAGE_COLOR);
    writer = new VideoWriter();

    result = Mat::zeros(480, 640 + 320, 16);

    record = false;
//    minHue = 10;
//    maxHue = 20;
    minHue = 102;
    maxHue = 103;
    morph = true;
    blurRadius = 5;

    createTrackbar("Hue - min", title, &minHue, 180);
    createTrackbar("Hue - max", title, &maxHue, 180);
    createTrackbar("Blur radius", title, &blurRadius, 30);
    setMouseCallback(title.c_str(), onMouse, this);
}

SeeHandWindow::~SeeHandWindow() {
}

void SeeHandWindow::control(char key) {
    if (key == 'w') setMinHue(minHue + 1);
    if (key == 's') setMinHue(minHue - 1);

    if (key == 'e') setMaxHue(maxHue + 1);
    if (key == 'd') setMaxHue(maxHue - 1);

    if (key == 'r') setBlurRadius(blurRadius + 1);
    if (key == 'f') setBlurRadius(blurRadius - 1);

    if (key == 'm') morph = !morph;

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

    if (key != '\xff')
        printf("Hue: %d - %d, Blur: %d, Morph: %s\r", minHue, maxHue, blurRadius, morph ? "yes" : "no");
}

cv::Mat const &SeeHandWindow::getResult() const {
    return result;
}

int SeeHandWindow::getMinHue() const {
    return minHue;
}

void SeeHandWindow::setMinHue(int minHue) {
    this->minHue = minHue;
    setTrackbarPos("Hue - min", getTitle(), minHue);
}

int SeeHandWindow::getMaxHue() const {
    return maxHue;
}

void SeeHandWindow::setMaxHue(int maxHue) {
    this->maxHue = maxHue;
    setTrackbarPos("Hue - max", getTitle(), maxHue);
}

int SeeHandWindow::getBlurRadius() const {
    return blurRadius;
}

void SeeHandWindow::setBlurRadius(int blurRadius) {
    if (blurRadius > 0) {
        this->blurRadius = blurRadius;
        setTrackbarPos("Blur radius", getTitle(), blurRadius);
    }
}