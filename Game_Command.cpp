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
	bool throwaway = model-> update();
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

void getInputStream(char & cmdCode, std::string & inputString)
{
	std::getline(std::cin, inputString); // get input using getline

	if (inputString.size() == 0)
	{
		throw Invalid_Input("Please enter a command.");
	}
	else
	{
		// if the size was not zero, extract the commnad code and sput out the stream and the command
		std::istringstream inputStream(inputString);

		if (! (inputStream >> cmdCode) )
		{
			throw Invalid_Input("Expected a charecter for command code.");
		}
		else
		{
			cleanInputString(inputString); // then clean the input string
		}
	}
}

char getChar(std::string & inputString)
{
// first convert the string to an input stream
	std::istringstream inputStream(inputString);

	char charInput;
	if (! (inputStream >> charInput) )
	{
		throw Invalid_Input("Expected a charecter.");
	}
	else
	{
		cleanInputString(inputString);
		return charInput;
	}
}

int getInt(std::string & inputString)
{
	// first convert the string to an input stream
	std::istringstream inputStream(inputString);

	int intInput;
	if (! (inputStream >> intInput) )
	{
		throw Invalid_Input("Expected an integer.");
	}
	else
	{
		cleanInputString(inputString);
		return intInput;
	}
}

double getDouble(std::string & inputString)
{
	// first convert the string to an input stream
	std::istringstream inputStream(inputString);

	double doubleInput;
	if (! (inputStream >> doubleInput) )
	{
		throw Invalid_Input("Expected a real number.");
	}
	else
	{
		cleanInputString(inputString);
		return doubleInput;
	}
}

void cleanInputString(std::string & inputString)
{
	// to change the inputString appropriately to drop the first parameter, 
	// we first check if the first cahrecter is a space or not
	if (inputString.at(0) == ' ')
	{
		// if it is then find location fo the first non-space char
		std::size_t firstCharLocation = inputString.find_first_not_of(" ");

		// and location of the first space after that
		std::size_t secondSpaceLocation = inputString.find_first_of(" ", firstCharLocation);
		
		// if the secondSpaceLocation does not exist then we erase the whole string
		if (secondSpaceLocation == std::string::npos)
		{
			// erase the whole string
			inputString.clear();
		}
		else
		{
			// otherwise just erase from the begin of the string till the first space
			inputString.erase(0, secondSpaceLocation);
		}
	}
	else // otherwise if the first element is not a 
	{
		std::size_t firstSpaceLocation = inputString.find_first_of(" ");

		inputString.erase(0, firstSpaceLocation);
	}
}

void checkBloatedInput(std::string & inputString)
{
	// this function serves the sole purpose of throwing an exception
	// if the input had more number of parameters than the command allows
	// even if the leading parameter were of the appropriate foramt

	if (inputString.find_first_not_of(" ") != std::string::npos)
	{
		throw Invalid_Input("More input parameters than expected.");
	}
}