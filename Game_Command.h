#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H

#include "Model.h"
#include "View.h"

#include <string>
#include <fstream> 

// game commands
// generic
void move(Model * model, View * view, int personID, double xcord, double ycord);
void stop(Model * model, View * view, int personID);

// Minder commands
void work(Model * model, View * view, int personID, int mineID, int hallID);

// Soldier commands
void attack(Model * model, View * view, int soldierID, int personID);

// Inspector commands
void inspect(Model * model, View * view, int personID);

// Model commands
void go(Model * model, View * view);
void run(Model * model, View * view);
void list(Model * model);
void save(Model * model, View * view, std::string fileName);
void restore(Model * model, View * view, std::string fileName);
void makeNew(Model * model, View * view, char type, char inputID, double xcord, double ycord);
bool quitGame(Model * model);

// string input and extraction functions
void getInputStream(char & cmdCode, std::string & inputString);
char getChar(std::string & inputString);
int getInt(std::string & inputString);
double getDouble(std::string & inputString);
std::string getFilename(std::string & inputString);

// input string cleanup and bloat checkers
void cleanInputString(std::string & inputString);
void checkBloatedInput(std::string & inputString);

#endif