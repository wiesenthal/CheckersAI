cmake_minimum_required(VERSION 3.14)
project(Checker_Teacher C CXX)

set(CMAKE_CXX_STANDARD 11)
#set(SOURCE_FILES main.cpp GameLogic.cpp Move.cpp ManualAI.cpp StudentAI.cpp Move.cpp Move.h AI.h Board.cpp)
set(SOURCE_FILES main.cpp Move.cpp Move.h Board.cpp Board.h Checker.cpp Checker.h Utils.cpp Utils.h StudentAI.cpp StudentAI.h GameLogic.cpp GameLogic.h ManualAI.cpp ManualAI.h)

add_executable(Checker_Teacher ${SOURCE_FILES})
