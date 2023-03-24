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
            if ((++m->body.begin())->second >= m->body.front().second)
                m->dir = UP;
            break;
        case 's':
            if ((++m->body.begin())->second <= m->body.front().second)
                m->dir = DOWN;
            break;
        case 'a':
            if ((++m->body.begin())->first >= m->body.front().first)
                m->dir = LEFT;
            break;
        case 'd':
            if ((++m->body.begin())->first <= m->body.front().first)
                m->dir = RIGHT;
            break;
        default:
            break;
    }
}
