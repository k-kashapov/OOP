#ifndef AI_H
#define AI_H

#include <list>
#include <functional>
#include "model.h"

class AIController {
private:
    Snake* m;
    std::list<coord> *r;

public:
    AIController(Snake *snake, std::list<coord> *rabbits);
    ~AIController();
    
    void setSnake(Snake *model);
    void calculatePath();
};

#endif // AI_H
