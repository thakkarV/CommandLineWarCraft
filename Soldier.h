#ifndef SOLDIER_H
#define SOLDIER_H

#include "Person.h"
#include "Input_Handling.h"

#include <iostream>

class Soldier : public Person
{
public:
	Soldier();

	Soldier(const int inId, const Cart_Point inLoc);

	~Soldier();

	void start_attack(Person * targetPtr);
	// sets up the soldier to attack the person pointer to by the input pointer, virtual in parent person

	bool update();
	// update function for the soldier, pure virtual in parent game object

	void show_status();
	// show status for soldier, virtual in parent game object and person
	
	void take_hit(int attack_strength, Person * attackerPtr);
	// makes the soldier take a hit and then attack the attacking soldier back

private:
	int attack_strength;
	// int value of enemy health lost per attack. default is 2

	double range;
	// radius within which the soldier can attack. default is 2.0

	Person * target;
	// pointer to the person currently being targetted for attack

};

#endif