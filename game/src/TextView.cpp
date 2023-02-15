#include <iostream>
#include "TextView.h"

pair_t TextView::WinXY(void) {
    return pair_t { 100, 100 };
}

void TextView::draw(void) {
    std::cout << "TextView(" << _x << ", " << _y << ") draw called\n";
}
