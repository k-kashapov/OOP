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

class Snake {
public:
    std::list<coord> body;
    DIRECTIONS dir;
    void onKey(int key);
};

class Model {
public:    
    Model();
    ~Model() {};
    
    void Update();
    Snake snake;
    std::list<coord> rabbits;    

    void SetXY(unsigned x, unsigned y);

private:
    coord borders;

    void MoveRabbits();
    int  RabbitEaten();
    void moveCoord(coord &tgt, int dir, unsigned len = 1);
};

#endif // MODEL_H
