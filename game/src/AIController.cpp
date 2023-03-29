#include <functional>
#include "AIController.h"
#include "view.h"
#include "model.h"
#include <list>

AIController::AIController(Model *m, Snake *snake) {
    _m = m;
    _s = snake;
}

AIController::~AIController() {}

int AIController::adjustDir() {
    coord head = _s->body.front();

    _m->moveCoord(head, _s->dir);

    if (_m->isOccupied(head) != 1) {
        return _s->dir;
    }

    head = _s->body.front();

    int newdir = (4 - _s->dir - 1) % 4;

    _m->moveCoord(head, newdir);

    if (_m->isOccupied(head) != 1) {
        return newdir;
    }
    
    newdir = (_s->dir + 1) % 4;

    head = _s->body.front();

    _m->moveCoord(head, newdir);

    if (_m->isOccupied(head) != 1) {
        return newdir;
    }

    return _s->dir;
}

void AIController::calculatePath() {
    coord head    = _s->body.front();
    coord closest = getClosest(head, _m->rabbits);

    int xdiff = (int)closest.first  - (int)head.first;
    int ydiff = (int)closest.second - (int)head.second;

    if (xdiff > ydiff) {
        if (xdiff < 0) {
            _s->dir = LEFT;
        } else {
            _s->dir = RIGHT;
        }
    }  else {
        if (ydiff < 0) {
            _s->dir = UP;
        } else {
            _s->dir = DOWN;
        }
    }

    _s->dir = adjustDir();
}

void AIController::setSnake(Snake *snake) {
    _s = snake;
}

