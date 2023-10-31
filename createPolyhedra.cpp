#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>

#include "Polyhedron.h"
#include "PolyhedronFactory.h"

using namespace std;

using PolyhedronSmtPtr = std::unique_ptr<Polyhedron>;
using PolyhedronCollection = std::vector<PolyhedronSmtPtr>;

/**
 * Construct a list of polyhedra from
 * an input stream
 */
void readPolyhedra(istream& inf, PolyhedronCollection& polyhedra);

/**
 * Print a collection of polyhedra
 */
void printPolyhedra(ostream& outs, const PolyhedronCollection& polyhedra,
                    std::string heading);

/**
 * Main function
 *
 * @param argv[1] polyhedron input file
 * @param argv[2] scaling factor
 */
int main(int argc, char** argv)
{
    // Validate number of command line arguments
    if (argc < 3) {
        cerr << "Usage " << argv[0] << " inputFile scalingFactor" << "\n";
        return 1;
    }

    // Validate Scaling Factor
    int scalingFactor = atoi(argv[2]);
    if (scalingFactor < 1) {
        cerr << "Scaling Factor must be >= 1" << "\n";
        return 2;
    }

    // Validate Input File
    ifstream polyIn(argv[1]);
    if (!polyIn) {
        cerr << "Could not open " << argv[1] << "\n";
        return 3;
    }

    // Original polyhedra
    PolyhedronCollection polyhedra;
    readPolyhedra(polyIn, polyhedra);

    // Scaled copies
    PolyhedronCollection scaledCopies;
    std::transform(polyhedra.begin(), polyhedra.end(),
                   std::back_inserter(scaledCopies),
                   [scalingFactor](const PolyhedronSmtPtr& original) {
                        Polyhedron* copy = original->clone();
                        copy->scale(scalingFactor);

                        return std::unique_ptr<Polyhedron>(copy);
                    });

    printPolyhedra(cout, polyhedra, "Original Polyhedra");

    std::cout << "\n" << "\n";
    printPolyhedra(cout, scaledCopies, "Scaled Polyhedra (Clones)");

    return 0;
}

//------------------------------------------------------------------------------
void readPolyhedra(istream& inf, PolyhedronCollection& polyhedra)
{
    Polyhedron* p = nullptr;

    while (inf >> p) {
        if (p != nullptr) {
            polyhedra.emplace_back(p);
        }
    }
}

//------------------------------------------------------------------------------
void printPolyhedra(ostream& outs, const PolyhedronCollection& polyhedra,
                    std::string heading)
{
    outs << heading << "\n" << string(54, '-') << "\n";

    for (const PolyhedronSmtPtr& p : polyhedra) {
        outs << (*p) << "\n";
    }
}
