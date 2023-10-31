#ifndef POLYHEDRONFACTORY_H_INCLUDED
#define POLYHEDRONFACTORY_H_INCLUDED

#include <iostream>
#include <array>

class Polyhedron;

/**
 * The Polyhedron Creating Wizard
 */
class PolyhedronFactory {
    private:
        /**
         * Name Polyhedron Pair 2-tuple( name, model )
         * <p>
         * Note how this is now a std::pair
         */
        using PolyhedronPair = std::pair<std::string, Polyhedron*>;

        static PolyhedronPair _known_polyhedra[];  ///< Listing of known polyhedra

    public:
        /**
         * Create a Polyhedron
         *
         * @param name the polyhedron to be created
         *
         * @return A polyhedron with the specified name
         *     or nullptr if no matching polyhedron is found
         */
        static Polyhedron* createPolyhedron(std::string name);

        /**
         * Determine whether a given polyhedron is known
         *
         * @param name the polyhedron for which to query
         */
        static bool isKnown(std::string name);

        /**
         * Print a list of known Polyhedrons
         *
         * @param outs the output stream
         */
        static void listKnown(std::ostream& outs);

        /**
         * Determine the number of known Polyhedrons
         *
         * @return the number of known polyhedrons
         *
         */
        static int numberKnown();
};

#endif