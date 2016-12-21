#ifndef SOLDIER_H
#define SOLDIER_H


#include "Cart_Point.h"
#include "Person.h"
#include "Input_Handling.h"

#include <fstream>

class Soldier : public Person
{
public:
	Soldier();

	Soldier(const int inId, const Cart_Point inLoc);

	Soldier(const char inputcode, const int inId, const Cart_Point inLoc);

	~Soldier();

	void start_attack(Person * targetPtr);
	// sets up the soldier to attack the person pointer to by the input pointer, virtual in parent person

	bool update();
	// update function for the soldier, pure virtual in parent game object

	void show_status();
	// show status for soldier, virtual in parent game object and person
	
	void take_hit(int attack_strength, Person * attackerPtr);
	// makes the soldier take a hit and then attack the attacking soldier back

	void save(std::ofstream & file);
	// save state to file

	void restore(std::ifstream & file, Model * model);
	// load state from file

private:
	int attack_strength;
	// int value of enemy health lost per attack. default is 2

	double range;
	// radius within which the soldier can attack. default is 2.0

	Person * target;
	// pointer to the person currently being targetted for attack

};

#endif