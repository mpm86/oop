#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

extern const double FP_TOLERANCE;

/**
 * Compare two floating point numbers for equivalence. Allow them to differ
 * within a set tolerance
 *
 * Note there exists a tremendous amount of literature on how to
 * compare floating point number. For this exercise/example we will
 * use a slightly-better-than naive fp1 == fp2 approach.
 *
 * @param fp1 first floating point number
 * @param fp2 second floating point number
 * @param eps tolerance
 */
bool fpNumsAreEqual(double fp1, double fp2, double eps=FP_TOLERANCE);

#endif