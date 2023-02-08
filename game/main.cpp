#include <iostream>
#include "view.h"

int main(int argc, const char **argv)
{
    View *v;

    if(argc > 1)
    {
        if (std::string(argv[1]) == "GUI") {
            v = View::get(500, 60, 2);
        } else {
            v = View::get(10, 100, 1);
        }

        v->draw();

        delete v;
    }

    return 0;
}
