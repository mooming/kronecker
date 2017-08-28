// Copyright Hansol Park (anav96@naver.com, mooming.go@gmail.com). All rights reserved.

#include "System/System.h"
#include "System/TestEnv.h"

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix2x2.h"
#include "Math/Matrix3x3.h"
#include "Math/Matrix4x4.h"
#include "Math/Quaternion.h"
#include "Math/AffineTransform.h"
#include "Math/UniformTransform.h"
#include "Math/RigidTransform.h"
#include "Math/EuclidSpace.h"

#include <iostream>

using namespace HE;

int main(int argc, const char* argv[])
{
    using namespace std;

    cout << fixed;
    cout.precision(2);

#ifdef __UNIT_TEST__
    auto& testEnv = TestEnv::GetEnv();

    testEnv.AddTest(new AllocatorTest());
    testEnv.AddTest(new StackAllocatorTest());
    testEnv.AddTest(new ArrayTest());
    testEnv.AddTest(new ComponentSystemTest());
    testEnv.AddTest(new LinkedListTest());
    testEnv.AddTest(new OptionalTest());
    testEnv.AddTest(new PoolAllocatorTest());
    testEnv.AddTest(new StringTest());
    testEnv.AddTest(new VectorTest());
    testEnv.AddTest(new Vector2Test());
    testEnv.AddTest(new Vector3Test());
    testEnv.AddTest(new Vector4Test());
    testEnv.AddTest(new Matrix3x3Test());
    testEnv.AddTest(new QuaternionTest());
    testEnv.AddTest(new AffineTransformTest());
    testEnv.AddTest(new UniformTransformTest());
    testEnv.AddTest(new RigidTransformTest());
    testEnv.AddTest(new EuclidSpaceTest());

    testEnv.Start();
#else //__UNIT_TEST__
    cout << "Test configuration is disabled." << endl;
#endif //__UNIT_TEST__

    char ch;
    std::cin >> ch;

    return 0;
}