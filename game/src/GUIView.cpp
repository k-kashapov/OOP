#include <iostream>
#include "GUIView.h"
#include "window.h"

pair_t GUIView::WinXY(void) {
    return pair_t { 100, 100 };
}

void GUIView::draw(void) {
    std::cout << "GUI draw not implemented\n";
}
