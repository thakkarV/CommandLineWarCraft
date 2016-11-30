#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H

#include "Model.h"
#include "View.h"
#include "Person.h"
#include "Miner.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include <iostream>

void move(Model * model, View * view, int personID, double xcord, double ycord);
void work(Model * model, View * view, int personID, int mineID, int hallID);
void attack(Model * model, View * view, int soldierID, int personID);
void stop(Model * model, View * view, int id);
void go(Model * model, View * view);
void run(Model * model, View * view);
void list(Model * model);
bool quitGame(Model * model);

#endif