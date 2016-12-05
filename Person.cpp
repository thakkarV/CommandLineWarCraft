#include "Person.h"

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
		std::cout << "Moving " << this-> display_code <<  this-> get_id() << " to " << this-> destination << std::endl;

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

void Person::start_mining(Gold_Mine * minePtr, Town_Hall * hallPtr)
{
	if (this-> is_alive())
	{
		std::cout << "Sorry, I can't work a mine." << std::endl;
	}
	else
	{
		std::cout << this->display_code << this-> get_id() << " id dead." << std::endl;
	}	
}

// PUBLIC MEMBER FUNCTION
void Person::stop()
{
	// change state and print message
	this-> state = 's';
	std::cout << this-> display_code << this-> get_id() << ": Stopped." << std::endl;
}

// PUBLIC MEMBER FUNCTION
void Person::show_status()
{
	std::cout << this-> display_code << this-> get_id() << " at " << this-> get_location() << " ";
	std::cout << "has health " << this-> health << " and ";
	// now check if the person is moving
	if (this-> state == 'm' || this-> state == 'o' || this-> state == 'i' || this-> state == 'd')
	{
		std::cout << "moving at speed of " << this-> speed << " towards "
				  << this-> destination << " at each step of " << this-> delta;
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
	std::cout << "current state of person " << this-> get_id() << " is " << this-> state << std::endl;	
	if (this-> state == 'x')
	{
		return false;
	}
	else return true;
}

// PUBLIC MEMBER FUCTION
void Person::take_hit(int attack_strength)
{
	// check if the health is less than the attac strength
	if (this-> health > attack_strength)
	{
		this-> health -= attack_strength;
	}
	else
	{
		this-> health = 0;
	}

	// now depending upon the health, change state and output message
	if (this-> health <= 0)
	{
		this-> state = 'x';
		std::cout << this-> display_code << this-> get_id() << ": Arrggh!" << std::endl;
	}
	else
	{
		std::cout << this-> display_code << this-> get_id() << ": Ouch!" << std::endl;
	}
}

// PUBLIC MEMBER FUNCITON
void Person::start_attack(Person * tagetPtr)
{
	std::cout << "I can't attack." << std::endl;
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
		// if within one step of destinsation, set current location to destination and true for reaching
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