#include <cstdlib>
#include <functional>
#include <iostream>
#include "model.h"

#define RABBIT_JMP_LEN  2
#define RABBIT_CD       4 // Rabbit jump cooldown
#define RABBIT_SENSE   50 // Distance of snake detection
#define NEAR_DEATH      4 // Distance of rabbit perpendicular movement

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

        init_y += 10;
    }

    for (int i = 0; i < 600; i++) {
        rabbits.push_back(coord{rand() % 100, rand() % 100});
    }
}

int Model::isOccupied(coord &where) {
    for (coord &rab : rabbits) {
        if (rab == where) {
            return -1;
        }
    }

    for (auto& snk : snakes) {
        for (coord &part : snk.body) {
            if (part == where) {
                return 1;
            }
        }
    }

    return 0;
}

void Model::moveCoord(coord &tgt, int dir, unsigned len) {
    switch (dir) {
        case RIGHT:
            tgt.first += len;
            if (tgt.first >= borders.first) tgt.first -= borders.first - 1;
            break;
        case LEFT:
            if (tgt.first <= len) tgt.first += borders.first;
            tgt.first -= len;
            break;
        case DOWN:
            tgt.second += len;
            if (tgt.second >= borders.second) tgt.second -= borders.second - 1;
            break;
        case UP:
            if (tgt.second <= len) tgt.second += borders.second;
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
        auto snake = snakes.begin();
        unsigned dist = -1U;

        for (auto curr_snake = snakes.begin(); curr_snake != snakes.end(); curr_snake++) {
            unsigned new_dist = 0;
            coord curr_closest = getClosest(*rabbit, curr_snake->body, &new_dist);
            if (new_dist < dist) {
                dist    = new_dist;
                snake   = curr_snake;
                closest = curr_closest;
            }
        }

        int dir = UP;
        int xdiff = (int)closest.first  - (int)rabbit->first;
        int ydiff = (int)closest.second - (int)rabbit->second;

        if (xdiff == 0 && ydiff == 0) {
            rabbit = rabbits.erase(rabbit);
            snake->body.push_back(snake->body.back());
            snake->score += 100;
            return;
        } else if (dist > RABBIT_SENSE * RABBIT_SENSE) {
            dir = rand() & 0xF;
        } else if (dist < NEAR_DEATH * NEAR_DEATH) {
            dir = (snake->dir + 1) % 4; // Perpendicular movement
        } else {
            if (xdiff > ydiff) {
                if (xdiff > 0) {
                    dir = LEFT;
                } else {
                    dir = RIGHT;
                }
            } else {
                if (ydiff < 0) {
                    dir = DOWN;
                } else {
                    dir = UP;
                }
            }
        }

        moveCoord(*rabbit, dir, RABBIT_JMP_LEN);
    }
}

void Model::MoveSnake(Snake& snake) {
    if (snake.state != RUNNING) {
        if (snake.body.size() > 2) {
            snake.body.pop_back();
            return;
        } else {
            snake.state = RUNNING;
            return;
        }
    }

    snake.body.pop_back();

    coord new_head = snake.body.front();
    moveCoord(new_head, snake.dir);

    for (auto& snk : snakes) {
        for (coord& part: snk.body) {
            if (part == new_head) {
                snake.state = DEAD;
                snake.body.push_front(new_head);
                return;
            }
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
