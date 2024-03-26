# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* install SDL2 Image 
  * Installation instructions can be found [here](https://www.libsdl.org/projects/SDL_image/)
  > Note that for Ubuntu (Linix), run command : sudo apt-get install libsdl2-image-dev'
  > Note that for Windows 11 (windows), Go to the SDL2 download page: https://www.libsdl.org/download-2.0.php

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

** In order to change Backgroup imgae : before step3 make sure you have the SDL2_image development files installed on your system. 
If you're using Ubuntu or a similar system, you can install the necessary packages using: sudo apt-get install libsdl2-image-dev

## New features
1. Backgroup change : change background of the game with images in the foder "/image".You can upload your own. Default is "number0.jpeg"
2. Special Food Item : Special food appears every 5 regular foods. If snake consume the special food, it double the score, snake don't grow in size and the speed is decrease.
3. A new thread is created to count how many specials the snake has consumed.
4. Game now can be paused : press "P" to pause the game, press again to back to play

## Rubric Point:
1. Readme
  > A README with instructions is included with the project
  > The README indicates the new features added to the game.
  > The README includes information about each rubric point addressed.
2. Compiling and testing
  > The submission compile and run without errors on the Udacity project workspace.
3. Loops, Functions, I/O
  > The project demonstrates an understanding of C++ functions and control structures. Functions are organized, and there's a variety of control structures in the project.
  > The project reads data from a file and process the data, or the program writes data to a file.
  > The project accepts user input and processes it
4. Object Oriented Programming
  > One or more classes are added with appropriate access specifiers. Class members are organized with attributes and methods, and data members are specified as public, protected, or private    
  > Class constructors use member nitialization lists where appropria      
  > Classes abstract implementation details from their interfaces. Member functions document their effects, and they don't change the program state in undocumented   .
5. Memory Management
  > The project makes use of references in function declarations.
  > The project uses destructors appropriately.
     > in class Renderer : with destructor  ~Renderer()
  > The project uses smart pointers.
     > in class Renderer : using std::unique_ptr name sdl_window to manage the SDL_Window object
6. Concurrency
  > The project uses multithreading.
  > A mutex or lock is used in the project to protect shared data across multiple threads.
## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
