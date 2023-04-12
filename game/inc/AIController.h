#ifndef AI_H
#define AI_H

#include <list>
#include <functional>
#include "model.h"

using distFunc = std::function<unsigned (const coord& a, const coord& b)>;

class AIController {
private:
    Model* _m;
    Snake* _s;
    int number = 0;
    int adjustDir(coord pos, unsigned cur_dist);
    distFunc dist;

public:
    AIController(Model *m, Snake *snake, int num);
    ~AIController();
    
    void setSnake(Snake *model);
    void setDistFunc(distFunc);
    void calculatePath();
};

#endif // AI_H
