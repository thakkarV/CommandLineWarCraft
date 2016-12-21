#include "Model.h"
#include "View.h"
#include "Game_Object.h"
#include "Person.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "Miner.h"
#include "Soldier.h"
#include "Inspector.h"
#include "Cart_Point.h"
#include "Game_Command.h"
#include "Input_Handling.h"

#include <list>
#include <deque>

// CONSTRUCTOR: DEFAULT
Model::Model()
{
	this-> time = 0;

	// first instantiate all the linked lists

	person_ptrs.push_back(new Miner(1, Cart_Point(5,1))); // first default miner
	object_ptrs.push_back(person_ptrs.back()); // same pointer in person(0)
	active_ptrs.push_back(object_ptrs.back());

	person_ptrs.push_back(new Miner(2, Cart_Point(10,1))); // second default miner
	object_ptrs.push_back(person_ptrs.back());
	active_ptrs.push_back(object_ptrs.back());

	mine_ptrs.push_back(new Gold_Mine(1, Cart_Point(1,20))); // first default gold mine
	object_ptrs.push_back(mine_ptrs.back());
	active_ptrs.push_back(object_ptrs.back());

	mine_ptrs.push_back(new Gold_Mine(2, Cart_Point(10,20))); // second default gold mine
	object_ptrs.push_back(mine_ptrs.back());
	active_ptrs.push_back(object_ptrs.back());

	hall_ptrs.push_back(new Town_Hall(1, Cart_Point())); // default town hall
	object_ptrs.push_back(hall_ptrs.back());
	active_ptrs.push_back(object_ptrs.back());

	person_ptrs.push_back(new Soldier(3, Cart_Point(5,15))); // first default miner
	object_ptrs.push_back(person_ptrs.back()); // same pointer in person(0)
	active_ptrs.push_back(object_ptrs.back());

	person_ptrs.push_back(new Soldier(4, Cart_Point(10,15))); // second default miner
	object_ptrs.push_back(person_ptrs.back());
	active_ptrs.push_back(object_ptrs.back());

	person_ptrs.push_back(new Inspector(5, Cart_Point(5, 5))); // default inspector
	object_ptrs.push_back(person_ptrs.back());
	active_ptrs.push_back(object_ptrs.back());

	// now assing begin iterators to their variables
	object_itr = object_ptrs.begin();
	active_itr = active_ptrs.begin();
	person_itr = person_ptrs.begin();
	mine_itr = mine_ptrs.begin();
	hall_itr = hall_ptrs.begin();

	std::cout << "Model constructed." << std::endl;
}

// DESTRUCTOR
Model::~Model()
{
	for (object_itr = object_ptrs.begin(); object_itr != object_ptrs.end(); object_itr++)
	{
		delete *object_itr;
	}
	std::cout << "Model destructed." << std::endl;
}

// PUBLIC MEMBER FUNCTION
Person * Model::get_Person_ptr(int id)
{
	for (person_itr = person_ptrs.begin(); person_itr != person_ptrs.end(); person_itr++)
	{
		if ((*person_itr)-> get_id() == id)
		{
			return *person_itr;
		}
	}
	// else return null ptr
	return 0;
}

// PUBLIC MEMBER FUNCTION
Gold_Mine * Model::get_Gold_Mine_ptr(int id)
{
	for (mine_itr = mine_ptrs.begin(); mine_itr != mine_ptrs.end(); mine_itr++)
	{
		if ((*mine_itr)-> get_id() == id)
		{
			return *mine_itr;
		}
	}
	// else return null ptr
	return 0;
}

// PUBLIC MEMBER FUNCTION
Town_Hall * Model::get_Town_Hall_ptr(int id)
{
	for (hall_itr = hall_ptrs.begin(); hall_itr != hall_ptrs.end(); hall_itr++)
	{
		if ((*hall_itr)-> get_id() == id)
		{
			return *hall_itr;
		}
	}
	// else return null ptr
	return 0;
}

// PUBLIC MEMBER FUNCTION
bool Model::update()
{
	this-> time++;
	// iterates throuhg each pointer array and calls its update function
	// retruns true if any of those update functions retrurns true

	int events = 0;
	
	// update all objects in a loop
	for (active_itr = active_ptrs.begin(); active_itr != active_ptrs.end(); active_itr++)
	{
		if ((*active_itr)-> update())
		{
			events++;
		}

		// see if the object is still alive after the update
		if (!(*active_itr)->is_alive()) // object is dead
		{
			active_itr = active_ptrs.erase(active_itr);
		}
	}

	// if number of events is more than one then return true
	if (events > 0)
	{
		return true;
	}
	else return false;
}

// PUBLIC MEMBER FUNCTION
void Model::display(View * view)
{
	// first clear grid
	view-> clear();

	// now plot only the alive objects onto the grid
	for (active_itr = active_ptrs.begin(); active_itr != active_ptrs.end(); active_itr++)
	{
		view-> plot(*active_itr);
	}
	// now draw grid
	view-> draw();
}

// PUBLIC MEMBER FUNCTION
void Model::show_status()
{
	// first show time
	std::cout << "Time: " << this-> time << std::endl;

	// call the show_status() of all objects in a loop
	for (object_itr = object_ptrs.begin(); object_itr != object_ptrs.end(); object_itr++)
	{
		(*object_itr)-> show_status();
	}
}

// PUBLIC MEMBER FUNCTION
void Model::handleNew(char type, char inputID, double xcord, double ycord)
{
	switch (type)
	{
		case 'g' : // GOLDMINE
		{
			// first we error check to see if a mine of the same ID already exists
			Gold_Mine * minePtr = this-> get_Gold_Mine_ptr(inputID);

			// if the mine does not already exists then make it and add it to all the lists
			if (!minePtr)
			{
				this-> mine_ptrs.push_back(new Gold_Mine(inputID, Cart_Point(xcord, ycord)));
				this-> object_ptrs.push_back(mine_ptrs.back());
				this-> active_ptrs.push_back(mine_ptrs.back());
			}
			else
			{
				std::cout << "ID number already exists!" << std::endl;
			}
			break;
		}
		case 't' : // TOWNHALL
		{
			Town_Hall * hallPtr = this-> get_Town_Hall_ptr(inputID);

			if (!hallPtr)
			{
				this-> hall_ptrs.push_back(new Town_Hall(inputID, Cart_Point(xcord, ycord)));
				this-> object_ptrs.push_back(hall_ptrs.back());
				this-> active_ptrs.push_back(hall_ptrs.back());
			}
			else
			{
				std::cout << "ID number already exists!" << std::endl;
			}
			break;
		}
		case 'm' : // MINER
		{
			Person * minerPtr = this-> get_Person_ptr(inputID);

			if (!minerPtr)
			{
				this-> person_ptrs.push_back(new Miner(inputID, Cart_Point(xcord, ycord)));
				this-> object_ptrs.push_back(person_ptrs.back());
				this-> active_ptrs.push_back(person_ptrs.back());
			}
			else
			{
				std::cout << "ID number already exists!" << std::endl;
			}
			break;
		}
		case 's' : // SOLDIER
		{
			Person * soldierPtr = this-> get_Person_ptr(inputID);

			if (!soldierPtr)
			{
				this-> person_ptrs.push_back(new Soldier(inputID, Cart_Point(xcord, ycord)));
				this-> object_ptrs.push_back(person_ptrs.back());
				this-> active_ptrs.push_back(person_ptrs.back());
			}
			else
			{
				std::cout << "ID number already exists!" << std::endl;
			}
			break;
		}
		case 'i' : // INSPECTOR
		{
			Person * inspectorPtr = this-> get_Person_ptr(inputID);

			if (!inspectorPtr)
			{
				this-> person_ptrs.push_back(new Inspector(inputID, Cart_Point(xcord, ycord)));
				this-> object_ptrs.push_back(person_ptrs.back());
				this-> active_ptrs.push_back(person_ptrs.back());
			}
			else
			{
				std::cout << "ID number already exists!" << std::endl;
			}
			break;
		}
		default :
		{
			throw Invalid_Input("Incorrect input parameter for type of new object.");
		}
	}
}

// PUBLIC MEMBER FUNCTION
std::deque< Gold_Mine * > Model::getMinesList()
{
	std::deque< Gold_Mine * > inspectionQueue;

	for (this-> mine_itr = this-> mine_ptrs.begin(); mine_itr != mine_ptrs.end(); mine_itr++)
	{
		inspectionQueue.push_back(*mine_itr);
	}
	return inspectionQueue;
}

// PUBLIC MEMBER FUNCITON
void Model::save(std::ofstream & file)
{
	file << time << std::endl;

	// now we only store the objects that are alive
	file << active_ptrs.size() << std::endl;

	// first we make a catalog of all objects
	for (active_itr = active_ptrs.begin(); active_itr != active_ptrs.end(); active_itr++)
	{
		file << (*active_itr)-> getDisplayCode() << std::endl;
		file << (*active_itr)-> get_id() << std::endl;
		file << (*active_itr)-> get_location().x << std::endl;
		file << (*active_itr)-> get_location().y << std::endl;
	}

	// now save all the object variables
	for (active_itr = active_ptrs.begin(); active_itr != active_ptrs.end(); active_itr++)
	{
		(*active_itr)-> save(file);
	}
}

// PUBLIC MEMBER FUNCITON
void Model::restore(std::ifstream & file)
{
	// first nuke all existing lists
	this-> object_ptrs.clear();
	this-> active_ptrs.clear();
	this-> mine_ptrs.clear();
	this-> hall_ptrs.clear();
	this-> person_ptrs.clear();

	file >> this-> time;

	int objectCount;
	file >> objectCount;
	for (int i = 0; i < objectCount; i++)
	{
		// these five are what i call the "shuttle" variables that hold the value form file before instantiation
		char objectCode;
		int objectID;
		double locationX;
		double locationY;

		// first fill shuttle variables
		file >> objectCode >> objectID >> locationX >> locationY;

		// then instantiate all the game objects with their constructors using shuttles
		if (objectCode == 'G' || objectCode == 'g')
		{
			this-> mine_ptrs.push_back(new Gold_Mine(objectCode, objectID, Cart_Point(locationX, locationY)));
			this-> object_ptrs.push_back(this-> mine_ptrs.back());
		}
		else if (objectCode == 'T' || objectCode == 't')
		{
			this-> hall_ptrs.push_back(new Town_Hall(objectCode, objectID, Cart_Point(locationX, locationY)));
			this-> object_ptrs.push_back(this-> hall_ptrs.back());
		}
		else if (objectCode == 'M' || objectCode == 'm')
		{
			this-> person_ptrs.push_back(new Miner(objectCode, objectID, Cart_Point(locationX, locationY)));
			this-> object_ptrs.push_back(this-> person_ptrs.back());
		}
		else if (objectCode == 'S' || objectCode == 's')
		{
			this-> person_ptrs.push_back(new Soldier(objectCode, objectID, Cart_Point(locationX, locationY)));
			this-> object_ptrs.push_back(this-> person_ptrs.back());
		}
		else if (objectCode == 'I' || objectCode == 'i')
		{
			this-> person_ptrs.push_back(new Inspector(objectCode, objectID, Cart_Point(locationX, locationY)));
			this-> object_ptrs.push_back(this-> person_ptrs.back());
		}
	}
	
	// upon restoration, since dead objects are not saved, the active list is the same as the object list
		active_ptrs = object_ptrs;

		// now get all the object specific stats
		for (active_itr = active_ptrs.begin(); active_itr != active_ptrs.end(); active_itr++)
		{
			(*active_itr)-> restore(file, this);
		}

		std::cout << "Epic Game Restored" << std::endl;
}