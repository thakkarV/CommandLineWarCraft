#ifndef GOLD_MINE_H
#define GOLD_MINE_H

#include "Game_Object.h"

#include <fstream>

// gold mine is a derived object of game object
class Gold_Mine : public Game_Object
{	
public:
	Gold_Mine();
	//CONSTRUCTOR: DEFAULT
	
	Gold_Mine(const int inputId, const Cart_Point inputLoc);
	// CONSTRUCTOR: INPUT BASED

	Gold_Mine(const char inputCode, const int inputId, const Cart_Point inputLoc);
	// CONSTRUCTOR: INPUT BASED

	~Gold_Mine();
	// distructor only outputs message
	
	/* NOTE:
	 |	get_location is defined in Game_Object.cpp
	 |  get_id is defined in Game_Object.cpp
	 */

	bool is_empty(); // member
	// returns true if the mine is out of gold, false otherwise

	double dig_gold(double amount_to_dig = 35.0); // member
	// IF amount of gold in gold mine is greater than amount to dig then subtract that much from the mine
	// and then return the amount dug
	// IF it is less, return the current amount of gold in mine and set gold in mine to 0 (empty)

	bool update(); // purely virtual member
	// IF the gold mine empties out, sets the state memvar as 'e' for empty,
	// and chages display_code to 'g', and prints meesage “Gold_Mine (id number) has been depleted.”
	// and returns true. IF not depleted, then returns flase
	// NOTE: update shoul only return true once when the values are changed, and not after that
	// so even if an update has been made, it will not return true the next time it is called

	void show_status(); // virtual member
	// prints out the status of the gold mine object, including display_code, id_num, location,
	// and the amount of gold. See the sample output for the format.

	double getGoldAmount();
	// getter for the private gold amount avariable, used for the inspector class

	void save(std::ofstream & file);
	// saves state to file

	void restore(std::ifstream & file, Model * model);
	// loads state from file

private:
	
	double amount;
	// The amount of gold currently in the mine. default initial 100

	/*
	 |	// char display_code; default initial ‘G’, 'g' for empty
	 |	// int id_num 
	 |	// char state; default initial ‘f’ for full, 'e' when empty
	 |	// Cart_Point location; default initial (0.0, 0.0)
	 */

};

#endif