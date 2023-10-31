#include "Polyhedron.h"
#include "Composite.h"

//------------------------------------------------------------------------------
Composite::Composite()
    :Polyhedron("Composite")
{
}

//------------------------------------------------------------------------------
/**
 * @todo write this function
 */
Composite::Composite(const Composite& src)
    :Polyhedron("Composite")
{
    // Perform a deep copy... maybe the _add_ method can help...
}

//------------------------------------------------------------------------------
/**
 * @todo write this function
 */
Composite::~Composite()
{
    // Delete each component polyhedra
}

//------------------------------------------------------------------------------
void Composite::read(std::istream& ins){
    int numPolyhedra;

    ins >> numPolyhedra;

    allPolyhedra.resize(numPolyhedra);

    for (int i = 0; i < numPolyhedra; i++) {
        ins >> allPolyhedra[i];

        boundingBox.mergeWith(allPolyhedra[i]->getBoundingBox());
    }
}

//------------------------------------------------------------------------------
/**
 * @todo write this function
 */
void Composite::display(std::ostream& outs) const
{
    Polyhedron::display(outs);

    outs << allPolyhedra.size() << " polyhedra" << "\n";

    // Loop through all component polyhedra and
    // print (display) them
}

//------------------------------------------------------------------------------
/**
 * @todo write this function
 */
void Composite::scale(double scalingFactor)
{
    // Loop through all polyhedra and scale them

    // Do not forget the bounding box... after the loop
}

//------------------------------------------------------------------------------
Composite& Composite::operator=(Composite rhs)
{
    swap(*this, rhs);
    return *this;
}

//------------------------------------------------------------------------------
Composite::iterator Composite::begin()
{
    return allPolyhedra.begin();
}

//------------------------------------------------------------------------------
Composite::iterator Composite::end()
{
    return allPolyhedra.end();
}

//------------------------------------------------------------------------------
Composite::const_iterator Composite::begin() const
{
    return allPolyhedra.begin();
}

//------------------------------------------------------------------------------
Composite::const_iterator Composite::end() const
{
    return allPolyhedra.end();
}

//------------------------------------------------------------------------------
/**
 * @todo write this function
 */
void Composite::add(const Polyhedron* toAdd)
{
    // Add one new polyhedra and _merge_ its boundingBox with _this->boundingBox_
}

//------------------------------------------------------------------------------
void swap(Composite& lhs, Composite& rhs)
{
    using std::swap;

    std::swap(lhs.allPolyhedra, rhs.allPolyhedra);

    swap(lhs.boundingBox, rhs.boundingBox);
}
