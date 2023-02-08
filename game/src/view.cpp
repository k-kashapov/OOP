#include <iostream>
#include "view.h"

View *View::_curr = NULL;

View *View::get(int x, int y, int what) {
    switch(what) {
        case 1:  [[fallthrough]];
        default:
            if (!View::_curr) {
                View::_curr = new TextView{x, y};
            }

            return View::_curr;
        
        case 2:
            if (!View::_curr) {
                View::_curr = new GUIView{x, y};
            }

            return View::_curr;
    }
}

void TextView::draw(void) {
    std::cout << "TextView(" << _x << ", " << _y << ") draw called\n";
}

void GUIView::draw(void) {
    std::cout << "GUI draw not implemented\n";
}
