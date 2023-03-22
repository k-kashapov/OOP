#include <cstdlib>
#include <functional>
#include <iostream>
#include "model.h"

Model::Model() {
    std::srand(std::time(NULL));

    snake.dir = RIGHT;

    for (int i = 0; i < 7; i++) {
        snake.body.push_back(coord{5, 5});
    }

    for (int i = 0; i < 17; i++) {
        rabbits.push_back(coord{rand() % 15 + 15, rand() % 10 + 10});
    }
}

static void moveCoord(coord &tgt, int dir, int len = 1) {
    switch (dir) {
        case RIGHT:
            tgt.first += len;
            break;
        case LEFT:
            tgt.first -= len;
            if (tgt.first < 0) tgt.first = 0;
            break;
        case DOWN:
            tgt.second += len;
            break;
        case UP:
            tgt.second -= len;
            if (tgt.second < 0) tgt.second = 0;
            break;
        default:
            std::cerr << "Unexpected direction: " << dir << std::endl;
            break;
    }
}

void Model::Update() {
    snake.body.pop_back();

    coord new_head = snake.body.front();
    moveCoord(new_head, snake.dir);

    snake.body.push_front(new_head);

    for (auto &rabbit : rabbits){
        int dir = rand() % 4;
        moveCoord(rabbit, dir);
    }

    return;
}
