#ifndef TOWN_HALL_H
#define TOWN_HALL_H

#include "Cart_Point.h"
#include "Game_Object.h"

#include <iostream>

class Town_Hall : public Game_Object
{
public:
	Town_Hall();
	// CONSTRUCTOR: DEFAULT

	Town_Hall(const int inputId, const Cart_Point inputLoc);
	// CONSTRUCTOR: INPUT BASED

	~Town_Hall();
	// DISTRUCTOR

	/* NOTE:
	 |	get_location is defined in Game_Object.cpp
	 |  get_id is defined in Game_Objectc.pp
	 */

	void deposit_gold(const double deposit_amount); // member
	// adds the amount of input gold to the amount in town hall

	bool update(); // purely virtual member
	// If the Town_Hall has gold greater than or equal to 50, 
	// it sets the state to ‘u’ for “Upgraded”, change display_code to ‘T’,
	// prints the message “Town_Hall (idnumber) has been upgraded.” 
	// and lastly, returns true. Returns false if it does not have enough gold.
	// only returns true the first time the town hall gets upgraded. False afterwards.

	void show_status(); // virtual member

private:

	double amount;
	// stores the amount of gold in town hall. default initial 0

	/*
	 |	// char display_code; default initial ‘t’, 'T' for upgraded
	 |	// int id_num 
	 |	// char state; default initial ‘o’ for original level, 'u' for upgraded
	 |	// Cart_Point location; default initial (0.0, 0.0)
	 */

};

#endif