# Flappy Bird Clone in SFML!
This is a C++ project that implements a clone of the popular game Flappy Bird using the Simple and Fast Multimedia Library (SFML).

## Features
-   Classic Flappy Bird gameplay with SFML's collision detection.
-   Simple and intuitive controls using the spacebar to make the bird jump.
-   Randomly generated pipes for endless gameplay.
-   Score tracking and display of the current score.
-   Game over detection with the option to restart the game.

## Prerequisites
Before running the Flappy Bird clone, make sure you have the following installed on your system:
-   SFML library: You can download SFML from the official website ([https://www.sfml-dev.org/](https://www.sfml-dev.org/)) and follow the installation instructions for your operating system, for example on Debian:
```
$ sudo apt-get install libsfml-dev
```
- A C++ compiler, such as GCC or Clang
 
## Installation
1. Clone the repository to your local machine:
```
$ git clone https://github.com/BlackyDrum/flappy-bird.git
```
2. Change to the src directory:
```
$ cd flappy-bird/src
```
3. Build the project using a C++ compiler:
```
$ g++ main.cpp -o flappy-bird -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```
4. Run the binary file:
```
$ ./flappy-bird
```
## Build using Makefile
If you have GNU Make installed on your system, you can use the included Makefile to build the project.

1. Clone the repository to your local machine:
```
$ git clone https://github.com/BlackyDrum/flappy-bird.git
```
2. Change to the cloned directory:
```
$ cd flappy-bird
```
3. Use make to build the project. The executable ``flappy-bird`` will be generated in the same directory.
```
$ make
```
4. Run the binary file:
```
$ ./flappy-bird
```

## Acknowledgements

-   SFML: Simple and Fast Multimedia Library ([https://www.sfml-dev.org/](https://www.sfml-dev.org/))
-   Flappy Bird: Original game developed by Dong Nguyen ([https://en.wikipedia.org/wiki/Flappy_Bird](https://en.wikipedia.org/wiki/Flappy_Bird))
-   Assets: Sounds and textures ([https://github.com/samuelcust/flappy-bird-assets](https://github.com/samuelcust/flappy-bird-assets))
