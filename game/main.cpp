#include <stdio.h>
#include <iostream>
#include "view.h"
#include "HumanController.h"

int main(int argc, const char **argv) {
    View *v;

    if(argc > 1) {
        if (std::string(argv[1]) == "GUI") {
            v = View::get(GUI_TYPE);
        } else {
            v = View::get(TEXT_TYPE);
        }

        SnakeController c{};
        Model m{};

        c.setSnake(&m.snake);
        v->setModel(&m);

        while (1) {
            int key = v->getKey();
            if (key > 0) {
                v->callOnKey(key);
            }

            v->draw();
        }

        delete v;
    }

    return 0;
}
