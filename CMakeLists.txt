cmake_minimum_required(VERSION 3.6)
project(saper)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c userCommunication.c userCommunication.h model.h gameLogic.c gameLogic.h selectionModelStack.c selectionModelStack.h)
add_executable(saper ${SOURCE_FILES})