#include "Person.h"
#include "Game_Object.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Model.h"
#include "View.h"

#include <iostream>
#include <math.h>
#include <fstream>

// CONSTRUCTOR: DEFAULT
Person::Person() {}

// CONSTRUCTOR: INPUT BASED
Person::Person(const char inCode) : Game_Object(inCode, 0)
{
	this-> speed = 5.0;
	this-> health = 5;
	std::cout << "Person default constructed." << std::endl;
}

// CONSTRUCTOR: INPUT BASED
Person::Person(const char inCode, const int inId, const Cart_Point inLoc) : Game_Object(inCode, inId, inLoc)
{
	this-> speed = 5.0;
	this-> health = 5;
	std::cout << "Person constructed." << std::endl;
}

// DISTRUCTOR
Person::~Person()
{
	std::cout << "Person destructed." << std::endl;
}

// PUBLIC MEMBER FUNCTION
void Person::start_moving(const Cart_Point dest)
{
	// first check if the miner is alive or not
	if (this-> is_alive())
	{
		std::cout << "Moving " << this-> display_code <<  this-> get_id() << " to " << dest << std::endl;

		// see if the destination is the same as the location
		if (this-> get_location() == dest)
		{
			std::cout << this-> display_code << this-> get_id() << ": I'm already there. see?" << std::endl;
			return;
		}

		// first setup the destination
		this-> setup_destination(dest);
		// after calling setup destination, it sets the state to moving and prints out message
		this-> state = 'm';
		std::cout << this-> display_code << this-> get_id() << ": On my way." << std::endl;
	}
	else
	{
		std::cout << this->display_code << this-> get_id() << " is dead." << std::endl;
	}
}

// PUBLIC MEMBER FUNCTION
void Person::stop()
{
	// change state and print message
	this-> state = 's';
	std::cout << this-> display_code << this-> get_id() << ": Stopped." << std::endl;
}

// VIRTUAL PUBLIC MEMBER FUNCTION
void Person::show_status()
{
	std::cout << this-> display_code << this-> get_id() << " at " << this-> get_location() << " ";
	// now check if the person is moving
	if (this-> state == 'm' || this-> state == 'o' || this-> state == 'i' || this-> state == 'd')
	{
		std::cout << "moving at speed of " << this-> speed << " towards "
				  << this-> destination << " at each step of " << this-> delta
				  << " with health of " << this-> health;
	}
	// if dieded, print appropriate message
	else if (this-> state == 'x')
	{
		std::cout << "is dead." << std::endl;
	}
	// else print nothing
}

// PUBLIC MEMBER FUNCTION
bool Person::is_alive()
{
	// returns true if the person is alive
	if (this-> state == 'x')
	{
		return false;
	}
	else return true;
}

// VIRTUAL PUBLIC MEMBER FUCTION
void Person::take_hit(int attack_strength, Person * attackerPtr)
{
	// check if the health is less than the attac strength
	if (this-> health > attack_strength)
	{
		this-> health -= attack_strength;

		// change the display code to lower case in case the health goes below 3
		if (this-> health < 3)
		{
			this-> display_code = static_cast < char > ( static_cast < int > (this-> display_code) + 32);
		}

		std::cout << this-> display_code << this-> get_id() << ": Ouch!" << std::endl;
		std::cout << this-> display_code << this-> get_id() << ": I don't wanna fight!" << std::endl;
		// now depending upon the health, change state and output message
	
		// now do the calculations required for running away, first the direction vector and magnitude scaling
		Cart_Point attackerLocation = attackerPtr-> get_location();
		Cart_Vector runningDirection = (this-> location - attackerLocation) * 3.5;

		// now the location to ron to
		Cart_Point runningLocation = Cart_Point(attackerLocation.x + runningDirection.x, attackerLocation.y + runningDirection.y);

		// now bounds check with respect to the edges of the grid
		if (runningLocation.x > VIEW_MAXSIZE)
			runningLocation.x = VIEW_MAXSIZE;

		if (runningLocation.y > VIEW_MAXSIZE)
			runningLocation.y = VIEW_MAXSIZE;

		if (runningLocation.x < 0)
			runningLocation.x = 0;

		if (runningLocation.y < 0)
			runningLocation.y = 0;

		// setup destination
		this-> setup_destination(runningLocation);

		// now MOVE!
		this-> state = 'm';
	}
	else
	{
		this-> health = 0;
		this-> state = 'x';
		std::cout << this-> display_code << this-> get_id() << ": Ahhhh, I am dying." << std::endl;
	}
}

// VIRTUAL PUBLIC MEMBER FUNCTION
void Person::start_mining(Gold_Mine * minePtr, Town_Hall * hallPtr)
{
	std::cout << "Sorry, I can't work a mine." << std::endl;
}

// VIRTUAL PUBLIC MEMBER FUNCITON
void Person::start_attack(Person * tagetPtr)
{
	std::cout << "I can't attack." << std::endl;
}

// VIRTUAL PUBLIC MEMBER FUNCTION
void Person::start_inspecting(Model * model)
{
	std::cout << "Sorry, I cant't inspect." << std::endl;
}

// PROTECTED MEMBER FUNCTION
bool Person::update_location()
{
	// this funciton changes the location of the person object when it is in motion
	// note to self: fabs stands for floating point absolute lol
	double xdiff = fabs(fabs(destination.x) - fabs(location.x));
	double ydiff = fabs(fabs(destination.y) - fabs(location.y));

	if ( (xdiff <= fabs(this-> delta.x) && ydiff <= fabs(this-> delta.y)) || this-> location == this-> destination)
	{
		// if within one step of destination, set current location to destination and true for reaching
		this-> location = this-> destination;
		std::cout << this-> display_code << this-> get_id() << ": I’m there!" << std::endl;
		this-> delta = Cart_Vector(0, 0);
		return true;
	}
	else
	{
		// if not within one step, add the speed delta to location, show steps and return flase
		this-> location = this-> location + this-> delta;
		std::cout << this-> display_code << this-> get_id() << ": step..." << std::endl;
		return false;
	}
}

// PROTECTED MEMBER FUNCTION
void Person::setup_destination(const Cart_Point dest)
{
	this-> destination = dest;
	// changes the destination Cart_Point data member of the person object

	this-> delta = ( (this-> destination - this-> location) * (speed / cart_distance(this-> destination, this-> location)) );
	// also caculates the delta value and changes the data member in person object
}

// PURE VIRTUAL PUBLIC MEMBER FUNCTION
void Person::save(std::ofstream & file)
{
	file << this-> health << std::endl;
	file << this-> speed << std::endl;
	file << this-> destination.x << std::endl;
	file << this-> destination.y << std::endl;
	file << this-> delta.x << std::endl;
	file << this-> delta.y << std::endl;
	file << this-> state << std::endl;
}

// PURE VIRTUAL PUBLIC MEMBER FUNCTION
void Person::restore(std::ifstream & file, Model * model)
{
	file >> this-> health;
	file >> this-> speed;
	file >> this-> destination.x;
	file >> this-> destination.y;
	file >> this-> delta.x;
	file >> this-> delta.y;
	file >> this-> state;
}