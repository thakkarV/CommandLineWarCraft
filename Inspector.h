#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "Cart_Point.h"
#include "Person.h"
#include "Gold_Mine.h"
#include "Model.h"
#include "Input_Handling.h"

#include <stack>
#include <list>
#include <deque>
#include <iostream>
#include <math.h> // abs

class Inspector : public Person
{
public:
	Inspector();

	Inspector(const int inId, const Cart_Point inLoc);

	~Inspector();

	bool update();
	// update like any other person

	void show_status();
	// show status like any other person
	
	void start_inspecting(Model * model);
	// copies over the model's mine_ptrs into this inspector's inspectionQueue list

private:

	Gold_Mine * destMinePtr;
	// stores the pointer to the mine being currently headed towards or inspected

	std::deque < Gold_Mine * > inspectionQueue;
	std::deque< Gold_Mine * >::iterator inspectionQueueItr;
	// this deque of gold mine pointers stores the pointers to all the mines inspector is supposed to inspect
	// this deque is not the same as the mine_ptr list of model
	// this is because new mines can be added after starting an inspection, but once an spection is started
	// new added mines are not inspected as this list is copied over from model at the begging of the inspection
	// queue is also cleared if a new inspection command interrupts an ongoing one
	// rational for queue instead of copying over the entire list as a list is that the access is random
	// list does not allow at function  random access, which is what we need here


	std::stack < Gold_Mine * > inspectionOrder;
	// this stack stores the pointers of the already inspected mines in the corrrect inspection order
	// the mines need to be traced back in the order that is reverse of the inspection order


	std::deque < double > forwardPassGold;
	std::deque< double >::iterator forwardPassGoldItr;
	// this list stores the amount of gold in the mines when inspected for the first time
	// the index of the amount corresponds to the mine index in the inspectionMine list

	Gold_Mine * findClosestMine(std::deque< Gold_Mine * > inspectionQueue);
	// used for setting up destination for the next mine

};

#endif