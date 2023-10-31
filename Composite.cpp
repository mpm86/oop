#include "Composite.h"

Composite::Composite()
    :Polyhedron("Composite"), allPolyhedra()
{}

Composite::Composite(const Composite& src)
    :Polyhedron("Composite"), allPolyhedra()
{
    for (const auto& poly : src.allPolyhedra) {
        allPolyhedra.push_back(poly->clone());
        boundingBox.mergeWith(poly->getBoundingBox()); // Ensure bounding box is updated
    }
}

Composite::~Composite()
{
    for (auto& poly : allPolyhedra) {
        delete poly;
    }
    allPolyhedra.clear();
}

void Composite::read(std::istream& ins) {
    int numPolyhedra;
    ins >> numPolyhedra;
    allPolyhedra.resize(numPolyhedra);
    for (int i = 0; i < numPolyhedra; i++) {
        ins >> allPolyhedra[i];
        boundingBox.mergeWith(allPolyhedra[i]->getBoundingBox());
    }
}

void Composite::display(std::ostream& outs) const {
    Polyhedron::display(outs);
    outs << allPolyhedra.size() << " polyhedra";
    for (const auto& poly : allPolyhedra) {
        outs << std::endl << "  "; // Add indentation for polyhedra inside composite
        poly->display(outs);
    }
}

void Composite::scale(double scalingFactor) {
    for (auto& poly : allPolyhedra) {
        poly->scale(scalingFactor);
    }
    boundingBox.scale(scalingFactor);
}

Composite& Composite::operator=(Composite rhs) {
    // Delete old objects
    for (auto& poly : allPolyhedra) {
        delete poly;
    }
    allPolyhedra.clear();

    // Swap with the new objects
    swap(*this, rhs);
    return *this;
}

void Composite::add(const Polyhedron* toAdd) {
    allPolyhedra.push_back(toAdd->clone());
    boundingBox.mergeWith(toAdd->getBoundingBox());
}

void swap(Composite& lhs, Composite& rhs) {
    using std::swap;
    std::swap(lhs.allPolyhedra, rhs.allPolyhedra);
    swap(lhs.boundingBox, rhs.boundingBox);
}

Polyhedron* Composite::clone() const {
    return new Composite(*this);
}

int Composite::size() const {
    return allPolyhedra.size();
}

Composite::iterator Composite::begin() {
    return allPolyhedra.begin();
}

Composite::iterator Composite::end() {
    return allPolyhedra.end();
}

Composite::const_iterator Composite::begin() const {
    return allPolyhedra.begin();
}

Composite::const_iterator Composite::end() const {
    return allPolyhedra.end();
}
