#include "Game_Command.h"

void move(Model * model, View * view, int personID, double xcord, double ycord)
{
	// first try to get the pointer to the person we are trying to move
	Person * personPtr = model-> get_Person_ptr(personID);
	if (personPtr != 0)
	{
		// if the minser exists then set it moving towards that location
		personPtr-> start_moving(Cart_Point(xcord, ycord));
		// moving message will be displayed by start_moving function from person.cpp
	}
	model-> display(view);
}

void work(Model * model, View * view, int personID, int mineID, int hallID)
{
	// first get all the three pointers from the model
	Person * personPtr = model-> get_Person_ptr(personID);
	Miner * minerPtr = dynamic_cast < Miner * > (personPtr);
	Gold_Mine * minePtr = model-> get_Gold_Mine_ptr(mineID);
	Town_Hall * hallPtr = model-> get_Town_Hall_ptr(hallID);

	if ((minerPtr != 0) && (minePtr != 0) && (hallPtr != 0))
	{
		minerPtr-> start_mining(minePtr, hallPtr);
		// mining message will be displayed by the start_minig function in miner.cpp
	}
    model-> display(view);
}

void attack(Model * model, View * view, int soldierID, int personID)
{
	Person * soldierPtr = model-> get_Person_ptr(soldierID);
	Person * personPtr = model-> get_Person_ptr(personID);

	if ((soldierPtr != 0) && (personPtr != 0))
	{
		// if both ID numbers were valid then start attacking	
		soldierPtr-> start_attack(personPtr);
	}
	model-> display(view);
}

void stop(Model * model, View * view, int personID)
{
	// get pointer first
	Person * personPtr = model->get_Person_ptr(personID);
	if (personPtr != 0)
	{
		personPtr->stop();
		// stopping message will by ouput by the stop function in person.cpp
	}
	model-> display(view);
}

void go(Model * model, View * view)
{
	std::cout << "Advancing one tick." << std::endl;
	bool throwaway = model->update();
	model-> show_status();
	model-> display(view);
}

void run(Model * model, View * view)
{
	std::cout << "Advancing to next event." << std::endl;
	bool throwaway = false;
	int counter = 0;
	while (!throwaway && counter < 5)
	{
		throwaway = model-> update();
		counter++;
	}
	model-> show_status();
	model-> display(view);
}

void list(Model * model)
{
	// this function is intended to only show the current status of all game objects
	// without advancing time, giving any commands to any objects or re-drawing the grid
	model-> show_status();
}

bool quitGame(Model * model)
{
	std::cout << "Terminating program." << std::endl;
	delete model;
	return false;
}