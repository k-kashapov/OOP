#include <iostream>
#include "view.h"
#include "TextView.h"
#include "GUIView.h"

View *View::_curr = NULL;

View *View::get(int what) {
    switch(what) {
        case 1:  [[fallthrough]];
        default:
            if (!View::_curr) {
                View::_curr = new TextView{};
            }

            return View::_curr;
        
        case 2:
            if (!View::_curr) {
                View::_curr = new GUIView{};
            }

            return View::_curr;
    }
}
