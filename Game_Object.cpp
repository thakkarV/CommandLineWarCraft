#include "Game_Object.h"
#include "Cart_Point.h"
#include "Model.h"

#include <iostream>
#include <fstream>

Game_Object::Game_Object() {}

Game_Object::Game_Object(char in_code, int in_id)
{
	this->display_code = in_code;
	this->id_num = in_id;
	this->location = Cart_Point();
	std::cout << "Game_Object default constructed." << std::endl;
}

Game_Object::Game_Object(char in_code, int in_id, Cart_Point in_loc)
{
	this->display_code = in_code;
	this->id_num = in_id;
	this->location = in_loc;
	std::cout << "Game_Object constructed." << std::endl;
}

// DISTRUCTOR
Game_Object::~Game_Object()
{
	std::cout << "Game_Object destructed." << std::endl;
}

// PUBLIC MEMBER FUNCTION
void Game_Object::drawself(char * pointer)
{
	// puts the disiplay code at the place of char pointer
	// and the ID number at the memloc after the pointer as cahrecters
	*pointer  = this-> display_code;
	int charnum = id_num + static_cast < int > ('0');
	*(pointer + 1) = static_cast < char > (charnum);
}

// PUBLIC MEMBER FUNCTION
Cart_Point Game_Object::get_location()
{
	return this-> location;
}

// PUBLIC MEMBER FUNCTION
int Game_Object::get_id()
{
	// returns the integer id of the mine
	return this-> id_num;
}

// VIRTUAL PUBLIC MEMBER FUNCTION
void Game_Object::show_status()
{
	std::cout << this-> display_code << this-> id_num << " at location " << this-> location << " ";
}

// VIRTUAL PUBLIC MEMBER FUNCTION
bool Game_Object::is_alive()
{
	// this virtual will always return true
	// subdefintions is each derivation of person class
	return true;
}

// PUBLIC MEMBER FUNCTION
char Game_Object::getDisplayCode()
{
	return this-> display_code;
}