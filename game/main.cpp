#include <cstdio>
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

        v->draw();

        // printf("drawing end\n");

        while (1) {
            putchar(getchar());
        }

        delete v;
    }

    return 0;
}
