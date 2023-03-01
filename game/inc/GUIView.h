#ifndef GUIVIEW_H
#define GUIVIEW_H

#include "view.h"

class GUIView : public View {
public:
    void draw    (void)         override;
    void clear   (void)         override;
    int  WinXY   (void)         override;
    void setModel(Model* model) override;

    int  getKey() override { 
        return -1;
    }

    GUIView(void) {}

    GUIView(int x, int y):
        View(x, y)
    {}
    
    ~GUIView()
    {}
};

#endif // GUIVIEW_H
