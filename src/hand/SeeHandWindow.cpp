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
    Mat erodeElement = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));

    cv::GaussianBlur(thresh, thresh, cv::Size(0, 0), blurRadius);
    threshold(thresh, thresh, 0, 255, CV_THRESH_BINARY | THRESH_OTSU);

    //dilate with larger element so make sure object is nicely visible
//    Mat dilateElement = getStructuringElement(MORPH_ELLIPSE, Size(9, 9));

//    erode(thresh, thresh, erodeElement);
//    erode(thresh, thresh, erodeElement);


//    dilate(thresh, thresh, dilateElement);
//    dilate(thresh, thresh, dilateElement);
}

string intToString(int number) {


    std::stringstream ss;
    ss << number;
    return ss.str();
}

void drawObject(int x, int y, Mat &frame) {

    //use some of the openCV drawing functions to draw crosshairs
    //on your tracked image!

    //UPDATE:JUNE 18TH, 2013
    //added 'if' and 'else' statements to prevent
    //memory errors from writing off the screen (ie. (-25,-25) is not within the window!)

    circle(frame, Point(x, y), 20, Scalar(0, 255, 0), 2);
    if (y - 25 > 0)
        line(frame, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
    else line(frame, Point(x, y), Point(x, 0), Scalar(0, 255, 0), 2);
    if (y + 25 < FRAME_HEIGHT)
        line(frame, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
    else line(frame, Point(x, y), Point(x, FRAME_HEIGHT), Scalar(0, 255, 0), 2);
    if (x - 25 > 0)
        line(frame, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
    else line(frame, Point(x, y), Point(0, y), Scalar(0, 255, 0), 2);
    if (x + 25 < FRAME_WIDTH)
        line(frame, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);
    else line(frame, Point(x, y), Point(FRAME_WIDTH, y), Scalar(0, 255, 0), 2);

    putText(frame, intToString(x) + "," + intToString(y), Point(x, y + 30), 1, 1, Scalar(0, 255, 0), 2);

}

void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed) {

    Mat temp;
    threshold.copyTo(temp);
    //these two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
    //use moments method to find our filtered object
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


            }
            //let user know you found an object
            if (objectFound == true) {
                putText(cameraFeed, "Tracking Object", Point(0, 50), 2, 1, Scalar(0, 255, 0), 2);
                //draw object location on screen
                drawObject(x, y, cameraFeed);
            }

        } else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
    }
}

void pictureInPicture(Mat &source, Mat &destination, int x, int y, int w, int h) {
    Mat small;
    resize(source, small, Size(w, h));
    Mat subView = destination(Rect(x, y, small.cols, small.rows));
    if (small.type() != destination.type())
        cvtColor(small, small, CV_GRAY2RGB);
    small.copyTo(subView);
}

void SeeHandWindow::show() {
    try {
        capture->read(image);
        Mat result = Mat::zeros(480, 640 + 320, image.type());
        Mat hsv;
        Mat thresholdMat;
        cvtColor(image, hsv, CV_RGB2HSV);

        inRange(hsv, Scalar(minHue, 0, 0), Scalar(maxHue, 255, 255), thresholdMat);

        pictureInPicture(thresholdMat, result, 0, 240, 320, 240);

        if (morph) {
            findObjects(thresholdMat);
        }

        trackFilteredObject(x, y, thresholdMat, image);

        pictureInPicture(image, result, 0, 0, 320, 240);
        pictureInPicture(thresholdMat, result, 320, 0, 640, 480);


        if (record) {
            writer->write(result);
        }
        imshow(getTitle(), result);

        thresholdMat.release();
        result.release();
        hsv.release();
    } catch(...) {}
}

SeeHandWindow::SeeHandWindow(std::string title):DisplayWindow(title) {
    capture = SynchronizedVideoCapture::getInstance();
    writer = new VideoWriter();
    record = false;
//    minHue = 10;
//    maxHue = 20;
    minHue = 106;
    maxHue = 122;
    morph = true;
    blurRadius = 5;
}

SeeHandWindow::~SeeHandWindow() {
}

void SeeHandWindow::control(char key) {
    if (key == 'w') minHue++;
    if (key == 's') minHue--;

    if (key == 'e') maxHue++;
    if (key == 'd') maxHue--;

    if (key == 'r') blurRadius++;
    if (key == 'f') blurRadius = max(blurRadius - 1, 1);

    if (key == 'm') morph = !morph;

    if (key == ' ') {
        record = !record;
        if (record) {
            char name[100];
            sprintf(name, (AppConfig::outputDir + "/camera_%li.avi").c_str(), time(0));
            printf("Recording to file %s started\n", name);
            writer->open(name, 0, 15.0, Size(640 + 320, 480), true);
        } else {
            printf("Recording ended\n");
            writer->release();
        }
    }

    if (key != '\xff')
        printf("Hue: %d - %d, Blur: %d, Morph: %s\r", minHue, maxHue, blurRadius, morph ? "yes" : "no");
}
