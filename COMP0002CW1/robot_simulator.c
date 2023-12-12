#include "graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int BackgroundWidth = 800;
const int BackgroundHeight = 800;
const int SquareLength = 60;
const int WaitTime = 200;
const int TopLeftOfBorder_X = 100; 
const int TopLeftOfBorder_Y = 100;

int moves[1000];  
int counter = 0;  
int markers = 3;
int reversing_movements = 0;   // Used as a variable to track whether the moves are being reversed or not
int initialRobotDirection;
int inputRow;
int inputColumn;
int carrying_marker;

// These integer constants are used in the grid_status array to represent the status of each square in the grid.
const int Empty = 0;    
const int Marker = 1;
const int Block = 2;
const int HomeSquare = 3;
const int OutOfGrid = 9;

int row;
int column;
int grid_status[12][12] = {
    {9,9,9,9,9,9,9,9,9,9,9,9},
    {9,0,0,0,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,0,0,0,9},
    {9,2,0,0,0,0,0,0,0,0,1,9},
    {9,0,0,0,0,0,0,0,0,0,0,9},
    {9,0,0,0,1,0,0,2,0,0,0,9},
    {9,0,0,0,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,0,0,1,9},
    {9,0,0,2,0,0,0,0,0,0,0,9},
    {9,9,9,9,9,9,9,9,9,9,9,9}
};

struct Robot
{
    int x_coordinates[3];
    int y_coordinates[3];
};

struct Robot robot = // Initialises robot position at bottom left of grid facing right, if no arguments were passed by the user
{
    .x_coordinates = {100, 100, 160},
    .y_coordinates = {640, 700, 670},
};

void drawMarker(int x, int y)
{
    background();
    setColour(red);
    drawRect(x, y, SquareLength, SquareLength);
    fillRect(x, y, SquareLength, SquareLength);
}

void drawBlock(int x, int y)
{
    background();
    setColour(black);
    drawRect(x, y, SquareLength, SquareLength);
    fillRect(x, y, SquareLength, SquareLength);
}

int drawInputtedHomeSquare()
{
    int x = TopLeftOfBorder_X + ((inputColumn - 1) * SquareLength);
    int y = TopLeftOfBorder_Y + ((inputRow - 1) * SquareLength);

    background();
    setColour(blue);
    drawRect(x, y, SquareLength, SquareLength);
    fillRect(x, y, SquareLength, SquareLength);
}

void drawBackground()
{
    background();
    setColour(black);

    drawRect(100, 100, 600, 600);
    for(int i = 100; i <= 700; i += SquareLength)
    {
        for (int j = 100; j <= 700; j += SquareLength)
        {
            drawLine (i, 100, i, 700);
            drawLine (100, j, 700, j);
        }
    }

    drawBlock(100,280);
    drawBlock(460,400);
    drawBlock(220,640);
    drawInputtedHomeSquare(&robot);
}

void drawRobot(struct Robot *robot)
{
    foreground();
    setColour(green);

    drawPolygon(3, robot->x_coordinates, robot->y_coordinates);
    fillPolygon(3, robot->x_coordinates, robot->y_coordinates);
}

int robotDirection()
{
    if(robot.y_coordinates[2] < robot.y_coordinates[1] && robot.y_coordinates[2] < robot.y_coordinates[0])  
    {
        return 1;
        // returns 1 if robot is facing up
    }
    else if (robot.y_coordinates[2] > robot.y_coordinates[1] && robot.y_coordinates[2] > robot.y_coordinates[0]) 
    {
        return 2;
        // returns 2 if robot is facing down
    }
    else if  (robot.x_coordinates[2] < robot.x_coordinates[1] && robot.x_coordinates[2] < robot.x_coordinates[0])
    {
        return 3;
        // returns 3 if robot is facing left
    }
    else
    {
        return 4;
        // returns 4 if robot is facing right
    }
}


void dropMarker(struct Robot *robot)
{
    int direction = robotDirection();
    int x, y;
    if (direction == 1)
    {
        x = robot->x_coordinates[0];
        y = robot->y_coordinates[2];
    }
    else if (direction == 2)
    {
        x = robot->x_coordinates[1];
        y = robot->y_coordinates[1];
    }
    else if (direction == 3)
    {
        x = robot->x_coordinates[2];
        y = robot->y_coordinates[1];
    }
    else
    {
        x = robot->x_coordinates[0];
        y = robot->y_coordinates[0];
    }
    background();
    setColour(red);
    drawRect (x, y, SquareLength, SquareLength);
    fillRect (x, y, SquareLength, SquareLength);
    carrying_marker -= 1;
}

int atMarker() 
{
    int status = grid_status[row][column];
    if (status == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void pickUpMarker(struct Robot *robot)
{
    int direction = robotDirection();
    int x, y;
    if (direction == 1)
    {
        x = robot->x_coordinates[0];
        y = robot->y_coordinates[2];
    }
    else if (direction == 2)
    {
        x = robot->x_coordinates[1];
        y = robot->y_coordinates[1];
    }
    else if (direction == 3)
    {
        x = robot->x_coordinates[2];
        y = robot->y_coordinates[1];
    }
    else
    {
        x = robot->x_coordinates[0];
        y = robot->y_coordinates[0];
    }

    int status = grid_status[row][column];
    if (status == 1 && carrying_marker <= 1)
    {
        grid_status[row][column] = 0;
        background();
        setColour(white);
        sleep(WaitTime);
        drawRect (x, y, SquareLength, SquareLength);
        fillRect (x, y, SquareLength, SquareLength);
        drawBackground();
        carrying_marker += 1;
    }
}

int isCarryingAMarker()
{
    if(carrying_marker = 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int nearObstacle() 
{
    int direction = robotDirection();
    int temp_row, temp_column, status;
    if (direction == 1)
    {
        temp_row = row - 1; 
        status = grid_status[temp_row][column];
    }
    else if (direction == 2)
    {
        temp_row = row + 1;
        status = grid_status[temp_row][column];
    }
    else if (direction == 3)
    {
        temp_column = column - 1;
        status = grid_status[row][temp_column];
    }
    else
    {
        temp_column = column + 1;
        status = grid_status[row][temp_column];
    }
    if (status == 2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int atHome()
{
    int status = grid_status[row][column];
    if (status == 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int nearWall() 
{
    int direction = robotDirection();
    int temp_row, temp_column, status;
    if (direction == 1)
    {
        temp_row = row - 1;
        status = grid_status[temp_row][column];
    }
    else if (direction == 2)
    {
        temp_row = row + 1;
        status = grid_status[temp_row][column];
    }
    else if (direction == 3)
    {
        temp_column = column - 1;
        status = grid_status[row][temp_column];
    }
    else
    {
        temp_column = column + 1;
        status = grid_status[row][temp_column];
    }
    if (status == 9)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void foward(struct Robot *robot)
{
    int direction = robotDirection();
    if (direction == 1)
    {
        for (int j = 0; j <= 2; j++)
        {
            robot->y_coordinates[j] -= SquareLength;
        } 
        row -= 1;  
    }
    else if (direction == 2)
    {
        for (int j = 0; j <= 2; j++)
        {
            robot->y_coordinates[j] +=  SquareLength;
        }
        row += 1;
    }
    else if (direction == 3)
    {
        for (int i = 0; i <= 2; i++)
        {
            robot->x_coordinates[i] -= SquareLength;
        }
        column -= 1;
    }
    else
    {
        for (int i = 0; i <= 2; i++)
        {
            robot->x_coordinates[i] += SquareLength;
        }
        column += 1;
    }
    if (reversing_movements == 0)
    {
        moves[counter] = 1;
        counter += 1;
    }
    foreground();
    sleep(WaitTime);
    clear();
    drawRobot(robot);  
}

void left(struct Robot *robot)
{
    int direction = robotDirection();
    if (direction == 1)
    {
        robot->x_coordinates[0] += SquareLength;
        robot->y_coordinates[1] -= SquareLength;
        robot->x_coordinates[2] -= SquareLength/2;
        robot->y_coordinates[2] += SquareLength/2;
    }
    else if (direction == 2)
    {
        robot->x_coordinates[0] -= SquareLength;
        robot->y_coordinates[1] += SquareLength;
        robot->x_coordinates[2] += SquareLength/2;
        robot->y_coordinates[2] -= SquareLength/2;
    }
    else if (direction == 3)
    {
        robot->y_coordinates[0] -= SquareLength;
        robot->x_coordinates[1] -= SquareLength;
        robot->x_coordinates[2] += SquareLength/2;
        robot->y_coordinates[2] += SquareLength/2;
    }
    else 
    {
        robot->y_coordinates[0] += SquareLength;
        robot->x_coordinates[1] += SquareLength;
        robot->x_coordinates[2] -= SquareLength/2;
        robot->y_coordinates[2] -= SquareLength/2;
    }
    if (reversing_movements == 0)
    {
        moves[counter] = 2;
        counter += 1;
    }
    foreground();
    sleep(WaitTime);
    clear();
    drawRobot(robot);  
}

void right(struct Robot *robot)
{
    int direction = robotDirection();
    if (direction == 1)
    {
        robot->y_coordinates[0] -= SquareLength;
        robot->x_coordinates[1] -= SquareLength;
        robot->x_coordinates[2] += SquareLength/2;
        robot->y_coordinates[2] += SquareLength/2; 
    }
    else if (direction == 2)
    {
        robot->y_coordinates[0] += SquareLength;
        robot->x_coordinates[1] += SquareLength;
        robot->x_coordinates[2] -= SquareLength/2;
        robot->y_coordinates[2] -= SquareLength/2;
    }
    else if (direction == 3)
    {
        robot->x_coordinates[0] -= SquareLength;
        robot->y_coordinates[1] += SquareLength;
        robot->x_coordinates[2] += SquareLength/2;
        robot->y_coordinates[2] -= SquareLength/2;
    }
    else
    {
        robot->x_coordinates[0] += SquareLength;
        robot->y_coordinates[1] -= SquareLength;
        robot->x_coordinates[2] -= SquareLength/2;
        robot->y_coordinates[2] += SquareLength/2;
    }
    if (reversing_movements == 0)
    {
        moves[counter] = 3;
        counter += 1; 
    }
    foreground();
    sleep(WaitTime);
    clear();
    drawRobot(robot);  
}

int canMoveFoward()
{
    if (!nearObstacle() && !nearWall())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void reverseMoves(struct Robot *robot)
{
    reversing_movements = 1;
    left(robot);
    left(robot);
    for (counter; counter >= 0; counter--)
    {
        if (moves[counter] == 1)
        {
            foward(robot);
        }
        else if (moves[counter] == 2)
        {
            right(robot);
        }
        else if (moves[counter] == 3)
        {
            left(robot);
        }
        foreground();
        clear();
        drawRobot(robot);
    }
}

void drawInputtedRobot(struct Robot *robot)
{
    if (initialRobotDirection == 1)
    {
        robot->x_coordinates[0] = TopLeftOfBorder_X + ((inputColumn - 1) * SquareLength);
        robot->y_coordinates[0] = TopLeftOfBorder_Y + (inputRow * SquareLength);
        robot->x_coordinates[1] = TopLeftOfBorder_X + (inputColumn * SquareLength);
        robot->y_coordinates[1] = TopLeftOfBorder_Y + (inputRow * SquareLength);
        robot->x_coordinates[2] = (robot->x_coordinates[0] + robot->x_coordinates[1]) / 2;
        robot->y_coordinates[2] = TopLeftOfBorder_Y + ((inputRow - 1) * SquareLength);
    }
    else if (initialRobotDirection == 2)
    {
        robot->x_coordinates[0] = TopLeftOfBorder_X + (inputColumn * SquareLength);
        robot->y_coordinates[0] = TopLeftOfBorder_Y + ((inputRow - 1) * SquareLength);
        robot->x_coordinates[1] = TopLeftOfBorder_X + ((inputColumn - 1) * SquareLength);
        robot->y_coordinates[1] = TopLeftOfBorder_Y + ((inputRow - 1) * SquareLength);
        robot->x_coordinates[2] = (robot->x_coordinates[0] + robot->x_coordinates[1]) / 2;
        robot->y_coordinates[2] = TopLeftOfBorder_Y + (inputRow * SquareLength);
    }
    else if (initialRobotDirection == 3)  
    {
        robot->x_coordinates[0] = TopLeftOfBorder_X + (inputColumn * SquareLength);
        robot->y_coordinates[0] = TopLeftOfBorder_Y + (inputRow * SquareLength);
        robot->x_coordinates[1] = TopLeftOfBorder_X + (inputColumn * SquareLength);
        robot->y_coordinates[1] = TopLeftOfBorder_Y + ((inputRow - 1) * SquareLength);
        robot->x_coordinates[2] = TopLeftOfBorder_X + ((inputColumn - 1) * SquareLength);
        robot->y_coordinates[2] = (robot->y_coordinates[0] + robot->y_coordinates[1]) / 2;
    }
    else 
    {
        robot->x_coordinates[0] = TopLeftOfBorder_X + ((inputColumn - 1) * SquareLength);
        robot->y_coordinates[0] = TopLeftOfBorder_Y + ((inputRow - 1) * SquareLength);
        robot->x_coordinates[1] = TopLeftOfBorder_X + ((inputColumn - 1) * SquareLength);
        robot->y_coordinates[1] = TopLeftOfBorder_Y + (inputRow * SquareLength);
        robot->x_coordinates[2] = TopLeftOfBorder_X + (inputColumn * SquareLength);
        robot->y_coordinates[2] = (robot->y_coordinates[0] + robot->y_coordinates[1]) / 2;
    }
    drawRobot(robot);
}

void clearMoveArray()
{
    for (int i = 0; i <= 1000; i++)
    {
        moves[i] = 0;
    }
    counter = 0;
}

int main(int argc, char **argv)
{
    setWindowSize(BackgroundWidth, BackgroundHeight);
    char *inputDirection;
    // Position of Robot if no arguments are entered
    inputRow = 10;
    inputColumn = 1;

    if (argc == 4)
    {
        inputRow = atoi(argv[1]);
        inputColumn = atoi(argv[2]);
        inputDirection = argv[3];
    }
    row = inputRow;
    column = inputColumn;
    grid_status[row][column] = 3;

    if (strcmp(inputDirection, "up") == 0)
    {
        initialRobotDirection = 1;
    }
    else if (strcmp(inputDirection, "down") == 0)
    {
        initialRobotDirection = 2;
    }
    else if (strcmp(inputDirection, "left") == 0)
    {
        initialRobotDirection = 3;
    }
    else 
    {
        initialRobotDirection = 4;
    }

    drawBackground();
    drawMarker(640, 280);
    drawMarker(640, 580);
    drawMarker(280, 400);
    drawInputtedRobot(&robot);

    for (int i = 0; i < markers ; i++)
    {
        while(!atMarker())
    {
            right(&robot);
            while(!atMarker() && canMoveFoward())
            {
                foward(&robot);
            }
    }
        pickUpMarker(&robot);
        reverseMoves(&robot);
        dropMarker(&robot);
        clearMoveArray();
        reversing_movements = 0;
    }
}