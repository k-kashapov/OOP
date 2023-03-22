#ifndef MODEL_H
#define MODEL_H

#include <functional>
#include <utility>
#include <list>
#include <cstdlib>
#include <ctime>

using coord = std::pair<int, int>;
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
    std::list<coord> rabbits;
    
    Snake snake;
    
    Model();
    ~Model() {};
    
    void Update();
};

#endif // MODEL_H
