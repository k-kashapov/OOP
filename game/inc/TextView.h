#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include "view.h"

class TextView : public View {
public:
    TextView(void);

    TextView(int x, int y):
        View(x, y)
    {}

    ~TextView()
    {}

    void draw(void);
    void clear(void);
    int  WinXY(void);
    void setCaret(int x, int y);
    void vline(int x, int y, int len);
    void hline(int x, int y, int len);
};

#endif // TEXTVIEW_H
