# CMakeList.txt : CMake project for DSProject, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.8)

project(DSProject)

enable_language("C")
# Add source to this project's executable.
add_executable (DSProject "Main.c" "Login.h" "Constants.h" "BookList.h" "FileIO.h" "Menu.h" "UserList.h")

# TODO: Add tests and install targets if needed.
