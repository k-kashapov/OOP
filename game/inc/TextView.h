#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <functional>
#include "view.h"

#define COLOR_BLCK 0
#define COLOR_RED  1
#define COLOR_GREN 2
#define COLOR_YELW 3
#define COLOR_BLUE 4
#define COLOR_MGNT 5
#define COLOR_CYAN 6
#define COLOR_WHIT 7
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
