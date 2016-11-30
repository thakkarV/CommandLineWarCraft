#include "Model.h"

// CONSTRUCTOR: DEFAULT
Model::Model()
{
	this-> time = 0;

	// now we make the default game objects

	person_ptrs[0] = new Miner(1, Cart_Point(5,1)); // first default miner
	object_ptrs[0] = person_ptrs[0]; // same pointer in person(0)

	person_ptrs[1] = new Miner(2, Cart_Point(10,1)); // second default miner
	object_ptrs[1] = person_ptrs[1];

	mine_ptrs[0] = new Gold_Mine(1, Cart_Point(1,20)); // first default gold mine
	object_ptrs[2] = mine_ptrs[0];

	mine_ptrs[1] = new Gold_Mine(2, Cart_Point(10,20)); // second default gold mine
	object_ptrs[3] = mine_ptrs[1];

	hall_ptrs[0] = new Town_Hall(1, Cart_Point()); // default town hall
	object_ptrs[4] = hall_ptrs[0];

	person_ptrs[2] = new Soldier(3, Cart_Point(5,15)); // first default miner
	object_ptrs[5] = person_ptrs[2]; // same pointer in person(0)

	person_ptrs[3] = new Soldier(4, Cart_Point(10,15)); // second default miner
	object_ptrs[6] = person_ptrs[3];


	// so at the start we have a total of 5 game objects
	num_objects = 7;

	// 2 miners, 2 gold mines and 1 town hall
	num_persons = 4;
	num_mines = 2;
	num_halls = 1;

	std::cout << "Model constructed." << std::endl;
}

// DESTRUCTOR
Model::~Model()
{
	for (int i = 0; i < this->num_objects; i++)
	{
		delete object_ptrs[i];
	}
	std::cout << "Model destructed." << std::endl;
}

// PUBLIC MEMBER FUNCTION
Person * Model::get_Person_ptr(int id)
{
	for (int i = 0; i < this-> num_persons; i++)
	{
		if (this-> person_ptrs[i]-> get_id() == id)
		{
			return person_ptrs[i];
		}
	}
	// else return null ptr
	return 0;
}

// PUBLIC MEMBER FUNCTION
Gold_Mine * Model::get_Gold_Mine_ptr(int id)
{
	for (int i = 0; i < this-> num_mines; i++)
	{
		if (this-> mine_ptrs[i]-> get_id() == id)
		{
			return this-> mine_ptrs[i];
		}
	}
	// else return null ptr
	return 0;
}

// PUBLIC MEMBER FUNCTION
Town_Hall * Model::get_Town_Hall_ptr(int id)
{
	for (int i = 0; i < this-> num_halls; i++)
	{
		if (this-> hall_ptrs[i]-> get_id() == id)
		{
			return this-> hall_ptrs[i];
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
	// first update all persons
	for (int i = 0; i < this-> num_objects; i++)
	{
		if ( this-> object_ptrs[i]-> update() )
		{
			events++;
		}
	}

	// now check if any values in the vector are true, and if yes, return ture
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

	// now plot everything into the cleared grid
	for (int i = 0; i < this-> num_objects; i++)
	{
		// we only draw the object if it is alive
		if (this-> object_ptrs[i]-> is_alive())
		{
			view-> plot(this-> object_ptrs[i]);
		}
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
	for (int i = 0; i < this-> num_objects; i++)
	{
		this-> object_ptrs[i]-> show_status();
	}
}