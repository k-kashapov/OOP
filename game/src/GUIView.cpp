#include <iostream>
#include "GUIView.h"

int GUIView::WinXY(void) {
    _x = _y = 0;
    return 0;
}

void GUIView::setModel(Model *model) {
    (void) model;
    std::cout << "GUIView(" << _x << ", " << _y << ") set Model called\n";
}

void GUIView::draw(void) {
    std::cout << "GUIView(" << _x << ", " << _y << ") draw called\n";
}

void GUIView::clear(void) {
    std::cout << "GUIView(" << _x << ", " << _y << ") clear called\n";
}
