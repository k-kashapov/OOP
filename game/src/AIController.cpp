#include <functional>
#include "AIController.h"
#include "view.h"
#include "model.h"
#include <list>

AIController::AIController(Snake *snake, std::list<coord> *rabbits) {
    m = snake;
    r = rabbits;
}

AIController::~AIController() {}

static int adjustDir(Snake *snk) {
    int dirPicked = -1;
    coord& head = snk->body.front();

    for (int cur = snk->dir; (cur + 1) % 4 != snk->dir && dirPicked < 0; cur = (cur + 1) % 4) {
        dirPicked = cur;

        coord new_head = coord_arr[cur];
        new_head.first  += head.first;
        new_head.second += head.second;

        for (auto& part : snk->body) {
            if (new_head == part) {
                dirPicked = -1;
                break;
            }
        }
    }

    return dirPicked < 0 ? snk->dir : dirPicked;
}

void AIController::calculatePath() {
    coord head = m->body.front();
    coord closest = getClosest(head, *r);

    int xdiff = (int)closest.first  - (int)head.first;
    int ydiff = (int)closest.second - (int)head.second;

    if (xdiff > ydiff) {
        if (xdiff < 0) {
            m->dir = LEFT;
        } else {
            m->dir = RIGHT;
        }
    }  else {
        if (ydiff < 0) {
            m->dir = UP;
        } else {
            m->dir = DOWN;
        }
    }

    m->dir = adjustDir(m);
}

void AIController::setSnake(Snake *snake) {
    m = snake;
}

