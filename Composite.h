#ifndef COMPOSITE_H_INCLUDED
#define COMPOSITE_H_INCLUDED

#include <vector>

#include "Polyhedron.h"

class Composite : public Polyhedron {
    public:
        using Collection = std::vector<Polyhedron*>;

        using iterator       = Collection::iterator;
        using const_iterator = Collection::const_iterator;

    private:
        /**
         * Collection of polyhedra of which
         * this composite polyhedron is composed
         */
        Collection allPolyhedra;

    public:

        /**
         * Default Constructor
         */
        Composite();

        /**
         * Copy Constructor
         */
        Composite(const Composite& src);

        /**
         * Destructor
         */
        virtual ~Composite();

        /**
         * Assignment Operator
         */
        Composite& operator=(Composite rhs);

        /**
         * Return the number of polyhedra that are part of this
         * Composite object.
         */
        int size() const;

        // Iterator helpers
        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        /**
         * Add a Polyhedron to the `Composite` collection.
         *
         * @post toAdd is cloned and the copy is added.
         */
        void add(const Polyhedron* toAdd);

        // Polyhedron Interface

        /**
         * Copy Constructor Wrapper
         */
        virtual Polyhedron* clone() const;

        /**
         * Read all component polyhedra
         *
         * @pre numPolyhedra == 0
         */
        virtual void read(std::istream& ins);

        /**
         * Print all polyhedra
         */
        virtual void display(std::ostream& outs) const;

        /**
         * Scale all polyhedra
         */
        virtual void scale(double scalingFactor);

        /**
         * Swap the contents of two `Composite`s
         * <p>
         * I am using a friend function here and only here (under protest)
         */
        friend
        void swap(Composite& lhs, Composite& rhs);
};

//------------------------------------------------------------------------------
inline
int Composite::size() const
{
    return this->allPolyhedra.size();
}

//------------------------------------------------------------------------------
inline
Polyhedron* Composite::clone() const
{
    return new Composite(*this);
}

#endif
