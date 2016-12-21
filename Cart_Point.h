#ifndef CART_POINT_H
#define CART_POINT_H

#include "Cart_Vector.h"

#include <iostream>

// stores the x and y cartesian coordinates of all game objects

class Cart_Point
{
// everything within this class is a public member
public:
	// the two coordinates
	double x, y;

	// CONSTRUCTOR: DEFAULT
	Cart_Point();

	// CONSTRUCTOR: input based
	Cart_Point(double inputx, double inputy);
};

// NON MEMBER FUNCTIONS
double cart_distance(const Cart_Point &, const Cart_Point &);

// OPERATOR OVERLOADS
Cart_Point operator + (const Cart_Point &, const Cart_Vector &);
Cart_Vector operator - (const Cart_Point &, const Cart_Point &);
std::ostream & operator << (std::ostream &, const Cart_Point &);
bool operator == (const Cart_Point & p1, const Cart_Point & p2);

#endif