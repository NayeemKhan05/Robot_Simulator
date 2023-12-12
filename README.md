# Robot Movement Simulator

## Overview

The Robot Movement Simulator is a program, written in C, that simulates the movement of a robot within a grid. The robot is capable of moving in four directions (up, down, left, right) and can perform actions such as picking up and dropping markers. The goal of the robot is to pick up and drop of all markers back to the starting position of the robot.

## Table of Contents

- [Requirements](#requirements)
- [Stages Completed](#stagescomplete)
- [Graphics](#usage)
- [Compiling Program](#compiling-program)
- [Input Robot](#grid-representation)


## Requirements
To run this program you will need the following...
- C compiler (gcc or clang)
- Java Drawapp version 2 or version 3

## Stages Completed

Stages 1-6 have been completed. 

The grid contains three markers and three obstacles, with one marker and one obstacle not placed against a wall. Under this current setup, the robot is able to successfully retrieve all three markers successfully when starting at most positions.

## Graphics

- The robot is represented as a green triangle, with the top vertex acting as the "head" in order to determine the direction the robot is facing.
- A marker is represented as a red square.
- An obstacle is represented as a black square.
- The home square is represented as a blue square.

## Compiling Program
To compile the program, type the following command in your terminal
```bash
gcc -o robot_simulator robot_simulator.c graphics.c
```
Or if you are using the clang compiler then type
```bash
clang -o robot_simulator robot_simulator.c graphics.c
```
To open the program (without inputting robot positon) type the following in your terminal
```bash
./robot_simulator | java -jar drawapp-2.0.jar
```
## Inputing Robot 

The program takes three command-line arguments in the following order to determine where to place the robot.

1. Row of the initial robot position.
2. Column of the initial robot position.
3. Direction the robot is facing (`up`, `down`, `left`, or `right`).

### Example
```bash
./robot_simulator 1 2 up | java -jar drawapp-2.0.jar
