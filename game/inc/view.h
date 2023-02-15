#ifndef VIEW_H
#define VIEW_H

#include "window.h"

#define GUI_TYPE  2
#define TEXT_TYPE 1

class View {
public:
    int _x, _y;
    virtual void   draw(void)  = 0;
    virtual pair_t WinXY(void) = 0;
    
    View(void){}

    View(int x, int y):
        _x(x), _y(y)
    {}

    static View *get(int what = 0);
    static View *_curr;

    virtual ~View()
    {}
};

#endif // VIEW_H
