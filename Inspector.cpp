#include "Inspector.h"
#include "Model.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Person.h"
#include "Input_Handling.h"

#include <math.h>
#include <fstream>
#include <iostream>
#include <deque>
#include <list>

// CONSTRUCTOR: DEFUALT
Inspector::Inspector() : Person('I')
{
	this-> state = 's';
}

// CONSTRUCTOR: INPUT BASED
Inspector::Inspector(const int inId, const Cart_Point inLoc) : Person('I', inId, inLoc)
{
	this-> state = 's';
}

// CONSTRUCTOR: INPUT BASED
Inspector::Inspector(const char inputCode, const int inId, const Cart_Point inLoc) : Person(inputCode, inId, inLoc)
{
	this-> state = 's';
}

// DESTRUCTOR
Inspector::~Inspector()
{
	std::cout << "Inspector destructed." << std::endl;
}

// PURE VIRTUAL PUBLIC MEMEBR FUNCITON
bool Inspector::update()
{
	switch (this-> state)
	{
		case 's' : // STOPPED
		{
			return false;
		}
		case 'm' : // MOVING
		{
			// call update_location function in parent person to change location
			if (update_location())
			{
				this-> state = 's'; // if arrived, set state to stopped

				return true;
			}
			else 
			{
				return false;
			}
		}
		case 'o' : // OUTBOUND MOVE : forward pass inspection
		{
			if (this-> update_location())
			{
				this-> state = 'g';
				return true;
			}
			else
			{
				return false;
			}
		}
		case 'g' : // OUTBOUND INSPECT : forward pass inspection state
		{
			// first report on the mine
			double mineAmount = this-> destMinePtr-> getGoldAmount();
			std::cout << this-> display_code << this-> get_id() 
					  << ": this mine contains " << mineAmount << " gold." << std::endl;

			// also record the gold value into the vector
			forwardPassGold.push_back(mineAmount);

			// now we get the next mine to inspect
			if (inspectionQueue.size())
			{
				// if there are still more mines left for outbound inspection, then get the closest mine in queue
				Gold_Mine * destMinePtr = findClosestMine(this-> inspectionQueue);

				// push the closest mine onto the order of inspection list
				this-> inspectionOrder.push_back(destMinePtr);

				// set destination for the next mine of inspection
				this-> setup_destination(destMinePtr-> get_location());

				// finally go to outbound state again and retrun			
				this-> state = 'o';
				return false;
			}
			else
			{
				// if there are not more mines left for outboud inspection then start reverse inspection
				// first we delete the last gold mine pointer we just put in since we are already there
				// and  also the last value within the gold amount vector
				this-> inspectionOrder.pop_back();
				this-> forwardPassGold.pop_back();

				// then get the pointer of the first  mine to reverse inspect
				this-> destMinePtr = this-> inspectionOrder.back();

				// setup destination to the reverse mine
				this-> setup_destination(this-> destMinePtr-> get_location());

				this-> state = 'i';
				return false;
			}
		}
		case 'i' : // INBOUND MOVE : reverse pass inspection
		{
			if (this-> update_location())
			{
				this-> state = 'r';
				return true;
			}
			else
			{
				return false;
			}
		}
		case 'r' : // INBOUND INSPECT : reverse pass inspection state
		{
			// first get the new value  of gold from the mine
			double updatedAmount = destMinePtr-> getGoldAmount();

			// now display the delta of the amount
			double deltaGold = forwardPassGold.back() - updatedAmount;
			std::cout << "Amount of gold removed from mine is " << deltaGold << " gold." << std::endl;

			// delete extracted pointer and delete the last amount in the amount deque
			this-> inspectionOrder.pop_back();
			this-> forwardPassGold.pop_back();

			// check if there are more mines left to reverse traverse
			if (this-> inspectionOrder.size())
			{
				// get the pointer of the next mine to reverse inspect
				this-> destMinePtr = this-> inspectionOrder.back();

				// setup destination to the reverse mine
				this-> setup_destination(destMinePtr-> get_location());
				
				this-> state = 'i';
				return false;
			}
			else
			{
				std::cout << this-> display_code << this-> get_id() << ": Finished inspection. Returning to starting point." << std::endl;
				this-> setup_destination(startLocation);
				this-> state = 'm';
			}
		}
		case 'x' : // DIEDED
		{
			return false;
		}
	}
}

void Inspector::show_status()
{
	std::cout << "Inspector status: ";
	Person::show_status();

	switch (this-> state)
	{
		case 's' : // STOPPED
		{
			std::cout << "is stopped." << std::endl;
			break;
		}
		case 'o' : // OUTBOUND
		{
			std::cout << "is outbound to inspect." << std::endl;
			break;
		}
		case 'i' : // INBOUND
		{
			std::cout << "is inbound from inspection" << std::endl;
			break;
		}
		case 'g' : // INSPECTING
		{
			std::cout << "is doing outbound inspection." << std::endl;
			break;
		}
		case 'r' : // REPORTING
		{
			std::cout << "is doing inbound inspection." << std::endl;
			break;
		}
	}
}

// PUBLIC MEMBER FUNCTION
void Inspector::start_inspecting(Model * model)
{
	if (this-> is_alive())
	{
		std::cout << this-> display_code << this-> get_id() << ": starting to inspect." << std::endl;

		// first we clear all the lists and queues for inspection in case of a command interrupt
		this-> inspectionQueue.clear();
		this-> inspectionOrder.clear();
		this-> forwardPassGold.clear();


		// first get the list of mines to be inspected and store current location into startLocation
		this-> inspectionQueue = model-> getMinesList();
		this-> startLocation = this-> location;

		// check for empty mine list
		if (inspectionQueue.size() == 0)
		{
			this-> state = 's';
			throw Invalid_Input("No mines avaliable to inspect.");
		}

		// now find the closest mine
		destMinePtr = findClosestMine(this-> inspectionQueue);

		// then setup destination to that mine and change state to outbound
		Cart_Point destMineLocation = destMinePtr-> get_location();
		this-> setup_destination(destMineLocation);
		this-> inspectionOrder.push_back(destMinePtr);
		this-> state = 'o';
	}
	else
	{
		throw Invalid_Input("Inspector is dead.");
	}
}

// PRIVATE MEMBER FUNCTION
Gold_Mine * Inspector::findClosestMine(std::deque< Gold_Mine * > inspectionQueue)
{
	// calcualtr distence to all mines
	double currentDistance = 0;
	double previousDistence = cart_distance(this-> location, (*this-> inspectionQueue.begin())-> get_location());
	Gold_Mine * closestMinePtr = *(inspectionQueue.begin());
	std::deque< Gold_Mine * >::iterator closestMineItr;

	for (this-> inspectionQueueItr = (this->inspectionQueue.begin()); inspectionQueueItr != (this->inspectionQueue.end()); this->inspectionQueueItr++)
	{
		currentDistance = cart_distance(this-> location, (*inspectionQueueItr)-> get_location());
		if (currentDistance <= previousDistence)
		{
			closestMinePtr = *inspectionQueueItr;
			closestMineItr = inspectionQueueItr;
		}

		previousDistence = currentDistance;
	}
	// delete the now obtained pointer to the closestMinePtr from the inspection queue
	this-> inspectionQueue.erase(closestMineItr);

	return closestMinePtr;
}

// VIRTUAL PUBLIC MEMBER FUNCTION
void Inspector::save(std::ofstream & file)
{
	this-> Person::save(file);

	file << this-> startLocation.x << std::endl;
	file << this-> startLocation.y << std::endl;

	// first save the ID of the current destination mine
	if (this-> destMinePtr)
	{
		file << this-> destMinePtr-> get_id() << std::endl;
	}
	else
	{
		file << -1 << std::endl;
	}
	
	// first save the whole inspection queue
	file << this-> inspectionQueue.size() << std::endl;
	for (inspectionQueueItr = inspectionQueue.begin(); inspectionQueueItr != inspectionQueue.end(); inspectionQueueItr++)
	{
		file << (*inspectionQueueItr)-> get_id() << std::endl;
	}

	// now save the whole inspectionOrder list
	file << this-> inspectionOrder.size() << std::endl;
	for (inspectionOrderItr = inspectionOrder.begin(); inspectionOrderItr != inspectionOrder.end(); inspectionOrderItr++)
	{
		file << (*inspectionOrderItr)-> get_id() << std::endl;
	}

	// now save the forwardPassGold vector
	file << this-> forwardPassGold.size() << std::endl;
	for (forwardPassGoldItr = forwardPassGold.begin(); forwardPassGoldItr != forwardPassGold.end(); forwardPassGoldItr++)
	{
		file << (*forwardPassGoldItr) << std::endl;
	}
}

// VIRTUAL PUBLIC MEMBER FUNCTION
void Inspector::restore(std::ifstream & file, Model * model)
{
	// first reset all three containers
	this-> inspectionQueue.clear();
	this-> inspectionOrder.clear();
	this-> forwardPassGold.clear();

	// now start resore
	this-> Person::restore(file, model);

	file >> this-> startLocation.x;
	file >> this-> startLocation.y;

	// first desination mine
	int destMineID;
	file >> destMineID;

	if (destMineID == -1)
	{
		this-> destMinePtr = 0;
	}
	else
	{
		this-> destMinePtr = model-> get_Gold_Mine_ptr(destMineID);
	}

	// restore the deque first
	int queueSize;
	file >> queueSize;
	int mineID;
	for (int i = 0; i < queueSize; i++)
	{
		file >> mineID;
		this-> inspectionQueue.push_back(model-> get_Gold_Mine_ptr(mineID));
	}

	// restore the list next
	int listSize;
	file >> listSize;
	for (int i = 0; i < listSize; i++)
	{
		file >> mineID;
		this-> inspectionOrder.push_back(model-> get_Gold_Mine_ptr(mineID));
	}

	// restore the vector last
	int vectorSize;
	file >> vectorSize;
	double gold;
	for (int i = 0; i < vectorSize; i++)
	{
		file >> gold;
		this-> forwardPassGold.push_back(gold);
	}
}