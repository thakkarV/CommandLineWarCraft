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

#include <iostream>

class Model
{
public:
	// DEFAULT CONSTRUCTOR
	Model();

	// DESTRUCTOR
	~Model();

	// Lookup and validation functions for each array of pointers
	Person * get_Person_ptr(int id);
	Gold_Mine * get_Gold_Mine_ptr(int id);
	Town_Hall * get_Town_Hall_ptr(int id);

	// update function for the model
	bool update();

	// updates the view field of the game
	void display(View * view);

	// outputs the status of all the game objects by calling their show status function
	void show_status();
	
private:
	int time;
	// stores the current time tick of the game

	Game_Object * object_ptrs[10];
	// array of pointers to all game objects
	int num_objects; 
	// stores the number of game objects = size of object_ptrs[]

	Person * person_ptrs[10];
	// array of pointers to all person objects in game
	int num_persons;
	// stores the number of person objects = size of person_pters[]

	Gold_Mine * mine_ptrs[10];
	// array of pointers to all game mines in the game
	int num_mines;
	// stores the number of gold mines = size of mine_ptrs[]

	Town_Hall * hall_ptrs[10];
	// array of pointers to all town halls in the game
	int num_halls;
	// stores the number of all town halls = size of hall_ptrs[]

	// PRIVATE COPY CONSTRUCTOR
	Model(const Model & object);

};

#endif