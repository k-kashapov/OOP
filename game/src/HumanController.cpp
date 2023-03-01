#include <functional>
#include "HumanController.h"
#include "view.h"

SnakeController::SnakeController() {
    View *v = View::get();
    v->setOnKey(std::bind(&SnakeController::onKeyPressed, this, std::placeholders::_1));
}

SnakeController::~SnakeController() {}

void SnakeController::setSnake(Snake *snake) {
    m = snake;
}

void SnakeController::onKeyPressed(int key) {
    switch (key) {
        case 'w':
            m->dir = UP;
            break;
        case 'a':
            m->dir = DOWN;
            break;
        case 's':
            m->dir = LEFT;
            break;
        case 'd':
            m->dir = RIGHT;
            break;
        default:
            break;
    }
}
