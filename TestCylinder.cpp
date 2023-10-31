#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cmath>

#include "Polyhedron.h"
#include "Sphere.h"
#include "Cylinder.h"

#include "utilities.h"

#include "bodgeUnitTest.h"

//-----------------------------------------------------------------------------
// Unit Tests
//-----------------------------------------------------------------------------

Cylinder* defaultCylinder = new Cylinder();

bool testDefaultConstructor()
{
    bodgeAssert(fpNumsAreEqual(defaultCylinder->getRadius(), 1));
    bodgeAssert(fpNumsAreEqual(defaultCylinder->getDiameter(), 2));

    bodgeAssert(fpNumsAreEqual(defaultCylinder->getHeight(), 1));

    // BoundingBox...
    Point expectedPoint(2, 2, 1);
    const Point& point = (defaultCylinder->getBoundingBox()).getUpperRightVertex();

    bodgeAssert(point == expectedPoint);

    // I am skipping display in this test

    return true;
}

//-----------------------------------------------------------------------------
bool testNonDefaultConstructor()
{
    Cylinder* cyl = new Cylinder(3, 2);

    bodgeAssert(fpNumsAreEqual(cyl->getRadius(), 3));
    bodgeAssert(fpNumsAreEqual(cyl->getDiameter(), 6));

    bodgeAssert(fpNumsAreEqual(cyl->getHeight(), 2));

    // BoundingBox...
    Point expectedPoint(6, 6, 2);
    const Point& point = (cyl->getBoundingBox()).getUpperRightVertex();

    bodgeAssert(point == expectedPoint);

    // I am skipping display in this test

    delete cyl;

    return true;
}

//-----------------------------------------------------------------------------
bool testSetRadius()
{
    Cylinder* cyl = new Cylinder(1, 2);

    cyl->setRadius(12);

    bodgeAssert(fpNumsAreEqual(cyl->getRadius(), 12));
    bodgeAssert(fpNumsAreEqual(cyl->getDiameter(), 24));

    bodgeAssert(fpNumsAreEqual(cyl->getHeight(), 2));

    // BoundingBox...
    Point expectedPoint(24, 24, 2);
    const Point& point = (cyl->getBoundingBox()).getUpperRightVertex();

    bodgeAssert(point == expectedPoint);

    // I am skipping display in this test

    delete cyl;

    return true;
}

//-----------------------------------------------------------------------------
bool testSetHeight()
{
    Cylinder* cyl = new Cylinder(1, 2);

    cyl->setHeight(8);

    bodgeAssert(fpNumsAreEqual(cyl->getRadius(), 1));
    bodgeAssert(fpNumsAreEqual(cyl->getDiameter(), 2));

    bodgeAssert(fpNumsAreEqual(cyl->getHeight(), 8));

    // BoundingBox...
    Point expectedPoint(2, 2, 8);
    const Point& point = (cyl->getBoundingBox()).getUpperRightVertex();

    bodgeAssert(point == expectedPoint);

    // I am skipping display in this test

    delete cyl;

    return true;
}

//-----------------------------------------------------------------------------
bool testClone()
{
    Cylinder* cyl = new Cylinder(3, 2);

    Cylinder* cpy = (Cylinder*) cyl->clone();

    bodgeAssert(fpNumsAreEqual(cpy->getRadius(), 3));
    bodgeAssert(fpNumsAreEqual(cpy->getDiameter(), 6));

    bodgeAssert(fpNumsAreEqual(cpy->getHeight(), 2));

    // BoundingBox...
    Point expectedPoint(6, 6, 2);
    const Point& point = (cpy->getBoundingBox()).getUpperRightVertex();

    bodgeAssert(point == expectedPoint);

    // I am skipping display in this test

    delete cyl;
    delete cpy;

    return true;
}

//-----------------------------------------------------------------------------
bool testRead()
{
    Cylinder* cyl = new Cylinder();

    std::istringstream ins("4 12");

    cyl->read(ins);

    bodgeAssert(fpNumsAreEqual(cyl->getRadius(), 12));
    bodgeAssert(fpNumsAreEqual(cyl->getDiameter(), 24));

    bodgeAssert(fpNumsAreEqual(cyl->getHeight(), 4));

    // BoundingBox...
    Point expectedPoint(24, 24, 4);
    const Point& point = (cyl->getBoundingBox()).getUpperRightVertex();

    bodgeAssert(point == expectedPoint);

    // I am skipping display in this test

    delete cyl;

    return true;
}

//-----------------------------------------------------------------------------
bool testScale()
{
    Cylinder* cyl = new Cylinder(5, 3);

    cyl->scale(2);

    bodgeAssert(fpNumsAreEqual(cyl->getRadius(), 10));
    bodgeAssert(fpNumsAreEqual(cyl->getDiameter(), 20));

    bodgeAssert(fpNumsAreEqual(cyl->getHeight(), 6));

    // BoundingBox...
    Point expectedPoint(20, 20, 6);
    const Point& point = (cyl->getBoundingBox()).getUpperRightVertex();

    bodgeAssert(point == expectedPoint);

    // I am skipping display in this test

    delete cyl;

    return true;
}

//-----------------------------------------------------------------------------
bool testDisplay()
{
    Cylinder* cyl = new Cylinder(3, 5);

    std::ostringstream outs;
    const std::string expectedOutput = "[Cylinder] (6, 6, 5)->Radius: 3 Height: 5";

    cyl->display(outs);
    bodgeAssert(outs.str() == expectedOutput);

    delete cyl;

    return true;
}

//------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    UnitTestPair tests[] = {
        {testDefaultConstructor, "testDefaultConstructor"},
        {testNonDefaultConstructor, "testNonDefaultConstructor"},
        {testSetRadius, "testSetRadius"},
        {testSetHeight, "testSetHeight"},
        {testClone, "testClone"},
        {testRead, "testRead"},
        {testScale, "testScale"},
        {testDisplay, "testDisplay"}
    };

    for (const UnitTestPair& testPair : tests) {
        runTest(testPair.first, testPair.second);
    }

    return 0;
}

