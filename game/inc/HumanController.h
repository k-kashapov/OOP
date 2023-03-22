#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>
#include <functional>
#include "model.h"

class SnakeController {
private:
    Snake* m;

public:
    SnakeController();
    SnakeController(Snake *snake);
    ~SnakeController();
    
    void onKeyPressed(int key);
    void setSnake(Snake *model);
};

#endif // CONTROLLER_H
