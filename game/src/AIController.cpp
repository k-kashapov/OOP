#include <functional>
#include "AIController.h"
#include "view.h"
#include "model.h"
#include <list>
#include <iostream>

AIController::AIController(Model *m, Snake *snake) {
    _m = m;
    _s = snake;
}

AIController::~AIController() {}

int AIController::adjustDir() {
    coord head = _s->body.front();

    // std::cerr << "dir = " << _s->dir << std::endl;

    coord newhead = _m->moveCoord(head, _s->dir);

    // std::cerr << "newhead = (" << newhead.first << ", " << newhead.second << ")" << std::endl;

    if (_m->isOccupied(newhead) != 1) {
        return _s->dir;
    }

    unsigned newdir = ((unsigned)_s->dir + 1) % 4;

    // std::cerr << "newdir = " << newdir << std::endl;
    newhead = _m->moveCoord(head, (int)newdir);
    // std::cerr << "newhead = (" << newhead.first << ", " << newhead.second << ")" << std::endl;

    if (_m->isOccupied(newhead) != 1) {
        return (int)newdir;
    }

    newdir = ((unsigned)_s->dir - 1) % 4;

    // std::cerr << "newdir = " << newdir << std::endl;
    newhead = _m->moveCoord(head, (int)newdir);
    // std::cerr << "newhead = (" << newhead.first << ", " << newhead.second << ")" << std::endl;

    if (_m->isOccupied(newhead) != 1) {
        return (int)newdir;
    }

    newdir = ((unsigned)_s->dir + 2) % 4;

    // std::cerr << "newdir = " << newdir << std::endl;
    newhead = _m->moveCoord(head, (int)newdir);
    // std::cerr << "newhead = (" << newhead.first << ", " << newhead.second << ")" << std::endl;

    if (_m->isOccupied(newhead) != 1) {
        return (int)newdir;
    }

    // std::cerr << "ded\n";

    return _s->dir;
}

void AIController::calculatePath() {
    coord head    = _s->body.front();
    coord closest = _m->getClosest(head, _m->rabbits);

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

