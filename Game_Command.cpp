#include "Game_Command.h"
#include "Model.h"
#include "View.h"
#include "Cart_Point.h"
#include "Person.h"
#include "Miner.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "Input_Handling.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// makes a new game object on the fly
void makeNew(Model * model, View * view, char type, char inputID, double xcord, double ycord)
{
	model-> handleNew(type, inputID, xcord, ycord);
	model-> display(view);
}

// tells a person to move to input coordinates
void move(Model * model, View * view, int personID, double xcord, double ycord)
{
	// first try to get the pointer to the person we are trying to move
	Person * personPtr = model-> get_Person_ptr(personID);
	
	// if it does not  exist, throw an exception
	if (personPtr != 0)
	{
		// if the minser exists then set it moving towards that location
		personPtr-> start_moving(Cart_Point(xcord, ycord));
		// moving message will be displayed by start_moving function from person.cpp
	}
	else
	{
		throw Invalid_Input("Person with entered ID number does not exist.");
	}

	model-> display(view);
}

// tells a miner to start mining form input mine and submitting at input hall
void work(Model * model, View * view, int personID, int mineID, int hallID)
{
	// first get all the three pointers from the model
	Person * personPtr = model-> get_Person_ptr(personID);
	Miner * minerPtr = dynamic_cast < Miner * > (personPtr);
	Gold_Mine * minePtr = model-> get_Gold_Mine_ptr(mineID);
	Town_Hall * hallPtr = model-> get_Town_Hall_ptr(hallID);

	if (minerPtr && minePtr && hallPtr)
	{
		minerPtr-> start_mining(minePtr, hallPtr);
		// mining message will be displayed by the start_minig function in miner.cpp
	}
	else if (!minerPtr)
	{
		throw Invalid_Input("Miner with entered ID does not exist.");
	}
	else if (!minePtr)
	{
		throw Invalid_Input("Gold mine with entered ID does not exist.");
	}
	else // if hall pointer is null
	{
		throw Invalid_Input("Town hall with entered ID does not exist.");
	}

    model-> display(view);
}

// tells a soldier to attack the input person
void attack(Model * model, View * view, int soldierID, int personID)
{
	Person * soldierPtr = model-> get_Person_ptr(soldierID);
	Person * personPtr = model-> get_Person_ptr(personID);

	if (soldierPtr && personPtr)
	{
		// if both ID numbers were valid then start attacking	
		soldierPtr-> start_attack(personPtr);
	}
	else if (soldierPtr)
	{
		throw Invalid_Input("Solider with entered ID does not exist.");
	}
	else
	{
		throw Invalid_Input("Target with entered ID does not exist.");
	}

	model-> display(view);
}

// tells a person to stop whatever its doing
void stop(Model * model, View * view, int personID)
{
	// get pointer first
	Person * personPtr = model-> get_Person_ptr(personID);

	if (personPtr)
	{
		personPtr-> stop();
		// stopping message will by ouput by the stop function in person.cpp
	}
	else
	{
		throw Invalid_Input("Person with entered ID number does not exist.");
	}

	model-> display(view);
}

// tells an inspector to start inspecting mines
void inspect(Model * model, View * view, int inspectorID)
{
	Person * inspectorPtr = model-> get_Person_ptr(inspectorID);

	if (inspectorPtr)
	{
		inspectorPtr-> start_inspecting(model);
	}
	else
	{
		throw Invalid_Input("Person with entered ID number does not exist.");
	}

	model-> display(view);
}

// model advance one time tick
void go(Model * model, View * view)
{
	std::cout << "Advancing one tick." << std::endl;
	bool event = model-> update();
	model-> show_status();
	model-> display(view);
}

// modle advance either 5 time ticks or until a significant event, whichever is earlier
void run(Model * model, View * view)
{
	std::cout << "Advancing to next event." << std::endl;
	bool event = false;
	int counter = 0;

	while (!event && counter < 5)
	{
		event = model-> update();
		counter++;
	}

	model-> show_status();
	model-> display(view);
}

// list the status of all game objects
void list(Model * model)
{
	model-> show_status();
}

// terminate main and delete all objects from memory
bool quitGame(Model * model)
{
	std::cout << "Terminating program." << std::endl;
	delete model;
	return false;
}

// get the entire command input from the user as a string and extract command code
void getInputStream(char & cmdCode, std::string & inputString)
{
	// this funciton is the first one called by the  main to get the entire user input command as a string
	// once this string is input this function checkts for size, extracts command code, chomps it off
	// and then writes the cmdCode and original input string back as a return since they are PBR

	std::getline(std::cin, inputString); // get input using getline

	// check for empty command
	if (inputString.size() == 0)
	{
		throw Invalid_Input("Please enter a command.");
	}
	else
	{
		cmdCode = getChar(inputString);
	}
}

// extract next char from input command string
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
		// chomp of the extracted char and return it
		cleanInputString(inputString);
		return charInput;
	}
}

// extract next int form the inpt command string
int getInt(std::string & inputString)
{
	// first convert the string to an input stream
	std::istringstream inputStream(inputString);

	int intInput;
	if (! (inputStream >> intInput) )
	{
		throw Invalid_Input("Expected an integer.");
	}
	else if (intInput > 9)
	{
		throw Invalid_Input("ID number cannot exceed a value of 9.");
	}
	else
	{
		// chomp off the extracted int and return it
		cleanInputString(inputString);
		return intInput;
	}
}

// extract next duoble from input command string
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
		// chomp off the extracted double and return it
		cleanInputString(inputString);
		return doubleInput;
	}
}

// extract file name for save or load form command string
std::string getFilename(std::string & inputString)
{
	char expectedSpace = inputString.at(0);

	if (expectedSpace != ' ')
	{
		throw Invalid_Input("Invalid input format for command. Must have a space after ");
	}

	int firstChar = inputString.find_first_not_of(" ");
	std::string fileName = inputString.substr(firstChar, std::string::npos);
	inputString.clear();

	// there could be more spaces in the file name as well and no file extension
	if (fileName.find(" ") != std::string::npos) 
	{
		throw Invalid_Input("Filename must not contain any spaces.");
	}

	if (fileName.find(".") == std::string::npos)
	{
		throw Invalid_Input("Filename must have an extension.");
	}

	return fileName;
}

// delete the last extraction from the command string
void cleanInputString(std::string & inputString)
{
	// to change the inputString appropriately to drop the first parameter, 
	// we first check if the first charecter is a space or not
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

// check for redundant input parameters after extracting all required inputs from command string
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

// save game state to a file of user input name
void save(Model * model, View * view, std::string fileName)
{
	std::ofstream saveStream;
	saveStream.open(fileName.c_str());

	if (saveStream.is_open())
	{
		model-> save(saveStream);

		saveStream.close();

		std::cout << "Epic Game Saved!" << std::endl;

		model->display(view);
	}
	else
	{
		throw Invalid_Input("Could not open file to save to.");
	}
 }

// load game state from a fiel of user input name
void restore(Model * model, View * view, std::string fileName)
{
	std::ifstream loadStream;
	loadStream.open(fileName.c_str());

	if (loadStream.is_open())
	{
		std::cout << "All objects are destroyed on DOOMS DAY!!" << std::endl;

		model-> restore(loadStream);

		loadStream.close();

		model->display(view);
	}	
	else
	{
		throw Invalid_Input("No file of input name exists to load from.");
	}
}