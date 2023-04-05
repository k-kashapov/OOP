#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "view.h"
#include "HumanController.h"
#include "AIController.h"

int main(int argc, const char **argv) {
    View *v;

    if(argc > 1) {
        if (std::string(argv[1]) == "GUI") {
            if (argc < 4) {
                std::cout << "USAGE: main.elf GUI [x: int] [y: int]" << std::endl;
                return 0;
            }

            v = View::get(GUI_TYPE, (unsigned) std::stoul(argv[2]), (unsigned) std::stoul(argv[3]));
        } else {
            v = View::get(TEXT_TYPE);
        }

        Model m{7};
        // SnakeController c1(&m.snakes.front());
        // SnakeController c2(&m.snakes.back(), "ikjl");

        auto begin = m.snakes.begin();

        AIController ai1(&m, &*(begin++), 1);
        AIController ai2(&m, &*(begin++), 2);
        AIController ai3(&m, &*(begin++), 3);
        AIController ai4(&m, &*(begin++), 4);
        AIController ai5(&m, &*(begin++), 5);
        AIController ai6(&m, &*(begin++), 6);
        AIController ai7(&m, &*(begin++), 7);
        
        v->subTimer(150, std::bind(&AIController::calculatePath, &ai1));
        v->subTimer(150, std::bind(&AIController::calculatePath, &ai2));
        v->subTimer(150, std::bind(&AIController::calculatePath, &ai3));
        v->subTimer(150, std::bind(&AIController::calculatePath, &ai4));
        v->subTimer(150, std::bind(&AIController::calculatePath, &ai5));
        v->subTimer(150, std::bind(&AIController::calculatePath, &ai6));
        v->subTimer(150, std::bind(&AIController::calculatePath, &ai7));

        v->setModel(&m);
        v->subTimer(150, std::bind(&Model::Update, &m));
        
        v->loop();

        delete v;

        getchar();

    } else {
        std::cout << "USAGE: ./main.elf [TEXT | GUI] [Xres] [Yres]" << std::endl;
    }

    return 0;
}
