// Class Cart_Vector definitions
// stores the x and y vector components
#include "Cart_Vector.h"

// CONSTRUCTOR: DEFAULT
Cart_Vector::Cart_Vector()
{
	this-> x = 0.0;
	this-> y = 0.0;
}

// CONSTRUCTOR: INPUT BASED
Cart_Vector::Cart_Vector(double inputx, double inputy)
{
	this-> x = inputx;
	this-> y = inputy;
}

// OPERATOR OVERLOAD
Cart_Vector operator * (const Cart_Vector & v1, double d)
{
	// returns a scalar multiple of v1 by the scalar double d
	double x = v1.x * d;
	double y = v1.y * d;
	return Cart_Vector(x, y);
}

// OPERATOR OVERLOAD
Cart_Vector operator / (const Cart_Vector & v1, double d)
{
	// returns a scalar division of v1 by the scalar double d
	if (d != 0)
	{
		double xcomp = v1.x / d;
		double ycomp = v1.y / d;
		return Cart_Vector(xcomp, ycomp);
	}
	else // if dividing by 0 then just return original input vector object
	{
		return v1;
	}
}

// OPERATOR OVERLOAD
std::ostream & operator << (std::ostream & out, const Cart_Vector & v1)
{
	out << "<" << v1.x << ", " << v1.y << ">";
	return out;
}