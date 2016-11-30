#include "Gold_Mine.h"

// CONSTRUCTOR: DEFAULT
Gold_Mine::Gold_Mine() : Game_Object('G', 0, Cart_Point())
{
	// calls upon the game object constructor with the three default parameters of the gold mine
	this-> state = 'f';
	this-> amount = 100;
	std::cout << "Gold_Mine default constructed." << std::endl;
}

// CONSTRUCTOR: INPUT BASED
Gold_Mine::Gold_Mine(int inputId, const Cart_Point inputLoc) : Game_Object('G', inputId, inputLoc)
{
	// make the game object based on the input parameters
	this-> state = 'f';
	this-> amount = 100;
	std::cout << "Gold_Mine constructed." << std::endl;
}

// DISTRUCTOR
Gold_Mine::~Gold_Mine()
{
	std::cout << "Gold_Mine distructed." << std::endl;
}

/* NOTE:
 |	 get_location is defined in Game_Object.cpp
 |	 get_id is defined in Game_Object.cpp
 */

// PUBLIC MEMBER FUNCTION
bool Gold_Mine::is_empty()
{
	// returns true if mine is empty, otherwise false
	if (amount == 0)
	{
		return true;
	}
	else return false;
}

// PUBLIC MEMBER FUNCTION
double Gold_Mine::dig_gold(double amount_to_dig)
{
	// first we see if amount in mine is greater than amount to be dug
	if (this-> amount > amount_to_dig)
	{
		// if yes we subtract amount dub from amount left in mine and then return that
		this-> amount -= amount_to_dig;
		return amount_to_dig;
	}
	else
	{
		// otherwise we just empty out the gold mine and return whatever was left
		double goldLeft = this-> amount;
		this-> amount = 0;
		return goldLeft;
	}
}

// PURELY VIRTUAL PUBLIC MEMBER FUNCTION
bool Gold_Mine::update()
{
	// state would have been changed last time if it had been called before, so we check with state as well as amount
	if ( (this-> amount == 0) && (this-> state != 'e') )
	{
		this-> state = 'e'; // e for empty
		this-> display_code = 'g'; // display g instead of G on map to show emptyness
		std::cout << "Gold Mine " << this-> get_id() << " has been depleted." << std::endl;
		return true;
	}
	else return false;
}

// VIRTUAL PUBLIC MEMBER FUNCTION
void Gold_Mine::show_status()
{
	// shows mine status as: "Gold Mine status: G1 at location (1,20) Contains 100."
	std::cout << "Gold Mine status: ";
	Game_Object::show_status();
	std::cout << "Contains " << this-> amount << "." << std::endl;
}