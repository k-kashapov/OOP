#include <cstdlib>
#include <functional>
#include <iostream>
#include "model.h"

#define RABBIT_JMP_LEN  2
#define RABBIT_CD       4 // Rabbit jump cooldown
#define RABBIT_SENSE   20 // Distance of snake detection
#define NEAR_DEATH      3 // Distance of rabbit perpendicular movement

#define SNAKE_CD 1 // Snake movement cooldown

Model::Model(int num) {
    std::srand((unsigned)std::time(NULL));

    for (int i = 0; i < num; i++) {
        snakes.push_back(Snake());
    }

    unsigned init_y = 5;

    for (auto& snake : snakes) {
        snake.dir = RIGHT;

        unsigned init_x = 5;

        for (int i = 0; i < 7; i++) {
            snake.body.push_front(coord{init_x++, init_y});
        }

        for (int i = 0; i < 200; i++) {
            rabbits.push_back(coord{rand() % 15 + 150, rand() % 10 + 40});
        }

        init_y += 3;
    }
}

void Model::moveCoord(coord &tgt, int dir, unsigned len) {
    switch (dir) {
        case RIGHT:
            tgt.first += len;
            if (tgt.first >= borders.first) tgt.first = 1;
            break;
        case LEFT:
            if (tgt.first <= len) tgt.first = borders.first;
            tgt.first -= len;
            break;
        case DOWN:
            tgt.second += len;
            if (tgt.second >= borders.second) tgt.second = 1;
            break;
        case UP:
            if (tgt.second <= len) tgt.second = borders.second;
            tgt.second -= len;
            break;
        default:
            std::cerr << "Unexpected direction: " << dir << std::endl;
            break;
    }
}

static unsigned euclDistSqr(const coord& a, const coord& b) {
    return (a.first - b.first)  * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

coord getClosest(const coord &from, const std::list<coord>& to, unsigned *dist_res) {
    unsigned dist = -1U;
    coord res = to.front();

    for (auto& iter : to) {
        unsigned new_dist = euclDistSqr(from, iter);
        if (new_dist < dist) {
            dist = new_dist;
            res = iter;
            if (dist_res) {
                *dist_res = new_dist;
            }
        }
    }

    return res;
}

void Model::MoveRabbits() {
    for (auto rabbit = rabbits.begin(); rabbit != rabbits.end(); ++rabbit) {
        coord closest;
        Snake *snake;
        unsigned dist = -1U;

        for (auto curr_snake = snakes.begin(); curr_snake != snakes.end(); curr_snake++) {
            unsigned new_dist;
            coord curr_closest = getClosest(*rabbit, curr_snake->body, &new_dist);
            if (new_dist < dist) {
                dist    = new_dist;
                snake   = &(*curr_snake);
                closest = curr_closest;
            }
        }

        int dir = UP;

        if (dist > RABBIT_SENSE * RABBIT_SENSE) {
            dir = rand() % 4;
        } else if (dist < NEAR_DEATH * NEAR_DEATH && dist > 0) {
            dir = (snake->dir + 2) % 4; // Perpendicular movement
        } else {
            if      (closest.first  > rabbit->first)  dir = LEFT;
            else if (closest.second > rabbit->second) dir = UP;
            else if (closest.first  < rabbit->first)  dir = RIGHT;
            else if (closest.second < rabbit->second) dir = DOWN;
            else {
                rabbit = rabbits.erase(rabbit);
                snake->body.push_back(snake->body.back());
            }
        }

        moveCoord(*rabbit, dir, RABBIT_JMP_LEN);
    }
}

void Model::MoveSnake(Snake& snake) {
    snake.body.pop_back();

    coord new_head = snake.body.front();
    moveCoord(new_head, snake.dir);

    for (coord& part: snake.body) {
        if (part == new_head) {
            state = DEAD;
        }
    }

    snake.body.push_front(new_head);
}

void Model::SetXY(unsigned x, unsigned y) {
    borders.first  = x - 1;
    borders.second = y - 1;
}

void Model::Update() {
    static uint64_t frames = 0;
    frames++;

    if (!(frames % SNAKE_CD)) {
        for (auto& snake : snakes)
            MoveSnake(snake);
    }

    if (!(frames % RABBIT_CD)) {
        MoveRabbits();
    }
}
