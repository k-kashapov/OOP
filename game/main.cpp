#include <stdio.h>
#include <iostream>
#include "view.h"

int main(int argc, const char **argv)
{
    View *v;

    if(argc > 1) {
        if (std::string(argv[1]) == "GUI") {
            v = View::get(GUI_TYPE);
        } else {
            v = View::get(TEXT_TYPE);
        }

        while (1) {
            v->draw();
        }

        delete v;
    }

    return 0;
}
