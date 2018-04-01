// Copyright Hansol Park (anav96@naver.com, mooming.go@gmail.com). All rights reserved.

#include "System/TestCase.h"

#include <iostream>
#include <exception>

using namespace HardBop::Test;

TestCase::TestCase(const char * title) : title(title), isDone(false), isSuccess(false)
{
}

void TestCase::Start()
{
    using namespace std;

    try
    {
        cout << title << " : START ====================" << endl;
        isSuccess = DoTest();
        isDone = true;
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }

    Report();
}

void TestCase::Report()
{
    using namespace std;

    if (isSuccess)
    {
        cout << title << " : SUCCESS" << endl;
    }
    else
    {
        cerr << title << " : FAILED" << endl;
    }

    cout << endl;
}
