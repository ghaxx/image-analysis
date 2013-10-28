//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include <opencv2/highgui/highgui.hpp>
#include "TransformVideo.h"
#include <unistd.h>

using namespace cv;

TransformVideo::TransformVideo(Transformation *transformation, char const *source, char const *dest):transformation(transformation), source(source), dest(dest) {
    double t = (double) getTickCount();

    Mat frame;
    VideoCapture capture(source);

    double width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    double height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
    double fps = capture.get(CV_CAP_PROP_FPS);
    int fourcc = (int) capture.get(CV_CAP_PROP_FOURCC);
    fourcc = 0;
    printf("fourcc: %d\n", fourcc);

    VideoWriter writer(dest, fourcc, fps, Size(width, height), true);

    vector<int> params;
    params.push_back(CV_IMWRITE_JPEG_QUALITY);
    params.push_back(80);

    cv::Mat transformed;
    while (capture.get(CV_CAP_PROP_POS_FRAMES) < capture.get(CV_CAP_PROP_FRAME_COUNT)) {
        capture.read(transformed);
        printf("%f/%f\r", capture.get(CV_CAP_PROP_POS_FRAMES), capture.get(CV_CAP_PROP_FRAME_COUNT));

        transformed = transformation->transform(transformed);

        writer.write(transformed);
    }
    writer.release();
    t = ((double) getTickCount() - t) / getTickFrequency();
    printf("Sharpened in %.3fs\n", t);
}