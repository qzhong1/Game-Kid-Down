# CPPND: Capstone Hello World Repo

This is the repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

In this project, a 2D game of a kid (more like a stickman figure) going downstairs are created. The player needs to control the motion of the kid using left and right key on the keyboard. Press down key to start the game. The goal is to keep the kid on the raising bars without touching the ceiling or falling to the bottom. If the kid stands on the spiky bar, the blood bar will decrease. The kid dies when blood bar goes to zero.



## Code Overview
* SDL2 library is used to render the game window and gain control of the game figure. Class Renderer and class controller is created for those purposes.
* There are three types of bar, which are normal, moving and damaging bars. They are inherited from based class Bar. If the kid stands on moving bar, it will constantly transfer the kid to the left, while damaging bars constantly damaging kid's blood bar.
* Game class is created to control the game flow, including keep rendering the images, updating kid and bar positions, checking kid status, restarting game after game over and etc. 
* All images used is stored in the img folder. Font used are stored in ttf folder.
![Main Code Structure](img/Code&#32;Structure.PNG)

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* libsdl2
  * sudo apt-get install libsdl2-dev
  * sudo apt-get install libsdl2-image-dev
  * sudo apt-get install libsdl2-ttf-dev

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./KidDown`.

## Rubric Points
* The project demonstrates an understanding of C++ functions and control structures.
  * controller.cpp (Controller::HandleInput, switch)
  * game.cpp (Game::Run, while loop)
  * kid.cpp (Kid::FallOnBar)
* The project accepts user input and processes the input.
  * controller.cpp (Accept left, right and down key, and mouse click event)
* The project uses Object Oriented Programming techniques.
  * Classes are divided into different files
* The project uses Object Oriented Programming techniques.
  * bar.h (base class variables are protected)
  * renderer.h (most image containers are private)
* Class constructors utilize member initialization lists.
  * game.cpp (In initialisation list, initialised kid object)
* Classes abstract implementation details from their interfaces.
* Classes encapsulate behavior.
* Classes follow an appropriate inheritance hierarchy.
  * bar.h (NormalBar, MovingBar, DamageBar inherited from base class Bar)
