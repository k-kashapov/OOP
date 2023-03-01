#include <cstdlib>
#include <iostream>
#include "model.h"

enum DIRECTIONS {
    UP    = 0,
    DOWN  = 1,
    LEFT  = 2,
    RIGHT = 3,
};

Model::Model() {
    std::srand(std::time(NULL));

    for (int i = 0; i < 7; i++) {
        snake.push_back(coord{5, 5});
    }

    for (int i = 0; i < 7; i++) {
        rabbits.push_back(coord{rand() % 20 + 20, rand() % 20});
    }
}

void Model::Update() {
    snake.pop_back();

    coord new_head = snake.front();
    new_head.first += 1;

    snake.push_front(new_head);

    for (auto &rabbit : rabbits){
        int dir = rand() % 4;
        switch (dir) {
            case RIGHT:
                rabbit.first += 1;
                break;
            case LEFT:
                rabbit.first -= 1;
                break;
            case DOWN:
                rabbit.second += 1;
                break;
            case UP:
                rabbit.second -= 1;
                break;
            default:
                std::cout << "Unexpected direction: %d\n" << std::endl;
                break;
        }
    }

    return;
}
