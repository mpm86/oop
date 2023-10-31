#include "Cylinder.h"

//------------------------------------------------------------------------------
Cylinder::Cylinder()
    :Cylinder(1, 1)
{
    recomputeBox();
}

//------------------------------------------------------------------------------
Cylinder::Cylinder(double r, double h)
    :Polyhedron("Cylinder"),
     height(h),
     radius(r)
{
    // D.R.Y (Do not Repeat Yourself)
    // const double d = this->getDiameter();
    // boundingBox.setUpperRightVertex(d, d, height);
    recomputeBox();
}

//------------------------------------------------------------------------------
void Cylinder::read(std::istream& ins)
{
    ins >> height >> radius;

    // D.R.Y (Do not Repeat Yourself)
    // const double d = this->getDiameter();
    // boundingBox.setUpperRightVertex(d, d, height);
    recomputeBox();
}

//------------------------------------------------------------------------------
void Cylinder::display(std::ostream& outs) const
{
    Polyhedron::display(outs);

    outs << "Radius: " << radius
         << " "
         << "Height: " << height;
}

//------------------------------------------------------------------------------
void Cylinder::scale(double scalingFactor)
{
    radius *= scalingFactor;
    height *= scalingFactor;

    Polyhedron::scale(scalingFactor);
}

//------------------------------------------------------------------------------
void Cylinder::recomputeBox()
{
    const double d = this->getDiameter();
    boundingBox.setUpperRightVertex(d, d, height);
}