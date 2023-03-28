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

        Model m{2};
        SnakeController c(&m.snakes.front());

        AIController ai1(&*(++m.snakes.begin()), &m.rabbits);

        v->setModel(&m);
        v->subTimer(120, std::bind(&AIController::calculatePath, &ai1));
        v->subTimer(60, std::bind(&Model::Update, &m));
        
        v->loop();

        delete v;
    }

    return 0;
}
