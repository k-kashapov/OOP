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
    DOWN  = 1,
    LEFT  = 2,
    RIGHT = 3,
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
    DIRECTIONS dir = RIGHT;
};

class Model {
public:
    unsigned state = RUNNING;

    Model(int num = 1);
    ~Model() {};
    
    void Update();
    std::list<Snake> snakes;
    std::list<coord> rabbits;    

    void SetXY(unsigned x, unsigned y);

private:
    coord borders;

    void MoveRabbits();
    void MoveSnake(Snake &snake);
    void moveCoord(coord &tgt, int dir, unsigned len = 1);
};

coord getClosest(const coord &from, const std::list<coord>& to, unsigned *dist_res = NULL);

#endif // MODEL_H
