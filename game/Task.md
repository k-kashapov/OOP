# Writing a game

`C++, MVC`

M triggers V\
O sees V\
O uses C\
C updates M\

<img src="https://raw.githubusercontent.com/Codecademy/articles/0b631b51723fbb3cc652ef5f009082aa71916e63/images/mvc_process.svg">

```
Model {
    // Everything not needed on screen
    _x;
    _y;
    _list;
}

View {
    // Visualizes model
}

Controller {
    // Gets input from operator
}
```

Game - snake.\
Snake! Respond! Snaaaake!\
Has 2 views: text and graphics\

```
main.cpp:
    View v();
    Model m();
    v.setmodel(m);

view.h:
    class View {
        int _x, _y;
        
        View();
        
        ~View();
        
        void draw();
    }

view.cpp:
    #include "view.h"

    void View::View(int x, int y):
        _x(x), _y(y) {
        _x = _y = 0;
    }

    void View::~View() {

    }

    void View::draw() {
        ...
    }
```
