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

SnakeController::SnakeController(Snake *snake, const char* new_keys) {
    View *v = View::get();
    v->setOnKey(std::bind(&SnakeController::onKeyPressed, this, std::placeholders::_1));
    m = snake;
    keys = new_keys;
}

SnakeController::~SnakeController() {}

void SnakeController::setSnake(Snake *snake) {
    m = snake;
}

void SnakeController::onKeyPressed(int key) {
    if (key == keys[UP]) {
        if ((++m->body.begin())->second >= m->body.front().second)
            m->dir = UP;
    } else if (key == keys[DOWN]) {
        if ((++m->body.begin())->second <= m->body.front().second)
            m->dir = DOWN;
    } else if (key == keys[LEFT]) {
        if ((++m->body.begin())->first >= m->body.front().first)
            m->dir = LEFT;
    } else if (key == keys[RIGHT]) {
        if ((++m->body.begin())->first <= m->body.front().first)
            m->dir = RIGHT;
    }
}
