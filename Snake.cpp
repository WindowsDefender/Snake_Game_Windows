#include "Snake.h"
#include <time.h>
#include <conio.h>
#include <iostream>
#include <Windows.h>

int gridsize = 30;
int upper = gridsize - 4;
int lower = 4;

void Snake::gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE Current_Console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(Current_Console, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(Current_Console, &cursorInfo);
}

Snake::Snake(int length)
{
    int i;
    bool first = true;
    this->snake_body_vector = new std::vector <cdT*>();
    for (i = 1; i <= length; i++)
    {
        cdT* coordinate = new cdT();
        
        coordinate->x = i;
        coordinate->y = 1;
        this->snake_body_vector->push_back(coordinate);
    }
    //default direction for the snake is going to the right, which is why when constructing a snake, 
    //we start with the assumption that the snake is going to the right.
    this->direction = right;
    this->head = *(this->snake_body_vector->at(this->snake_body_vector->size() - 1));
}

void Snake::createApple()
{
    srand(time(NULL));
    bool same = true;
    int i = 0;
    while (same)
    {
        this->apple.x = (rand() % (upper - lower + 1)) + lower;
        this->apple.y = (rand() % (upper - lower + 1)) + lower;
        for (i = 0; i < (int) this->snake_body_vector->size(); i++)
        {
            if (this->snake_body_vector->at(i)->x == this->apple.x
                && this->snake_body_vector->at(i)->y == this->apple.y)
            {
                i = 0;
                break;
            }
        }
        if (i == this->snake_body_vector->size())
        {
            same = false;
        }
    }
    this->gotoxy(this->apple.x * 2 - 1, this->apple.y);
    printf("A");
}

void Snake::move() {
    cdT* coordinate = new cdT();
    switch (this->direction)
    {
    case up:
        coordinate->x = this->head.x;
        coordinate->y = this->head.y - 1;
        break;
    case down:
        coordinate->x = this->head.x;
        coordinate->y = this->head.y + 1;
        break;
    case right:
        coordinate->x = this->head.x + 1;
        coordinate->y = this->head.y;
        break;
    case left:
        coordinate->x = this->head.x - 1;
        coordinate->y = this->head.y;
        break;
    }
    this->snake_body_vector->push_back(coordinate);
    this->head = *(this->snake_body_vector->at(this->snake_body_vector->size() - 1));
    gotoxy(this->snake_body_vector->at(0)->x*2-1, this->snake_body_vector->at(0)->y);
    printf("-");
    this->snake_body_vector->erase(this->snake_body_vector->begin());
}

void Snake::changeDirection(directionT newdirection)
{
    bool correct_direction = false;
    switch (this->direction)
    {
    case up:
        if (newdirection != down)
            correct_direction = true;
        break;
    case down:
        if (newdirection != up)
            correct_direction = true;
        break;
    case left:
        if (newdirection != right)
            correct_direction = true;
        break;
    case right:
        if (newdirection != left)
            correct_direction = true;
        break;
    }
    if (correct_direction) this->direction = newdirection;
}

bool Snake::CollidedIntoWall()
{
    for (int i = 0; i < (int) this->snake_body_vector->size() - 1; i++)
    {
        if (this->head.x == this->snake_body_vector->at(i)->x
            && this->head.y == this->snake_body_vector->at(i)->y) return true;
    }
    if ((this->head.x == 0 || this->head.y == 0)) return true;
    else if ((this->head.x == gridsize -1 || this->head.y == gridsize - 1)) return true;
    else return false;
}

bool Snake::AteApple()
{
    if (this->head.y == this->apple.y && this->head.x == this->apple.x) return true;
    else return false;
}

void Snake::grow()
{
    cdT* coordinate = new cdT();
    switch (this->direction)
    {
    case up:
        coordinate->x = this->head.x;
        coordinate->y = this->head.y - 1;
        break;
    case down:
        coordinate->x = this->head.x;
        coordinate->y = this->head.y + 1;
        break;
    case right:
        coordinate->x = this->head.x + 1;
        coordinate->y = this->head.y;
        break;
    case left:
        coordinate->x = this->head.x - 1;
        coordinate->y = this->head.y;
        break;
    }
    this->snake_body_vector->push_back(coordinate);
    this->head = *(this->snake_body_vector->at(this->snake_body_vector->size() - 1));
}




void Snake::print()
{
    ShowConsoleCursor(false);



    int i = 0;//column
    int j = 0;//row
    int v = 0;//index of the vector
    bool found;//flag for body of the snake

    for (int i=0; i < (int) this->snake_body_vector->size(); i++)
    {
        gotoxy(this->snake_body_vector->at(i)->x *2 -1, this->snake_body_vector->at(i)->y);
        printf("o");
    }
}

int Snake::getScore()
{
    return (int)this->snake_body_vector->size();
}


void Snake::testprint()
{
    for (int i = 1; i < gridsize - 1; i++)
    {
        for (int j = 1; j <gridsize-1; j++)
        {
            gotoxy(i * 2 - 1, j );
            printf("-");
        }
    }
}