a.out: Board.o Cell.o Console.o ConsoleController.o Directions.o Game.o HumanPlayer.o main.o Path.o Player.o PlayerController.o StandardAttack.o StdGameLogic.o
	g++  Board.o Cell.o Console.o ConsoleController.o Directions.o Game.o HumanPlayer.o main.o Path.o Player.o PlayerController.o StandardAttack.o StdGameLogic.o

Board.o: Board.h Board.cpp Cell.h TypesOf.h
	g++ -c Board.cpp

Cell.o: Cell.h Cell.cpp
	g++ -c Cell.cpp

Console.o: Console.h Console.cpp Display.h Board.h Cell.h
	g++ -c Console.cpp

ConsoleController.o: ConsoleController.h ConsoleController.cpp PlayerController.h
	g++ -c ConsoleController.cpp

Directions.o: Directions.h Directions.cpp Cell.h
	g++ -c Directions.cpp

Game.o: Game.h Game.cpp GameLogic.h Player.h Display.h Board.h Path.h
	g++ -c Game.cpp

HumanPlayer.o: HumanPlayer.h HumanPlayer.cpp Player.h PlayerController.h Cell.h
	g++ -c HumanPlayer.cpp

main.o: main.cpp Game.h
	g++ -c main.cpp

Path.o: Path.h Path.cpp Cell.h
	g++ -c Path.cpp

Player.o: Player.h Player.cpp PlayerController.h TypesOf.h
	g++ -c Player.cpp

PlayerController.o: PlayerController.h PlayerController.cpp Cell.h
	g++ -c PlayerController.cpp

StandardAttack.o: StandardAttack.h StandardAttack.cpp Attack.h Path.h
	g++ -c StandardAttack.cpp

StdGameLogic.o: StdGameLogic.h StdGameLogic.cpp GameLogic.h Board.h Player.h Directions.h
	g++ -c StdGameLogic.cpp
