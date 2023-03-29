#ifndef MODEL_H
#define MODEL_H

#include <functional>
#include <utility>
#include <list>
#include <cstdlib>
#include <ctime>

using coord = std::pair<unsigned, unsigned>;
using hndlr = std::function<void ()>; 

enum DIRECTIONS {
    UP    = 0,
    LEFT  = 1,
    DOWN  = 2,
    RIGHT = 3,
};

const coord coord_arr[4] = {
    { 0, -1},
    {-1,  0},
    { 0,  1},
    { 1,  0},
};

enum STATES {
    MENU    = 0,
    RUNNING = 1,
    DEAD    = 2,
    WIN     = 3,
};

class Snake {
public:
    std::list<coord> body;
    void onKey(int key);
    int dir = RIGHT;
    unsigned state = RUNNING;
    int score = 0;
};

class Model {
public:
    Model(int num = 1);
    ~Model() {};
    
    void Update();
    std::list<Snake> snakes;
    std::list<coord> rabbits;    

    int isOccupied(coord &where);

    void SetXY(unsigned x, unsigned y);
    void moveCoord(coord &tgt, int dir, unsigned len = 1);

private:
    coord borders;

    void MoveRabbits();
    void MoveSnake(Snake &snake);
};

coord getClosest(const coord &from, const std::list<coord>& to, unsigned *dist_res = NULL);

#endif // MODEL_H
