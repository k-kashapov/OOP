#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include "view.h"
#include "window.h"

class TextView : public View {
public:
    void   draw(void);
    pair_t WinXY(void);

    TextView(void) {}

    TextView(int x, int y):
        View(x, y)
    {}

    ~TextView()
    {}
};

#endif // TEXTVIEW_H
