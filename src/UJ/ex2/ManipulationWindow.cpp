//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "ManipulationWindow.h"
#include "App.h"
#include "SharpenWithGaussian.h"


ManipulationWindow::ManipulationWindow(std::string title) : FilterWindow(title, new LinearTransformation()) {
    capture = SynchronizedVideoCapture::getInstance();
}

void ManipulationWindow::show() {
    cv::Mat mat;
    capture->read(mat);
    App::debug("Manipulation\n");
    cv::Mat transformed(getT()->transform(mat));

    char a[100];
    sprintf(a, "Multiply by %.2f", getLT()->mult);
    cv::putText(transformed, a, cvPoint(10, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
    sprintf(a, "Add: %d", getLT()->add);
    cv::putText(transformed, a, cvPoint(10, 70), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
    SharpenWithGaussian s;
    imshow(getTitle(), s.transform(transformed));
    mat.release();
    transformed.release();
}


void ManipulationWindow::control(char key) {
    if (key == 'a')
        getLT()->mult -= 0.1;
    if (key == 'q')
        getLT()->mult += 0.1;
    if (key == 'w')
        getLT()->add += 5;
    if (key == 's')
        getLT()->add -= 5;
    if (key == 'r')
        reset();
}

void ManipulationWindow::reset() {
    getLT()->mult = 1;
    getLT()->add = 0;
}

LinearTransformation *ManipulationWindow::getLT() {
    return (LinearTransformation *) getT();
}
