#include "Soldier.h"

// CONSTRUCTOR: DEFAULT
Soldier::Soldier() : Person('S')
{
	this-> range = 2.0;
	this-> state = 's';
	this-> attack_strength = 2;
	this-> target = 0; // NULL pointer
	std::cout << "Soldier default constructed." << std::endl;
}

// CONSTRUCTOR: INPUT BASED
Soldier::Soldier(const int inId, const Cart_Point inLoc) : Person('S', inId, inLoc)
{
	this-> range = 2.0;
	this-> state = 's';
	this-> attack_strength = 2;
	this-> target = 0; // NULL pointer
	std::cout << "Soldier constructed." << std::endl;
}

// DISTRUCTOR
Soldier::~Soldier()
{
	std::cout << "Soldier destructed." << std::endl;
}

// VIRTUAL PUBLIC MEMBER FUNCTION
void Soldier::start_attack(Person * targetPtr)
{
	// first check if the sodier is alive or not
	if (this-> is_alive())
	{
		// first we get the location of the person to be attacked
		Cart_Point attackLocatoin = targetPtr-> get_location();

		// now calculate the distence between the two
		double attackDistance = cart_distance(this-> location, attackLocatoin);

		// now we check if the person is within the attack range of the soldier
		if (attackDistance <= this-> range)
		{
			// if within range of attack, setup state so that update can have some hammer time!
			this-> target = targetPtr;
			this-> state = 'a';
			std::cout << this-> display_code << this-> get_id() << ": Attacking!" << std::endl;
		}
		else
		{
			// if too far, just print out of range
			std::cout << this-> display_code << this-> get_id() << ": Target is out of range." << std::endl;
		}
	}
	else
	{
		throw Invalid_Input("Soldier is dead.");
	}
}

// VIRTUAL PUBLIC MEMBER FUNCTION
bool Soldier::update()
{
	switch (this-> state)
	{
		case 's' : // stopped
		{
			// do nothing and retrun false
			return false;
		}
		case 'm' : // moving
		{
			// call update_location function in parent person to change location
			if (update_location())
			{
				this-> state = 's'; // if arrived, set state to stopped

				return true;
			}
			else return false;
		}
		case 'a' : // attacking
		{
			// first check distence to target once again
			double attackDistance = cart_distance(this-> location, this-> target-> get_location());

			// if within the range of attack...
			if (attackDistance <= this-> range)
			{
				// and if it is still alive...
				if (this-> target-> is_alive())
				{
					// then attack the target
					this-> target-> take_hit(this-> attack_strength, this);
					// and then print message
					std::cout << this-> display_code << this-> get_id() << ": Clang!" << std::endl;
					return false;
				}
				else
				{
					// if the target dieded, stop and gloat
					this-> state = 's';
					std::cout << this-> display_code << this-> get_id() << ": I triumph!" << std::endl;
					return true;
				}
			}
			else
			{
				// if the target is out of range, print message, stop
				this-> state = 's';
				std::cout << this-> display_code << this-> get_id() << ": Target out of range." << std::endl;
				return true;
			}
		}
		case 'x' : // dieded
		{
			// if dieded do nothing and return false
			return false;
		}
	}
}

// VIRTUAL PUBLIC MEMBER FUNCTION
void Soldier::show_status()
{
	std::cout << "Soldier status: ";
	Person::show_status();
	switch (this-> state)
	{
		case 's' : // stopped
		{
			std::cout << "is stopped." << std::endl;
			break;
		}
		case 'm' : // moving
		{
			std::cout << std::endl;
			break;
		}
		case 'a' : // attacking
		{
			std::cout << "is attacking." << std::endl;
			break;
		}
	}
}

// VIRTUAL PUBLIC MEMBER FUNCTION
void Soldier::take_hit(int attack_strength, Person * attackerPtr)
{
	// check if the health is less than the attac strength
	if (this-> health > attack_strength)
	{
		this-> health -= attack_strength;

		// change the display code to lower case in case the health goes below 3
		if (this-> health < 3)
		{
			this-> display_code = static_cast < char > ( (static_cast < int > (this-> display_code)) + 32);
		}

		// start attacking the enemy soldier back if not yet dead
		this-> start_attack(attackerPtr);
		this-> state = 'a';
	}
	else
	{
		this-> health = 0;
		this-> state = 'x';
		std::cout << this-> display_code << this-> get_id() << ": Arrggh!" << std::endl;
	}
}