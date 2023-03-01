#ifndef VIEW_H
#define VIEW_H

#include <sys/ioctl.h>
#include "model.h"

enum VIEW_TYPE {
    TEXT_TYPE = 1,
    GUI_TYPE  = 2,
};

class View {
public:
    int _x, _y;
    Model* _model;

    virtual void draw    (void)         = 0;
    virtual void clear   (void)         = 0;
    virtual int  WinXY   (void)         = 0;
    virtual void setModel(Model* model) = 0;
    
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
