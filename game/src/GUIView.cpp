#include <iostream>
#include "GUIView.h"

int GUIView::WinXY(void) {
    _x = _y = 0;
    return 0;
}

void GUIView::draw(void) {
    std::cout << "GUIView(" << _x << ", " << _y << ") draw called\n";
}
