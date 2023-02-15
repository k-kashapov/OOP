#ifndef GUIVIEW_H
#define GUIVIEW_H

#include "view.h"

class GUIView : public View {
public:
    void draw(void);
    int  WinXY(void);

    GUIView(void) {}

    GUIView(int x, int y):
        View(x, y)
    {}
    
    ~GUIView()
    {}
};

#endif // GUIVIEW_H