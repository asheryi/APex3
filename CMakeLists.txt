cmake_minimum_required(VERSION 3.8)
project(ex3)

set(CMAKE_CXX_STANDARD 98)

add_subdirectory(gtest_src/googletest-master)
include_directories(gtest_src/googletest-master/googletest/include)
include_directories(gtest_src/googletest-master/googlemock/include)

set(SOURCE_FILES
        include/Attack.h
        src/Board.cpp
        include/Board.h
        src/Cell.cpp
        include/Cell.h
        include/Console.h
        src/ConsoleController.cpp
        include/ConsoleController.h
        src/Directions.cpp
        include/Directions.h
        include/Display.h
        src/Game.cpp
        include/Game.h
        include/GameLogic.h
        src/HumanPlayer.cpp
        include/HumanPlayer.h
        src/Path.cpp
        include/Path.h
        src/Player.cpp
        include/Player.h
        include/PlayerController.h
        src/StandardAttack.cpp
        include/StandardAttack.h
        src/StdGameLogic.cpp
        include/StdGameLogic.h
        include/TypesOf.h src/AIplayer.cpp include/AIplayer.h include/VectorExterminator.h src/Counter.cpp include/Counter.h
        include/HumanConsole.h src/AIConsole.cpp include/AIConsole.h src/Console.cpp)

set(TEST_FILES
        test/test_1.cpp test/BoardTest.cpp test/AITest.cpp)


add_executable(ex3 ${SOURCE_FILES} src/main.cpp)
add_executable(ex3_test ${SOURCE_FILES} ${TEST_FILES} test/test_main.cpp)

target_link_libraries(ex3_test gtest gmock gtest_main)
add_test(ex3_test ex3_test)