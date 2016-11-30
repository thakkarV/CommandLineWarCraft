#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Cart_Point.h"
#include <iostream>

class Game_Object
{

public:
	Game_Object();
	
	Game_Object(char in_code, int in_id);
	// Initializes the display_code, id_num, and location to (0,0)
	// It outputs the message: “Game_Object default constructed.”

	Game_Object(char in_code, int in_id, Cart_Point in_loc);
	// initialize with custom location point
	// It outputs the message: “Game_Object constructed.”

	virtual ~Game_Object();
	// distructor that prints message confirmation of distruction

	void drawself(char * pointer);
	// puts the display code at the place of the char pointer and the id num at the location after the pointer

	Cart_Point get_location();
	// returns the location for this derived object

	int get_id();
	// returns the id_num of this derived object

	virtual void show_status();
	// Outputs the information contained in this class: display_code, id_num, location
	// i.e. “<display_code> with ID <id_num> at location <location>”

	virtual bool update() = 0;
	// virtual function that updates the properties of the derieved class in one fell swoop

	virtual bool is_alive();
	// always returns true from game object if derived definiton not specified

protected:
	// locatin of the derived object
	Cart_Point location;

	// how the derived object is represented in view
	char display_code;

	// state of the object
	char state;

private:
	// id number of the object
	int id_num;

};

#endif