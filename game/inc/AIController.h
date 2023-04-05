#ifndef AI_H
#define AI_H

#include <list>
#include <functional>
#include "model.h"

class AIController {
private:
    Model* _m;
    Snake* _s;
    int number = 0;
    int adjustDir(coord pos, unsigned cur_dist, int recur);

public:
    AIController(Model *m, Snake *snake, int num);
    ~AIController();
    
    void setSnake(Snake *model);
    void calculatePath();
};

#endif // AI_H
