#ifndef VIEW_H
#define VIEW_H

#include <functional>
#include <sys/ioctl.h>
#include "model.h"

enum VIEW_TYPE {
    TEXT_TYPE = 1,
    GUI_TYPE  = 2,
};

class View {
protected:
    std::list<std::function<void(int)>> onKeySubs;

public:
    int _x, _y;
    Model* _model;

    virtual void loop    ()             = 0;
    virtual void clear   ()             = 0;
    virtual int  WinXY   ()             = 0;
    virtual void setModel(Model* model) = 0;
    virtual int  getKey  ()             = 0;
    
    View(void){}

    View(int x, int y):
        _x(x), _y(y)
    {}
    
    void setOnKey(std::function<void(int)>);
    void callOnKey(int key);
    
    static View *get(int what = 0, int x = -1, int y = -1);
    static View *_curr;

    virtual ~View()
    {}
};

#endif // VIEW_H
