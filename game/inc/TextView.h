#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include "view.h"
#include <functional>

class TextView : public View {
public:
    TextView();

    TextView(int x, int y):
        View(x, y)
    {}

    ~TextView();

    void loop    ()             override;
    void clear   ()             override;
    int  WinXY   ()             override;
    void setModel(Model* model) override;
    int  getKey  ()             override;
    
    void setCaret (int x, int y);
    void drawPixel(int x, int y, int ch);
    
    void vline(int x, int y, int len);
    void hline(int x, int y, int len);

    void subTimer(const unsigned interval, hndlr func);

private:
    void draw();

    std::list<std::pair<const unsigned, hndlr>> timer_subs;
    std::list<unsigned>                         timer_vals;

    void tickTimer();
};

#endif // TEXTVIEW_H
