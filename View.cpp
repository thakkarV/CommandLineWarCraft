#include "View.h"
#include "Cart_Point.h"
#include "Game_Object.h"

#include <iostream>
#include <iomanip> // setw() stream modifier and left flag

// CONTRUCTOR: DEFAULT
View::View()
{
	this-> size = 11;
	this-> scale = 2;
	this-> origin = Cart_Point();
}

// PUBLIC MEMBER FUNCTION
void View::clear()
{
	for (int  xcor = 0; xcor < this-> size; xcor++)
	{
		for (int ycor = 0; ycor < this-> size; ycor++)
		{
			grid[xcor][ycor][0] = '.';
			grid[xcor][ycor][1] = ' ';
		}
	}
}

// PUBLIC MEMBER FUNCTION
void View::plot(Game_Object * gameObjectPtr)
{
	int x ,y;
	// first check if the subscripts are valid
	if (this-> get_subscripts(x, y, gameObjectPtr->get_location()))
	{
		// now check if the cell is empty
		if (this-> grid[x][y][0] == '.')
		{
			gameObjectPtr-> drawself(grid[x][y]);
		}
		else // if not already empty show code for multiple occupancy
		{
			grid[x][y][0] = '*';
			grid[x][y][1] = ' ';
		}
	}
}

// PUBLIC MEMBER FUNCTION
void View::draw()
{
	// prints out the grid onto the screen for the user to see
	// first pitns the axes and then the 

	// we start from high y and low x so the nested for loop has the following starting counters
	for (int y = this-> size - 1; y >= 0; y--)
	{
		// now at every iteration where the size is a multipel of scale, we show the y axis value
		if ( y % static_cast < int > (this-> scale) == 0)
		{
			std::cout << std::setw(2) << std::left << (y * this-> scale);
		}
		else // if not a multiple of scale then just print two spaces as placeholder
		{
			std::cout << std::setw(2) << "  ";
		}
		
		// now print the grid values for the yth row in a nested for loop
		for (int x = 0; x < this-> size; x++)
		{
			std::cout << grid[x][y][0] << grid[x][y][1];
		}

		// now add a newline after each row
		std::cout << std::endl;
	}

	std::cout << "  ";
	// now we still have to print the x axis scale values
	for (int x = 0; x < this-> size; x++)
	{
		if (x % static_cast < int > (this-> scale) == 0)
		{
			std::cout << std::setw(2) << std::left << (x * this-> scale);
		}
		else
		{
			std::cout << "  ";
		}
	}
	// now the final newline to end the grid
	std::cout << std::endl;
}

// PUBLIC MEMBER FUNCTION
bool View::get_subscripts(int & ix, int & iy, Cart_Point location)
{
	// calcualtes the x and y coordinate of the location within the view gird
	// retruns true if the subscripts are valid, false otherwise

	int xSub = (location.x - this-> origin.x) / this-> scale;
	int ySub = (location.y - this-> origin.y) / this-> scale;

	// now check for bounds
	if (xSub > this->size || ySub > this->size || xSub < 0 || ySub < 0)
	{
		std::cout << "Object is outside the game viewfield." << std::endl;
		return false;
	}
	else
	{
		ix = xSub;
		iy = ySub;
		return true;
	}
}