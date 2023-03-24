#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <functional>
#include "view.h"

enum COLOR {
    COLOR_BLCK = 0,
    COLOR_RED  = 1,
    COLOR_GREN = 2,
    COLOR_YELW = 3,
    COLOR_BLUE = 4,
    COLOR_MGNT = 5,
    COLOR_CYAN = 6,
    COLOR_WHIT = 7,
    COLORS_NUM
};

#define BRIGHT(color) (color + 60U)

class TextView : public View {
public:
    TextView();

    TextView(unsigned x, unsigned y):
        View(x, y)
    {}

    ~TextView();

    void loop    ()             override;
    void clear   ()             override;
    int  WinXY   ()             override;
    void setModel(Model* model) override;
    int  getKey  ()             override;
    
    void setColor (int fg, int bg);
    
    void setCaret (unsigned x,  unsigned y);
    void drawPixel(unsigned x,  unsigned y, int ch);
    
    void vline(unsigned x, unsigned y, unsigned len);
    void hline(unsigned x, unsigned y, unsigned len);

    void subTimer(const long interval, hndlr func) override;

private:
    void draw();
    void tickTimer();
};

#endif // TEXTVIEW_H
