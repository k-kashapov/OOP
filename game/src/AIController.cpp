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
}

AIController::~AIController() {}

int AIController::adjustDir(coord pos, unsigned cur_dist, int recur) {
    // std::cerr << "snake num " << number << "\n";

    unsigned found_dist = cur_dist;
    int      picked_dir = -1;
    coord    head       = pos;

    int checked_dir = _s->dir;
    coord newhead   = _m->moveCoord(head, checked_dir);

    // std::cerr << "checking dir = " << checked_dir << "; newhead = (" << newhead.first << ", " << newhead.second << ")\n";

    if (_m->isOccupied(newhead, 0, &head) != 1) {
        _m->getClosest(newhead, _m->rabbits, &found_dist);
        if (found_dist <= cur_dist) {
            picked_dir = checked_dir;
            cur_dist   = found_dist;
            // std::cerr << "found dir = " << picked_dir << "; dist = " << cur_dist << "\n";
        }
    }

    checked_dir = (int)(((unsigned)checked_dir + 1) % 4);
    newhead = _m->moveCoord(head, checked_dir);

    // std::cerr << "checking dir = " << checked_dir << "; newhead = (" << newhead.first << ", " << newhead.second << ")\n";

    if (_m->isOccupied(newhead, 0, &head) != 1) {
        _m->getClosest(newhead, _m->rabbits, &found_dist);
        if (found_dist < cur_dist) {
            picked_dir = checked_dir;
            cur_dist   = found_dist;
            // std::cerr << "found dir = " << picked_dir << "; dist = " << cur_dist << "\n";
        }
    }

    checked_dir = (int)(((unsigned)checked_dir + 2) % 4);
    newhead = _m->moveCoord(head, checked_dir);

    // std::cerr << "checking dir = " << checked_dir << "; newhead = (" << newhead.first << ", " << newhead.second << ")\n";

    if (_m->isOccupied(newhead, 0, &head) != 1) {
        _m->getClosest(newhead, _m->rabbits, &found_dist);
        if (found_dist < cur_dist) {
            picked_dir = checked_dir;
            cur_dist   = found_dist;
            // std::cerr << "found dir = " << picked_dir << "; dist = " << cur_dist << "\n";
        }
    }

    // std::cerr << "returning: " << picked_dir << "\n";

    return picked_dir;
}

void AIController::calculatePath() {
    if (_s->state != RUNNING) return;
    coord    head     = _s->body.front();
    
    _m->getClosest(head, _m->rabbits);
    int newdir = adjustDir(head, -1U, 1);
    if (newdir >= 0) {
        _s->dir = newdir;
    }
}

void AIController::setSnake(Snake *snake) {
    _s = snake;
}

