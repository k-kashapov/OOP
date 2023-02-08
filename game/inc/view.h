#ifndef VIEW_H
#define VIEW_H

class View {
public:
    int _x, _y;
    virtual void draw(void) = 0;
    
    View(int x, int y):
        _x(x), _y(y)
    {}

    static View *get(int x, int y, int what = 0);
    static View *_curr;

    virtual ~View()
    {}
};

class TextView : public View {
public:
    void draw(void);

    TextView(int x, int y):
        View(x, y)
    {}

    ~TextView()
    {}
};

class GUIView : public View {
public:
    void draw(void);

    GUIView(int x, int y):
        View(x, y)
    {}
    
    ~GUIView()
    {}
};

#endif // VIEW_H
