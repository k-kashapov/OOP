#include <functional>
#include "AIController.h"
#include "view.h"

AIController::AIController(Snake *snake, std::list<coord> *rabbits) {
    View *v = View::get();
    v->subTimer(100, std::bind(&AIController::calculatePath, this));
    m = snake;
    r = rabbits;
}

AIController::~AIController() {}

void AIController::calculatePath() {
    coord closest = getClosest(m->body.front(), *r);
    
}

void AIController::setSnake(Snake *snake) {
    m = snake;
}

