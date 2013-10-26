//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include <opencv2/highgui/highgui.hpp>
#include "TransformVideo.h"
#include <unistd.h>

using namespace cv;

TransformVideo::TransformVideo(int number, Transformation **transformations, char const *source, char const *dest):number(number), transformations(transformations), source(source), dest(dest) {
    double t = (double)getTickCount();

    Mat frame;
    VideoCapture capture(source);

    double width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    double height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
    double fps = capture.get(CV_CAP_PROP_FPS);
    int fourcc = (int)capture.get(CV_CAP_PROP_FOURCC);
    printf("fourcc: %d\n", fourcc);

    VideoWriter writer(dest, fourcc, fps, Size(width, height), true);
//    writer.open(dest, fourcc, fps, Size(width, height), true);

        vector<int> params;
        params.push_back(CV_IMWRITE_JPEG_QUALITY);
        params.push_back(80);
    cv::Mat transformed;
    while(capture.get(CV_CAP_PROP_POS_FRAMES) < capture.get(CV_CAP_PROP_FRAME_COUNT)) {
        capture.read(transformed);
        printf("%f/%f\r", capture.get(CV_CAP_PROP_POS_FRAMES), capture.get(CV_CAP_PROP_FRAME_COUNT));

        for (int i = 0; i < number; i++) {
            transformed = transformations[i]->transform(transformed);
        }

        char name[100];
        sprintf(name, "/Users/ghaxx/img/capture_%f.jpg", capture.get(CV_CAP_PROP_POS_FRAMES));
        imwrite(name, transformed, params);
        writer.write(transformed);

    }
    writer.release();
//    char a[300];
//    sprintf(a, "/usr/local/bin/ffmpeg -y -r 25 -q:v 2 -i /Users/ghaxx/img/capture_%%d.000000.jpg %s", dest);
//    system(a);
    t = ((double)getTickCount() - t)/getTickFrequency();
    printf("Sharpened in %fs\n", t);
}