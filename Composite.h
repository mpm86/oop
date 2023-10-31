#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "Polyhedron.h"
#include <vector>

class Composite : public Polyhedron {
    public:
        using Collection = std::vector<Polyhedron*>;

        using iterator       = Collection::iterator;
        using const_iterator = Collection::const_iterator;

    private:
        Collection allPolyhedra;

    public:
        Composite();
        Composite(const Composite& src);
        virtual ~Composite();
        Composite& operator=(Composite rhs);

        int size() const;

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

        void add(const Polyhedron* toAdd);

        virtual Polyhedron* clone() const override;
        virtual void read(std::istream& ins) override;
        virtual void display(std::ostream& outs) const override;
        virtual void scale(double scalingFactor) override;

        friend void swap(Composite& lhs, Composite& rhs);
};

#endif // COMPOSITE_H
