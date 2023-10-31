#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cmath>
#include <memory>

#include "Polyhedron.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Composite.h"

#include "utilities.h"

#include "bodgeUnitTest.h"

//-----------------------------------------------------------------------------
// Unit Tests
//-----------------------------------------------------------------------------
const Point     ORIGIN(0, 0, 0);
const Composite EMPTY_POLY;

const std::string INPUT_STR = R"(2
    cylinder 1 2
    sphere 5)";

bool testDefaultConstructor()
{
    Point lowerPoint = (EMPTY_POLY.getBoundingBox()).getLowerLeftVertex();
    Point upperPoint = (EMPTY_POLY.getBoundingBox()).getUpperRightVertex();

    bodgeAssert(lowerPoint == ORIGIN);
    bodgeAssert(upperPoint == ORIGIN);

    bodgeAssert(EMPTY_POLY.size() == 0);

    bodgeAssert(EMPTY_POLY.begin() == EMPTY_POLY.end());

    // I am skipping display in this test

    return true;
}

//-----------------------------------------------------------------------------
bool testAdd()
{
    Polyhedron* sphere  = new Sphere(2);
    Polyhedron* cylinder = new Cylinder(3, 5);

    Composite comp1;

    comp1.add(sphere);
    bodgeAssert(comp1.size() == 1);
    bodgeAssert(comp1.begin() != comp1.end());

    Point lowerPoint = (comp1.getBoundingBox()).getLowerLeftVertex();
    Point upperPoint = (comp1.getBoundingBox()).getUpperRightVertex();

    bodgeAssert(lowerPoint == ORIGIN);
    bodgeAssert(upperPoint == Point(4, 4, 4));

    comp1.add(cylinder);

    bodgeAssert(comp1.size() == 2);
    bodgeAssert(comp1.begin() != comp1.end());

    lowerPoint = (comp1.getBoundingBox()).getLowerLeftVertex();
    upperPoint = (comp1.getBoundingBox()).getUpperRightVertex();

    bodgeAssert(lowerPoint == ORIGIN);
    bodgeAssert(upperPoint == Point(6, 6, 5));

    // I am skipping display in this test

    delete sphere;
    delete cylinder;

    return true;
}


//-----------------------------------------------------------------------------
bool testClone()
{
    Polyhedron* sphere  = new Sphere(2);
    Polyhedron* cylinder = new Cylinder(3, 5);

    Composite comp1;

    comp1.add(sphere);
    comp1.add(cylinder);

    // Sanity Check Original
    bodgeAssert(comp1.size() == 2);
    bodgeAssert(comp1.begin() != comp1.end());

    Point lowerPoint = (comp1.getBoundingBox()).getLowerLeftVertex();
    Point upperPoint = (comp1.getBoundingBox()).getUpperRightVertex();

    bodgeAssert(lowerPoint == ORIGIN);
    bodgeAssert(upperPoint == Point(6, 6, 5));

    // Make the copy and check it
    Polyhedron* theCopyAsBase = comp1.clone();
    Composite&  theCopyAsComp = *((Composite*) theCopyAsBase);

    bodgeAssert(theCopyAsComp.size() == 2);
    bodgeAssert(theCopyAsComp.begin() != theCopyAsComp.end());

    lowerPoint = (theCopyAsComp.getBoundingBox()).getLowerLeftVertex();
    upperPoint = (theCopyAsComp.getBoundingBox()).getUpperRightVertex();

    bodgeAssert(lowerPoint == ORIGIN);
    bodgeAssert(upperPoint == Point(6, 6, 5));

    // Technically I should use the iterator to check that I
    // have copies of `sphere` and `cylinder`

    // I am skipping display in this test

    delete theCopyAsBase;
    delete sphere;
    delete cylinder;

    return true;
}

//-----------------------------------------------------------------------------
bool testRead()
{
    std::istringstream ins(INPUT_STR);

    Composite comp1;
    comp1.read(ins);

    bodgeAssert(comp1.size() == 2);
    bodgeAssert(comp1.begin() != comp1.end());
    // Technically I should use the iterator to check that I
    // have the correct `sphere` and `cylinder`

    // BoundingBox...
    Point expectedPoint(10, 10, 10);
    const Point& point = (comp1.getBoundingBox()).getUpperRightVertex();

    bodgeAssert(point == expectedPoint);

    // I am skipping display in this test

    return true;
}

//-----------------------------------------------------------------------------
/**
This comment contains the markup to render a sequence diagram in sdedit:
    #![testScale]
    test:TestComposite[a]
    /sphere:unique_ptr<Sphere>[a]
    /rawSphere:Sphere*[a]
    /sphereBB:BoundingBox[a]
    /cylinder:unique_ptr<Cylinder>[a]
    /rawCylinder:Cylinder*[a]
    /cylinderBB:BoundingBox[a]
    /comp:Composite[a]
    /compBB:BoundingBox[a]
    /allPolyhedra:vector<Polyhedron*>[a]
    #
    # Setup
    test:rawSphere=rawSphere.new(2)
    rawSphere:sphereBB.new()
    rawSphere:d=rawSphere.getDiameter()
    rawSphere:sphereBB.setUpperRightVertex(d, d, d)
    test:sphere.new(rawSphere)
    test:rawCylinder=rawCylinder.new(3, 5)
    rawCylinder:cylinderBB.new()
    rawCylinder:d=rawCylinder.getDiameter()
    rawCylinder:cylinderBB.setUpperRightVertex(d, d, height)
    test:cylinder.new(rawCylinder)
    test:comp.new()
    comp:compBB.new()
    comp:allPolyhedra.new()
    #
    # Add rawSphere and rawCylinder to comp
    test:rawSphere=sphere.get()
    test:comp.add(rawSphere)
    comp:cpy=rawSphere.clone()
    comp:allPolyhedra.push_back(cpy)
    comp:compBB.merge(cpy.getBoundingBox())
    test:rawCylinder=cylinder.get()
    test:comp.add(rawCylinder)
    comp:cpy=rawCylinder.clone()
    comp:allPolyhedra.push_back(cpy)
    comp:compBB.merge(cpy.getBoundingBox())
    #
    test:comp.scale(5)
    [c:loop for each idx in {0, 1}]
    comp:poly=allPolyhedra.at(idx)
    comp:poly->scale() is invoked (omitted for brevity)
    [/c]
    test:All Checks (assertions run)
    test:sphere.destroy()
    sphere:rawSphere.destroy()
    rawSphere:sphereBB.destroy()
    test:cylinder.destroy()
    cylinder:rawCylinder.destroy()
    rawCylinder:cylinderBB.destroy()
    test:comp.destroy()
    [c:loop for each idx in {0, 1}]
    comp:poly=allPolyhedra.at(idx)
    comp:delete poly (omitted for brevity)
    [/c]
    comp:allPolyhedra.destroy()
**/
bool testScale()
{
    std::unique_ptr<Polyhedron> sphere(new Sphere(2));
    std::unique_ptr<Polyhedron> cylinder(new Cylinder(3, 5));

    Composite comp1;

    comp1.add(sphere.get());
    comp1.add(cylinder.get());

    comp1.scale(5);

    // Sanity Check Original
    bodgeAssert(comp1.size() == 2);
    bodgeAssert(comp1.begin() != comp1.end());
    // Technically I should use the iterator to check that I
    // have the correct `sphere` and `cylinder`

    Point lowerPoint = (comp1.getBoundingBox()).getLowerLeftVertex();
    Point upperPoint = (comp1.getBoundingBox()).getUpperRightVertex();

    bodgeAssert(lowerPoint == ORIGIN);
    bodgeAssert(upperPoint == Point(30, 30, 25));

    return true;
}

//-----------------------------------------------------------------------------
bool testDisplay()
{
    std::unique_ptr<Polyhedron> sphere(new Sphere(2));
    std::unique_ptr<Polyhedron> cylinder(new Cylinder(3, 5));

    Composite comp1;

    comp1.add(sphere.get());
    comp1.add(cylinder.get());

    comp1.scale(5);

    std::ostringstream outs;
    std::string expectedOutput = R"([Composite] (30, 30, 25)->2 polyhedra
  [Sphere] (20, 20, 20)->Radius: 10 Diameter: 20
  [Cylinder] (30, 30, 25)->Radius: 15 Height: 25
)";

    comp1.display(outs);
    bodgeAssert(outs.str() == expectedOutput);

    return true;
}

//------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    UnitTestPair tests[] = {
        {testDefaultConstructor, "testDefaultConstructor"},
        {testAdd, "testAdd"},
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

