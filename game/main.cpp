#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "view.h"
#include "HumanController.h"

int main(int argc, const char **argv) {
    View *v;

    if(argc > 1) {
        if (std::string(argv[1]) == "GUI") {
            if (argc < 4) {
                std::cout << "USAGE: main.elf GUI [x: int] [y: int]" << std::endl;
                return 0;
            }

            v = View::get(GUI_TYPE, std::stoi(argv[2]), std::stoi(argv[3]));
        } else {
            v = View::get(TEXT_TYPE);
        }

        Model m{};
        SnakeController c(&m.snake);

        v->setModel(&m);

        v->loop();

        delete v;
    }

    return 0;
}
