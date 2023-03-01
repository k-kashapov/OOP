#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include "view.h"

class TextView : public View {
public:
    TextView();

    TextView(int x, int y):
        View(x, y)
    {}

    ~TextView();

    void draw    (void)         override;
    void clear   (void)         override;
    int  WinXY   (void)         override;
    void setModel(Model* model) override;
    int  getKey  ()             override;
    
    void setCaret(int x, int y);
    void vline(int x, int y, int len);
    void hline(int x, int y, int len);

};

#endif // TEXTVIEW_H
