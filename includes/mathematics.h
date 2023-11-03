#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include "objects.h"

/******************************* geom_trans.c *******************************/

/**
 * @brief Function calculates the translation vector to move an object to the
 * origin in a 3D Cartesian plane.
 * @param object The object's current x,y,z position
 * @return 3D vector (x, y, z) representing the translation needed to bring the
 * object to the origin.
*/
t_coord	translation(t_coord object);
/**
 * @brief Function applies Rodrigues' rotation formula to find the new position
 * of a vector after it has been rotated about an arbitrary axis.
 * @param vector The original 3D vector.
 * @param angle The angle of rotation in radians.
 * @return Function returns a new position of a vector after it has been
 * rotated.
*/
t_coord	rotation(t_coord *vector, double angle);

/***************************** vector_algebra.c *****************************/

/**
 * @brief Function performs dot product operation on two vectors in a 3D
 * oriented Euclidean vector space.
 * @param a The first vector.
 * @param b The second vector.
 * @return Function returns a scalar number that is a measure of how closely the
 * two vectors align.
*/
double	dot_prod(t_coord a, t_coord b);
/**
 * @brief Function performs cross product operation on two vectors in a 3D
 * oriented Euclidean vector space.
 * @param a The first vector.
 * @param b The second vector.
 * @return Function returns a new vector that is perpendicular to both a and b,
 * thus normal to the plane containing them (assuming a and b are linearly
 * independent).
*/
t_coord	cross_prod(t_coord a, t_coord b);
t_coord	normalize(t_coord a);

/**************************** vector_arithmetic.c ****************************/

/**
 * @brief Function performs scalar multiplication on a vector, where each
 * components of the vector is multiplied by the specified value.
 * @param vector The vector for multiplication.
 * @param value The value to be multiplied for each component of the vector.
 * @return Function returns a new vector as the product of the arithmetic
 * operation.
*/
t_coord	vect_mult(t_coord vector, double value);
/**
 * @brief Function performs summation of two (or three) vectors.
 * @param a The first vector.
 * @param b The second vector.
 * @return Function returns a resulting vector of the vectors parsed.
*/
t_coord vect_add(t_coord a, t_coord b);
/**
 * @brief Function performs subtraction of two (or three) vectors.
 * @param a The first vector.
 * @param b The second vector.
 * @return Function returns a resulting vector of the vectors parsed.
*/
t_coord vect_subt(t_coord a, t_coord b);

#endif