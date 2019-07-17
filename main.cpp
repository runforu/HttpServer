//
// main.cpp
// ~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <csignal>
#include <ctime>
#include <iostream>
#include <string>
#include "Processor.h"
#include "RequestHandlerProviderImp.h"
#include "http/server.h"

_CrtMemState s1, s2, s3;
struct A {
    A() {
        
    }
    ~A() {
        
    }
};

A a;
int main(int argc, char* argv[]) {
    _CrtMemCheckpoint(&s1);
    {
        _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
        HANDLE hLogFile = CreateFile("c:/memleak.log", GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL,
            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
        _CrtSetReportFile(_CRT_WARN, hLogFile);
    }

    Processor::Instance().Initialize();

    std::string input;
    while (std::cin >> input) {
        if (input.compare("exit") == 0) {
            break;
        }
    }
    Processor::Instance().Shutdown();
    int *a = new int;
    _CrtMemCheckpoint(&s2);
    _CrtMemDifference(&s3, &s1, &s2);
    _CrtMemDumpStatistics(&s3);
    _CrtDumpMemoryLeaks();
    return 0;
}
