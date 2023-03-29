#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>
#include <functional>
#include "model.h"

class SnakeController {
private:
    Snake* m;
    const char *keys = "wsad";

public:
    SnakeController();
    SnakeController(Snake *snake);
    SnakeController(Snake *snake, const char *new_keys);
    ~SnakeController();
    
    void onKeyPressed(int key);
    void setSnake(Snake *model);
};

#endif // CONTROLLER_H
