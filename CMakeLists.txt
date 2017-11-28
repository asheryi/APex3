cmake_minimum_required(VERSION 3.8)
project(ex3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Attack.h
        Board.cpp
        Board.h
        Cell.cpp
        Cell.h
        Console.cpp
        Console.h
        ConsoleController.cpp
        ConsoleController.h
        Directions.cpp
        Directions.h
        Display.h
        Game.cpp
        Game.h
        GameLogic.h
        HumanPlayer.cpp
        HumanPlayer.h
        main.cpp
        Path.cpp
        Path.h
        Player.cpp
        Player.h
        PlayerController.h
        StandardAttack.cpp
        StandardAttack.h
        StdGameLogic.cpp
        StdGameLogic.h
        TypesOf.h AIplayer.cpp AIplayer.h VectorExterminator.h Counter.cpp Counter.h Tests/testClass.h Tests/test.cpp)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
add_executable(ex3 ${SOURCE_FILES} Tests/testClass.h Tests/test.cpp)
target_link_libraries(ex3 gtest main)
