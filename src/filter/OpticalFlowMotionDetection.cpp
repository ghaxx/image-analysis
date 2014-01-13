//
// Created by Kuba Sławiński on 12/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include "OpticalFlowMotionDetection.h"

using namespace std;
using namespace cv;


OpticalFlowMotionDetection::OpticalFlowMotionDetection() {
    maxCorners = 8;
    qualityLevel = 0.0001;
    minDistance = 1;
	found = 0;
}

cv::Mat OpticalFlowMotionDetection::transform(cv::Mat image) {
	int foundNow = 0;
    if (image_prev.empty() || features_next.size() == 0) {
        printf("Initializing corners\n");
        cvtColor(image, image_next, CV_RGB2GRAY);
        goodFeaturesToTrack(image_next, // the image
                features_next,   // the output detected features
                maxCorners,  // the maximum number of features
                qualityLevel,     // quality level
                minDistance     // min distance between two features
        );
    } else {
        features_prev = features_next;
        cvtColor(image, image_next, CV_RGB2GRAY);
        // Find position of feature in new image
        calcOpticalFlowPyrLK(
                image_prev, image_next, // 2 consecutive images
                features_prev, // input point positions in first im
                features_next, // output point positions in the 2nd
                status,    // tracking success
                err      // tracking error
        );
		
        for (int i = 0; i < status.size(); i++) {
            if ((int) status[i] == 1) {
				foundNow++;
                line(image, Point(features_prev[i].x, features_prev[i].y), Point(features_next[i].x, features_next[i].y), Scalar(0, 0, 0), 2);
                cv::circle(image, Point(features_next[i].x, features_next[i].y), 2, Scalar(0, 0, 0), -1);

                line(image, Point(features_prev[i].x, features_prev[i].y), Point(features_next[i].x, features_next[i].y), Scalar(255, 255, 255), 1);
                cv::circle(image, Point(features_next[i].x, features_next[i].y), 1, Scalar(255, 255, 255), -1);
            }
        }
    }
	if (foundNow < found) {
		reset();
	} else {
		image_prev = image_next.clone();
		found = foundNow;
	}
    return image;
}

void OpticalFlowMotionDetection::reset() {
    image_prev.release();

    features_prev.clear();
    features_next.clear();

	found = 0;
}
