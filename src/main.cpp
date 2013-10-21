//
//  main.cpp
//  OpenCV-1
//
//  Created by Kuba Sławiński on 11/10/2013.
//  Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//

#import "App.h"
#import "AppConfig.h"

int main(int argc, char *argv[]) {
    AppConfig::argc = argc;
    AppConfig::argv = argv;

    App *app = new App();
    app->run();

    return 0;
}

