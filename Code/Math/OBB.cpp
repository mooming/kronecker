// Copyright, all rights are reserved by Hansol Park, mooming.go@gmail.compl

#include "OBB.h"

using namespace HardBop::Math;
using namespace HardBop::Test;

template class OBB<float>;

#ifdef __UNIT_TEST__

#include <iostream>

bool OBBTest::DoTest()
{
	return true;
}

#endif  // __UNIT_TEST__
