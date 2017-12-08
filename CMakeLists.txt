cmake_minimum_required(VERSION 3.8)
project(ex3)

set(CMAKE_CXX_STANDARD 98)

add_subdirectory(gtest_src/googletest-master)
include_directories(gtest_src/googletest-master/googletest/include)
include_directories(gtest_src/googletest-master/googlemock/include)

set(CLIENT_FILES
        client/include/Attack.h
        client/src/Board.cpp
        client/include/Board.h
        client/src/Cell.cpp
        client/include/Cell.h
        client/include/Console.h
        client/src/ConsoleController.cpp
        client/include/ConsoleController.h
        client/src/Directions.cpp
        client/include/Directions.h
        client/include/Display.h
        client/src/Game.cpp
        client/include/Game.h
        client/include/GameLogic.h
        client/src/HumanPlayer.cpp
        client/include/HumanPlayer.h
        client/src/Path.cpp
        client/include/Path.h
        client/src/Player.cpp
        client/include/Player.h
        client/include/PlayerController.h
        client/src/StandardAttack.cpp
        client/include/StandardAttack.h
        client/src/StdGameLogic.cpp
        client/include/StdGameLogic.h
        client/include/TypesOf.h client/src/AIplayer.cpp client/include/AIplayer.h client/include/VectorExterminator.h client/src/Counter.cpp client/include/Counter.h
        client/include/HumanConsole.h client/src/AIConsole.cpp client/include/AIConsole.h client/src/Console.cpp client/src/HumanConsole.cpp client/src/RemoteInputController.cpp client/src/RemoteOutputController.cpp
        client/include/RemoteInputController.h client/include/RemoteOutputController.h
        client/include/RemoteConsole.h client/src/RemoteConsole.cpp)

set(TEST_FILES
        client/test/BoardTest.cpp client/test/AITest.cpp client/test/StdGameLogicTest.cpp)

set(SERVER_FILES
        server/src/Server.cpp server/include/Server.h server/include/Cell.h server/src/Cell.cpp)

add_executable(client ${CLIENT_FILES} client/src/main.cpp)
add_executable(server ${SERVER_FILES} server/src/main.cpp)
add_executable(ex3_test ${SOURCE_FILES} ${TEST_FILES} client/test/test_main.cpp)

target_link_libraries(ex3_test gtest gmock gtest_main)
add_test(ex3_test ex3_test)