cmake_minimum_required(VERSION 4.3)
project(WinLocker)

set(CMAKE_CXX_STANDARD 20)

add_executable(WinLocker WIN32
        src/main.cpp
        src/KeyValidator.cpp
        src/KeyValidator.h
        src/WindowsCoordinates.h
        src/WindowData.h
)
