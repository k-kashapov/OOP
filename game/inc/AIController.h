#ifndef AI_H
#define AI_H

#include <list>
#include <functional>
#include "model.h"

class AIController {
private:
    Model* _m;
    Snake* _s;
    int adjustDir();

public:
    AIController(Model *m, Snake *snake);
    ~AIController();
    
    void setSnake(Snake *model);
    void calculatePath();
};

#endif // AI_H
