#include "Cart_Point.h"
// Class Cart_Point definitions
// stores the x and y cartesian coordinates of all game objects

// CONSTRUCTOR: DEFAULT
Cart_Point::Cart_Point()
{
	this-> x = 0.0;
	this-> y = 0.0;
}

// CONSTRUCTOR: INPUT BASED
Cart_Point::Cart_Point(double inputx, double inputy)
{
	this-> x = inputx;
	this-> y = inputy;
}

// NON-MEMBER FUNCTION
double cart_distance(const Cart_Point & p1, const Cart_Point & p2)
{
	double distance;
	// sum the square of the difference of each vector component
	distance = pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);
	return sqrt(distance);
}

// OPERATOR OVERLOAD
Cart_Point operator + (const Cart_Point & p1, const Cart_Vector & v1)
{
	// p1 + v1 returns a new p1 with the translation component proportional to vector direction
	double pointx = p1.x + v1.x;
	double pointy = p1.y + v1.y;
	return Cart_Point(pointx, pointy);
}

// OPERATOR OVERLOAD
Cart_Vector operator - (const Cart_Point & p1, const Cart_Point & p2)
{
	// p1 - p1 gives a Cart_Vector object that is the vector form p1 pointing to p2
	double vecx = p1.x - p2.x;
	double vecy = p1.y - p2.y;
	return Cart_Vector(vecx, vecy);
}

// OPERATOR OVERLOAD
std::ostream & operator << (std::ostream & out, const Cart_Point & p1)
{
	out << "(" << p1.x << ", " << p1.y << ")";
	return out;
}

// OPERATOR OVERLOAD
bool operator == (const Cart_Point & p1, const Cart_Point & p2)
{
	if (p1.x == p2.x && p1.y == p2.y)
		return true;
	return false;
}