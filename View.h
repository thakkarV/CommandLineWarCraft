#ifndef VIEW_H
#define VIEW_H 

#include "Cart_Point.h"
#include "Game_Object.h"


const int VIEW_MAXSIZE = 20;


class View
{
public:
	View();

	void clear();
	// sets the char array to the default fill

	void plot(Game_Object * ptr);
	// calls get_subscript and plots the object in its proper location

	void draw();
	// displays the entire grid

private:
	int size;
	// current size of the gird to be displated

	double scale;
	// the distence represetned by each cell

	Cart_Point origin;
	// origin at lower left hand corner

	char grid[VIEW_MAXSIZE][VIEW_MAXSIZE][2];
	// holds al chars that make up the array

	bool get_subscripts(int & ix, int & iy, Cart_Point location);
	
};

#endif