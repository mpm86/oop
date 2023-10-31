#include "PolyhedronFactory.h"

#include "Sphere.h"
#include "Cylinder.h"
#include "Composite.h"

#include <iterator>
#include <algorithm>

PolyhedronFactory::PolyhedronPair PolyhedronFactory::_known_polyhedra[] = {
    {"sphere"   ,  new Sphere()},
    {"composite",  new Composite()},
    {"cylinder" ,  new Cylinder()}
};

//------------------------------------------------------------------------------
Polyhedron* PolyhedronFactory::createPolyhedron(std::string name)
{
    for(const PolyhedronPair& pair : _known_polyhedra) {
        if(pair.first == name) {
            return pair.second->clone();
        }
    }

    // A polygon with the given name could not be found
    return nullptr;
}

//------------------------------------------------------------------------------
bool PolyhedronFactory::isKnown(std::string name)
{
    const auto it = std::find_if(std::begin(_known_polyhedra),
                                 std::end(_known_polyhedra),
                                 [&name](const PolyhedronPair& pairToCheck) {
                                     return pairToCheck.first == name;
                                 });

    return it != std::end(_known_polyhedra);
}

//------------------------------------------------------------------------------
void PolyhedronFactory::listKnown(std::ostream& outs)
{
    for(const PolyhedronPair& pair : _known_polyhedra) {
        outs << " " << pair.first << "\n";
    }
}

//------------------------------------------------------------------------------
int PolyhedronFactory::numberKnown()
{
    return std::end(_known_polyhedra) - std::begin(_known_polyhedra);
}
