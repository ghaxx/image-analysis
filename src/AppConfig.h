//
// Created by Kuba Sławiński on 21/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#ifndef __AppArgs_H_
#define __AppArgs_H_

#include <string>

class AppConfig {
public:
    static int argc;
    static char** argv;
    static const std::string dataDir;
    static const std::string outputDir;
    static const std::string inputDir;
};


#endif //__AppArgs_H_
