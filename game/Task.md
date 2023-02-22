# Writing a game

`C++, MVC`

M triggers V\
O sees V\
O uses C\
C updates M

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
Has 2 views: text and graphics

```
main.cpp:
    View v();
    Model m();
    
    v.setmodel(m);
    
    if (argv[1] == ...) {
        v = Text;
    } else {
        v = GUI;
    }

    v->draw();

---------------------------------------------

view.h:
    class View {
        int _x, _y;
        
        View();
        
        ~View();
        
        void draw(void);

        void draw(Snake snk);
    }

---------------------------------------------

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

Abstract factory\
Singleton

```
View() { // abstract class
    virtual void draw(void) = 0; // virtual method
    // Vtable:
    //      TextView::draw || GUIView::draw
}

class TextView() : public View {
    void draw();
}

TextView()::draw() {
    ...
}

class GUIView() : View()

```
### Factory

```
class View {
    static View *get();
    static View *get(what);
    static View *obj;
}

static View *get(what) {
    switch what:
        case 1:  get("text");
        case 2:  get("gui");
        default: get();
}

```
## Sem 2

```
TUI:
    public:
        virtual draw();
        ... drawRabbit();
    private:
        rabbit_model;
```

```
           x --->
  /-------------------\
  |                   |
y |  ###              |
| |    #              |
| |    ####>    r     |
V |                   |
  |score:             |
  \-------------------/
```

1) WinSize
2) PutXY
3) hline, vline, line
4) cls

tty uses line discipline. We can ask it to get terminal width and height.

`ioctl (fd, cmd, param, ...)`

cmd = TIOCGWINSZ -> `struct WinSize { x, y }`;

add `WinSz()` to `View`.

#### SIGWINCH - signal that window size changed

CSI = Command Sequence Initiatior
`\e[13;5;1command`

```
cls:
    \e[H // Home
    \e[J // Clear
```

```
goto x,y:
    \e[yy;xxH
```

```
color (foreg, bkg):
    \e[ff;bbm    // ff: 30, 31...; bb: 40, 41, ...
    \e[aa;ff;bbm // attributes; foreground; background
```
## Sem 3

```
Model = DataBase {
    void Update(); // Called every ~ 1 second
}
```

```
main:
    model = Model();
    v->setModel(&model);
    v->draw();  // ==> model->Update()

view:
    setModel(Model *model);
    
    draw() {
        while(1) {
            model->Update();
            sleep(1);
        }
    }
```

#### Templates

```
template T;
T a[5];

class X;
X<int> Q; // no idea
```
#### Containers
```
C:
    int a[3]:
        a[x]
        *a
        a++
        a--

    struct a:
        a->x

STL: // standard template library
    vector // v[4]
    list   // l[4]
    map    // m["key"]
    set    // map but it says if present or not

namespace my_namespace {
    class a;
    class b;
}

std::vector aaa();

using namespace std;
```
