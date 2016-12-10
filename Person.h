#ifndef PERSON_H
#define PERSON_H

#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "View.h"

#include <iostream>
#include <math.h> // for fabs() function

class Model;

extern const int VIEW_MAXSIZE;



class Person : public Game_Object
{
public: 
	Person();

	Person(const char in_code);
	// input based constructor also initialises speed
	// Outputs a message "Person default constructed."

	Person(const char in_code, const int in_id, const Cart_Point in_loc);
	// input based constructor that initialises code, id and location
	// Also sets speed and outputs a message screen "Person constructed."

	virtual ~Person();

	void start_moving(const Cart_Point dest);
	// sets the person in motion towards the destination point by calling another function setup_destination()
	// changes state to 'm' for moving and prints "Moving (id) to (destination)."
	// and another message "(display_code)(id): On my way."

	void stop();
	// stops the movement of the person and sets state to 's' for stopped
	// Prints "Stopping (id)." and another message "(display_code)(id): All right."

	virtual void show_status();
	// It first calls Game_Object::show_status(), and then outputs the information
	// contained in this class for the moving state and the stopped state: speed, destination, delta

	virtual void start_mining(Gold_Mine * minePtr, Town_Hall * hallPtr);
	
	/* NOTE:
	 |	get_location is defined in Game_Object.cpp
	 |  get_id is defined in Game_Objectc.pp
	 */

	bool is_alive();
	// returns true if the state is not x, false if it is

	virtual void take_hit(int attack_strength, Person * attackerPtr);
	// decreases health of the person based on the attack level
	
	virtual void start_attack(Person * targetPtr);
	// tells the person to start attacking a given target

	virtual void start_inspecting(Model * model);
	// tells the person to start inspecting

protected:
	bool update_location();
	// Updates the object's location while it is moving
	// prints appropriate update message on the console

	void setup_destination(const Cart_Point dest);
	// Sets up the object to start moving to destination location

	int health;
	// stores the health of the person. default initial is 5

private:
	double speed;
	// The speed this object travels, expressed as distance per update time unit, Initial value 5.

	Cart_Point destination;
	// the destination location coordiate to which the person is headed

	Cart_Vector delta;
	// Contains the x and y amounts that the object will move on each time unit

};

#endif