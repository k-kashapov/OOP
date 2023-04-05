#include <cstdlib>
#include <functional>
#include <iostream>
#include "model.h"

#define RABBIT_JMP_LEN  2
#define RABBIT_CD       8 // Rabbit jump cooldown
#define RABBIT_SENSE   60 // Distance of snake detection
#define NEAR_DEATH      4 // Distance of rabbit perpendicular movement

#define SNAKE_CD 1  // Snake movement cooldown

#define RABBIT_RESPAWN_CD 10

Model::Model(int num) {
    std::srand((unsigned)std::time(NULL));

    for (int i = 0; i < num; i++) {
        snakes.push_back(Snake());
    }

    for (auto& snake : snakes) {
        snake.dir = RIGHT;

        unsigned init_x = (unsigned)rand() % 80;
        unsigned init_y = (unsigned)rand() % 40;

        for (int i = 0; i < 7; i++) {
            snake.body.push_front(coord{init_x++, init_y});
        }

        init_y += 5;
    }

    for (int i = 0; i < 15; i++) {
        rabbits.push_back(coord{rand() % 100, rand() % 100});
    }
}

void Model::addRabbit() {
    rabbits.push_back(coord{(unsigned)rand() % borders.first, (unsigned)rand() % borders.second});
}

int Model::isOccupied(coord &where, bool check_rab, coord* myhead) {
    for (auto& snk : snakes) {
        for (coord &part : snk.body) {
            // std::cerr << "checking (" << part.first << ", " << part.second << ")\n";

            if (part.first == where.first && part.second == where.second) {
                // std::cerr << "isOccupied snake\n";
                return 1;
            }
        }

        coord head = snk.body.front();
        if (head != *myhead) {
            head = moveCoord(head, snk.dir);
            if (head == where) return 1;
        }
    }

    if (check_rab) {
        for (coord &rab : rabbits) {
            // std::cerr << "checking rabbit (" << rab.first << ", " << rab.second << ")\n";
            if (rab.first == where.first && rab.second == where.second) {
                // std::cerr << "isOccupied rabbit\n";
                return -1;
            }
        }
    }

    // std::cerr << "notOccupied\n";
    return 0;
}

coord Model::moveCoord(coord tgt, int dir, unsigned len) {
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

    return tgt;
}

unsigned Model::euclDistSqr(const coord& a, const coord& b) {
    int diff_x = (int)(a.first % borders.first) - (int)(b.first % borders.first);
    int diff_y = (int)(a.second % borders.second) - (int)(b.second % borders.second);
    return (unsigned)(abs(diff_x) + abs(diff_y));
}

coord Model::getClosest(const coord &from, const std::list<coord>& to, unsigned *dist_res) {
    unsigned dist = -1U;
    coord res = to.front();

    for (auto& iter : to) {
        unsigned new_dist = euclDistSqr(from, iter);
        if (new_dist <= dist) {
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
            return;
        } else if (dist > RABBIT_SENSE * RABBIT_SENSE) {
            return;
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

        *rabbit = moveCoord(*rabbit, dir, RABBIT_JMP_LEN);
    }
}

void Model::MoveSnake(Snake& snake) {
    if (snake.state != RUNNING) {
        return;
    }

    snake.body.pop_back();

    coord new_head = snake.body.front();
    new_head = moveCoord(new_head, snake.dir);

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
    
    for (auto r = rabbits.begin(); r != rabbits.end(); r++) {
        unsigned dist = euclDistSqr(new_head, *r);        

        if (dist == 0) {
            rabbits.erase(r);
            snake.body.push_back(snake.body.back());
            snake.score += 100;
            return;
        }
    }
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

    if (!(frames % RABBIT_RESPAWN_CD)) {
        addRabbit();
    }
}
