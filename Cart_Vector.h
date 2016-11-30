#ifndef CART_VECTOR_H
#define CART_VECTOR_H

#include <iostream>

// stores the x and y vector components

class Cart_Vector
{
// everything within this class is a public member
public:
	// the two components
	double x, y;

	// CONSTRUCTOR: DEFAULT
	Cart_Vector();

	// CONSTRUCTOR: input based
	Cart_Vector(double inputx, double inputy);
};

// OPERATOR OVERLOADS
Cart_Vector operator * (const Cart_Vector &, double);
Cart_Vector operator / (const Cart_Vector &, double);
std::ostream & operator << (std::ostream &, const Cart_Vector &);

#endif