#ifndef MINER_H
#define MINER_H

#include "Person.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"

class Miner : public Person
{

public:
	Miner();
	// invokes parent constructor with a single char argument Person('M')
	// initialises the amount to 0 and mine and home pointers to NULL
	// outputs message "Miner default constructed."

	Miner(const int in_id, const Cart_Point in_loc);
	// input based constructor that invokes the corresponding input based constructor of parent Person
	// also initialises the amount to 0 and outputs message "Miner constructed."

	~Miner();
	
	bool update();
	// returns true when onject is changed
	// Updates the status of the object on each time unit

	void start_mining(Gold_Mine * inputMine, Town_Hall * inputHome);
	// sets miner to start mining: move gold from input mine to input town hall
	// calls setup_destination() to decide where to go
	// changes miner status to 'o' for outbound
	// Prints "Miner (id) mining at Gold_Mine (id) and depositing at Town_Hall (id)." 
	// and another message "(display_code)(id): Yes, my lord."

	Cart_Point get_location();
	// returns a cart point object which contains the coordiates of the miner
	// It also calls show status by itself which is a member function of its parent class, person
	// entire output is "Miner status: M1 at (5,1) moving at speed of 5 towards (0,0) at each step of <0,0>"

	/* NOTE:
	 |  get_id is defined in Game_Objectc.pp
	 */

	void show_status();

private:

	double amount;
	// amount of gold that the miner is carrying

	Gold_Mine * mine;
	// pointer to the mind objec that the miner is minign from. default initial is NULL

	Town_Hall * home;
	// town hall that the miner is depositing to. default initial is NULL

	/*
	 |	// char display_code; default initial ‘M’
	 |	// int id_num 
	 |	// char state; default initial ‘s’ for stopped, 'm' for moving, 'o' for outbound
	 |	// Cart_Point location; default initial (0.0, 0.0)
	 */

};


#endif