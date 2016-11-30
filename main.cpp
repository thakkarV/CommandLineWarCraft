#include <iostream>

#include "Cart_Vector.h"
#include "Cart_Point.h"
#include "Game_Object.h"
#include "Town_Hall.h"
#include "Gold_Mine.h"
#include "Miner.h"
#include "Person.h"
#include "Game_Command.h"
#include "Model.h"
#include "View.h"

//Students need to build on this
int main()
{
// Variable Declarations
    char cmdCode; // input command of type char that gets switched within the main loop
    
    int id1; // id_num of game obj 1
    int id2; // id_num of game obj 2
    int id3; // id_num of game obj 3
    
    double x; // co-ordinates of destination
    double y; // co-ordinates of destination
    
    bool quit = false; // loop termination condition variable

// initlal greet messages
    std::cout << "EC327: Introduction to Software Engineering" << std::endl;
    std::cout << "Fall 2016" << std::endl;
    std::cout << "Programming Assignment 3" << std::endl;

// instatiate all initial game objects and the MVC objects
    Model * model = new Model();
    View * view = new View();
    model-> show_status();
    model-> display(view);

// start of the main loop now
    bool continueLoop = true;
    while (continueLoop)
    {
        std::cout << "Enter command: ";
        std::cin >> cmdCode;
        switch (cmdCode)
        {
            case 'q' : // QUIT: input string format: "q"
            {
                continueLoop = quitGame(model);
                break;
            }
            case 'm' : // MOVE: input string format: "m 1 20 17" (miner id, xcord, ycord)
            {
                std::cin >> id1 >> x >> y;
                move(model, view, id1, x, y);
                break;
            }
            case 'w' : // WORK: input string format "w 1 2 0" (miner id, mine id, hall id)
            {
                std::cin >> id1 >> id2 >> id3;
                work(model, view, id1, id2, id3);
                break;
            }
            case 'a' : // ATTACK: input string format "a 1 2" (solderi id, person id)
            {
                std::cin >> id1 >> id2;
                attack(model, view, id1, id2);
                break;
            }
            case 's' : // STOP: input string format "s 1" (person id)
            {
                std::cin >> id1;
                stop(model, view, id1);
                break;
            }
            case 'g' : // GO: input string format "g"
            {
                go(model, view);
                break;
            }
            case 'r' : // RUN: input string format "r"
            {
                run(model, view);   
                break;
            }
            case 'l' : // LIST: input string format "l"
            {
                list(model);
                break;
            }
            // keep repeating this loop until the user wants to quit
        }
        std::cin.ignore(1000, '\n');
    }
    return 0;
}