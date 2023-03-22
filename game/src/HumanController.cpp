#include <functional>
#include "HumanController.h"
#include "view.h"

SnakeController::SnakeController() {
    View *v = View::get();
    v->setOnKey(std::bind(&SnakeController::onKeyPressed, this, std::placeholders::_1));
}

SnakeController::SnakeController(Snake *snake) {
    View *v = View::get();
    v->setOnKey(std::bind(&SnakeController::onKeyPressed, this, std::placeholders::_1));
    m = snake;
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
        case 's':
            m->dir = DOWN;
            break;
        case 'a':
            m->dir = LEFT;
            break;
        case 'd':
            m->dir = RIGHT;
            break;
        default:
            break;
    }
}
