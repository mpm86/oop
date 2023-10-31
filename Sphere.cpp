#include "Sphere.h"

//------------------------------------------------------------------------------
Sphere::Sphere()
    :Sphere(1)
{
}

//------------------------------------------------------------------------------
Sphere::Sphere(double r)
    :Polyhedron("Sphere"),
     radius(r)
{
    double d = this->getDiameter();
    boundingBox.setUpperRightVertex(d, d, d);
}

//------------------------------------------------------------------------------
void Sphere::read(std::istream& ins)
{
    ins >> radius;

    double d = this->getDiameter();
    boundingBox.setUpperRightVertex(d, d, d);
}

//------------------------------------------------------------------------------
void Sphere::display(std::ostream& outs) const
{
    Polyhedron::display(outs);

    outs << "Radius: " << radius
         << " "
         << "Diameter: " << getDiameter();
}

//------------------------------------------------------------------------------
void Sphere::scale(double scalingFactor)
{
    radius *= scalingFactor;

    boundingBox.scale(scalingFactor);
}
