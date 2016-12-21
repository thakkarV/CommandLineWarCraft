#include "Town_Hall.h"
#include "Game_Object.h"
#include "Cart_Point.h"
#include "Model.h"

#include <iostream>
#include <fstream>

// CONSTRUCTOR: DEFAULT
Town_Hall::Town_Hall() : Game_Object('t', 0, Cart_Point())
{
	this-> state = 'o';
	this-> amount = 0;
	std::cout << "Town_Hall default constructed." << std::endl;
}

// CONSTRUCTOR: INPUT BASED
Town_Hall::Town_Hall(const int inputId, const Cart_Point inputLoc) : Game_Object('t', inputId, inputLoc)
{
	this-> state = 'o';
	this-> amount = 0;
	std::cout << "Town_Hall constructed." << std::endl;
}

// CONSTRUCTOR: INPUT BASED
Town_Hall::Town_Hall(const char inputCode, const int inputId, const Cart_Point inputLoc) : Game_Object(inputCode, inputId, inputLoc)
{
	this-> state = 'o';
	this-> amount = 0;
	std::cout << "Town_Hall constructed." << std::endl;
}

// DISTRUCTOR
Town_Hall::~Town_Hall()
{
	std::cout << "Town_Hall destructed." << std::endl;
}

// PUBLIC MEMBER FUNCTION
void Town_Hall::deposit_gold(const double deposit_amount)
{
	this-> amount += deposit_amount;
}

// PURELY VIRTUAL PUBLIC MEMBER FUNCTION
bool Town_Hall::update()
{
	// state would have been changed last time if it had been called before, so we check with state as well as amount
	if ( (this-> amount >= 50) && (this-> state != 'u') )
	{
		this-> state = 'u'; // u for upgraded
		this-> display_code = 'T'; // display T instead of t on map to show upgrade
		std::cout << this-> display_code << this-> get_id() << " has been upgraded." << std::endl;
		return true;
	}
	else return false;
}

// VIRTUAL PUBLIC MEMBER FUNCTION
void Town_Hall::show_status()
{
	// shows town hall status as: "Town hall status: T1 at location (1,20) Contains 100."
	std::cout << "Town Hall status: " << this-> display_code << this-> get_id();
	std::cout << " at " << this-> get_location() << " contains " << this-> amount << " of gold. ";

	if (this-> display_code == 't')
	{
		std::cout << "Not yet upgraded." << std::endl; 
	}
	else
	{
		std::cout << "Upgraded." << std::endl; 
	}
}

// PURE IRTUAL PUBLIC MEMBER FUNCTION
void Town_Hall::save(std::ofstream & file)
{
	file << this-> amount << std::endl;
	file << this-> state << std::endl;
}

// PURE VIRTUAL PUBLIC MEMBER FUNCTION
void Town_Hall::restore(std::ifstream & file, Model * model)
{
	file >> this-> amount;
	file >> this-> state;
}