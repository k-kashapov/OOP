#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <functional>
#include "view.h"

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

    void subTimer(const long interval, hndlr func) override;

private:
    void draw();
    void tickTimer();
};

#endif // TEXTVIEW_H
