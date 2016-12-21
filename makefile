# compiler
CC = g++

# define objects to be compiled
OBJS = main.o Cart_Point.o Cart_Vector.o Inspector.o Game_Object.o Game_Command.o Gold_Mine.o Person.o Miner.o Soldier.o Model.o Town_Hall.o View.o

# Compiler flags for final compile
CPPFLAGSFCP = -c
# Compiler flags for debug compile
CPPFLAGSDBG = -c -ggdb

# linker flags
CXXFLAGS = -o

# DEFUALT COMPILE PROTOCOL
default: PA4

PA4: $(OBJS)
	$(CC) $(CXXFLAGS) PA4 $(OBJS) 

Cart_Vector.o: Cart_Vector.cpp Cart_Vector.h
	$(CC) $(CPPFLAGSFCP) Cart_Vector.cpp $(CXXFLAGS) Cart_Vector.o 
	
Cart_Point.o: Cart_Point.cpp Cart_Point.h Cart_Vector.h
	$(CC) $(CPPFLAGSFCP) Cart_Point.cpp $(CXXFLAGS) Cart_Point.o 

Game_Object.o: Game_Object.cpp Game_Object.h Cart_Point.h
	$(CC) $(CPPFLAGSFCP) Game_Object.cpp $(CXXFLAGS) Game_Object.o 

Gold_Mine.o: Gold_Mine.cpp Gold_Mine.h Game_Object.h Cart_Point.h
	$(CC) $(CPPFLAGSFCP) Gold_Mine.cpp $(CXXFLAGS) Gold_Mine.o

Model.o: Model.cpp Model.h Inspector.h Input_Handling.h Game_Object.h Person.h Town_Hall.h Gold_Mine.h Miner.h View.h Soldier.h
	$(CC) $(CPPFLAGSFCP) Model.cpp $(CXXFLAGS) Model.o 

Person.o: Person.cpp Person.h View.h Game_Object.h Cart_Point.h Cart_Vector.h Town_Hall.h Gold_Mine.h Model.h
	$(CC) $(CPPFLAGSFCP) Person.cpp $(CXXFLAGS) Person.o

Miner.o: Miner.cpp Miner.h Person.h Game_Object.h Gold_Mine.h Town_Hall.h Cart_Point.h Cart_Vector.h
	$(CC) $(CPPFLAGSFCP) Miner.cpp $(CXXFLAGS) Miner.o 

Soldier.o: Soldier.cpp Soldier.h Person.h Model.h
	$(CC) $(CPPFLAGSFCP) Soldier.cpp $(CXXFLAGS) Soldier.o

Inspector.o: Inspector.cpp Inspector.h Person.h Gold_Mine.h Model.h Input_Handling.h Cart_Point.h Model.h
	$(CC) $(CPPFLAGSFCP) Inspector.cpp $(CXXFLAGS) Inspector.o

Town_Hall.o: Town_Hall.cpp Town_Hall.h Game_Object.h Cart_Point.h Model.h
	$(CC) $(CPPFLAGSFCP) Town_Hall.cpp $(CXXFLAGS) Town_Hall.o 

View.o: View.cpp View.h Game_Object.h Cart_Point.h
	$(CC) $(CPPFLAGSFCP) View.cpp $(CXXFLAGS) View.o 

Game_Command.o: Game_Command.cpp Input_Handling.h Game_Command.h Model.h Game_Object.h Person.h Town_Hall.h Gold_Mine.h Miner.h View.h
	$(CC) $(CPPFLAGSFCP) Game_Command.cpp $(CXXFLAGS) Game_Command.o

main.o: main.cpp Cart_Point.h Cart_Vector.h Game_Command.h Gold_Mine.h Miner.h Model.h Person.h Town_Hall.h Game_Object.h View.h
	$(CC) $(CPPFLAGSFCP) main.cpp


# CLEANUP PROTOCOL
clean:
	rm $(OBJS) PA4