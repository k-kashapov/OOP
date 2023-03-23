#include <iostream>
#include "view.h"
#include "TextView.h"
#include "GUIView.h"

View *View::_curr = NULL;

View *View::get(int what, unsigned x, unsigned y) {
    switch(what) {
        case 1:  [[fallthrough]];
        default:
            if (!View::_curr) {
                if (x > 0 && y > 0) {
                    View::_curr = new TextView{x, y};
                } else {
                    View::_curr = new TextView{};
                }
            }

            return View::_curr;
        
        case 2:
            if (!View::_curr) {
                View::_curr = new GUIView{x, y};
            }

            return View::_curr;
    }
}

void View::setOnKey(std::function<void (int)> func) {
    onKeySubs.push_back(func);
}

void View::callOnKey(int key) {
    for (auto& func : onKeySubs) {
        func(key);
    }
}
