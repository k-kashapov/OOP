#include <functional>
#include "AIController.h"
#include "view.h"
#include "model.h"
#include <list>
#include <iostream>

AIController::AIController(Model *m, Snake *snake, int num) {
    _m = m;
    _s = snake;
    number = num;
    // dist = std::bind(&Model::euclDistSqr, _m, std::placeholders::_2);
}

AIController::~AIController() {}

int AIController::adjustDir(coord pos, unsigned cur_dist) {
    unsigned found_dist = cur_dist;
    int      picked_dir = -1;
    coord    head       = pos;

    int checked_dir = _s->dir;
    coord newhead   = _m->moveCoord(head, checked_dir);

    if (_m->isOccupied(newhead, 0, &head) != 1) {
        _m->getClosest(newhead, _m->rabbits, &found_dist);
        if (found_dist <= cur_dist) {
            picked_dir = checked_dir;
            cur_dist   = found_dist;
        }
    }

    checked_dir = (int)(((unsigned)checked_dir + 1) % 4);
    newhead = _m->moveCoord(head, checked_dir);

    if (_m->isOccupied(newhead, 0, &head) != 1) {
        _m->getClosest(newhead, _m->rabbits, &found_dist);
        if (found_dist < cur_dist) {
            picked_dir = checked_dir;
            cur_dist   = found_dist;
        }
    }

    checked_dir = (int)(((unsigned)checked_dir + 2) % 4);
    newhead = _m->moveCoord(head, checked_dir);

    if (_m->isOccupied(newhead, 0, &head) != 1) {
        _m->getClosest(newhead, _m->rabbits, &found_dist);
        if (found_dist < cur_dist) {
            picked_dir = checked_dir;
            cur_dist   = found_dist;
        }
    }

    return picked_dir;
}

void AIController::calculatePath() {
    if (_s->state != RUNNING) return;
    coord head = _s->body.front();
    
    _m->getClosest(head, _m->rabbits);
    int newdir = adjustDir(head, -1U);
    if (newdir >= 0) {
        _s->dir = newdir;
    }
}

void AIController::setSnake(Snake *snake) {
    _s = snake;
}

