#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <vector>
#include "cdT.h"

typedef enum { up, down, left, right } directionT;
typedef enum { start, pregame, controls, ingame, stopped, end } stateT;

class Snake
{
private:
public:
    Snake(int);
    directionT direction;
    cdT head;
    std::vector<cdT*>* snake_body_vector;
    cdT apple;
    bool CollidedIntoWall();
    bool AteApple();
    void createApple();
    void grow();
    void move();
    void changeDirection(directionT);
    void print();
    int getScore();
    void testprint();
    void gotoxy(int, int);
};

#endif