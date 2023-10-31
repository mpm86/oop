#include <cmath>

#include "utilities.h"

//------------------------------------------------------------------------------
const double FP_TOLERANCE = 0.01;

//------------------------------------------------------------------------------
bool fpNumsAreEqual(double fp1, double fp2, double eps)
{
    return std::abs(fp2 - fp1) <= eps;
}

