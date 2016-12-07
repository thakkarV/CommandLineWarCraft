#ifndef MODEL_H
#define MODEL_H 

#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "Miner.h"
#include "Person.h"
#include "View.h"
#include "Soldier.h"
#include "Input_Handling.h"

#include <iostream>
#include <list>

class Model
{
public:
	// DEFAULT CONSTRUCTOR
	Model();

	// DESTRUCTOR
	~Model();

	// Lookup and validation functions for each linked list of pointers
	Person * get_Person_ptr(int id);
	Gold_Mine * get_Gold_Mine_ptr(int id);
	Town_Hall * get_Town_Hall_ptr(int id);

	// update function for the model
	bool update();

	// updates the view field of the game
	void display(View * view);

	// outputs the status of all the game objects by calling their show status function
	void show_status();

	// this function makes the new object input to it when called upon by game command
	void handleNew(char type, char inputID, double xcord, double ycord);
	
private:
	int time;
	// stores the current time tick of the game

	// linked list of pointers to all game objects and assosiated start iterator
	std::list < Game_Object * > object_ptrs;
	std::list<Game_Object * >::iterator object_itr;

	// linked list of alive game object and associated start iterators
	std::list < Game_Object * > active_ptrs;
	std::list< Game_Object * >::iterator active_itr;

	// linked list of pointers to all person objects in game and assosicated start iterator
	std::list < Person * > person_ptrs;
	std::list< Person * >::iterator person_itr;

	// linked list of pointers to all game mines in the game and associated start iterator
	std::list < Gold_Mine * > mine_ptrs;
	std::list< Gold_Mine * >::iterator mine_itr;
	
	// linked list of pointers to all town halls in the game and associated start iterator
	std::list < Town_Hall * > hall_ptrs;
	std::list< Town_Hall * >::iterator hall_itr;

	// PRIVATE COPY CONSTRUCTOR
	Model(const Model & object);

};

#endif