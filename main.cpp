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
#include "Input_Handling.h"
#include <string>
#include <sstream>

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
    
    bool quit = false; // loop termination condition Variable

    std::string inputString; // stores the entire user input line until variables have been extracted from it

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
        try
        {
            inputString.clear(); // clear previous stream
            
            std::cout << "Enter command: "; // prompt user for input
            
            getInputStream(cmdCode, inputString); 
            // get input as a input string stream object and extract command code at the same time

            switch (cmdCode)
            {
                case 'q' : // QUIT: input string format: "q"
                {
                    checkBloatedInput(inputString);
                    continueLoop = quitGame(model);
                    break;
                }
                case 'm' : // MOVE: input string format: "m 1 20 17" (miner id, xcord, ycord)
                {
                    id1 = getInt(inputString);
                    x = getDouble(inputString);
                    y = getDouble(inputString);
					checkBloatedInput(inputString);
                    move(model, view, id1, x, y);
                    break;
                }
                case 'w' : // WORK: input string format "w 1 2 0" (miner id, mine id, hall id)
                {
                    id1 = getInt(inputString);
                    id2 = getInt(inputString);
                    id3 = getInt(inputString);
                    checkBloatedInput(inputString);
                    work(model, view, id1, id2, id3);
                    break;
                }
                case 'a' : // ATTACK: input string format "a 1 2" (solderi id, person id)
                {
                    id1 = getInt(inputString);
                    id2 = getInt(inputString);
                    checkBloatedInput(inputString);
                    attack(model, view, id1, id2);
                    break;
                }
                case 's' : // STOP: input string format "s 1" (person id)
                {
                    id1 = getInt(inputString);
                    checkBloatedInput(inputString);
                    stop(model, view, id1);
                    break;
                }
                case 'g' : // GO: input string format "g"
                {
                    checkBloatedInput(inputString);
                    go(model, view);
                    break;
                }
                case 'r' : // RUN: input string format "r"
                {
                    checkBloatedInput(inputString);
                    run(model, view);   
                    break;
                }
                case 'l' : // LIST: input string format "l"
                {
                    checkBloatedInput(inputString);
                    list(model);
                    break;
                }
                default :
                {
                    // if none of the codes are recognised then throw an exception
                    throw Invalid_Input("Command code not recognised.");
                }
                // keep repeating this loop until the user wants to quit
            }
        }
        catch (Invalid_Input & except)
        {
            std::cout << "Invalid Input - " << except.msg_ptr << std::endl;
        }
    }
    return 0;
}