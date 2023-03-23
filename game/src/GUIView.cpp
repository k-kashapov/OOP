#include <iostream>
#include "GUIView.h"

GUIView::GUIView(unsigned x, unsigned y): View(x, y), window(sf::VideoMode(_x, _y), "Snaaaaake") {
    window.setFramerateLimit(2);

    bunnyTex.loadFromFile("sprites/bunny.png");
    bunnyTex.setSmooth(false);

    snakeTex.loadFromFile("sprites/snake.png");
    snakeTex.setSmooth(false);
}

int GUIView::WinXY(void) {
    _x = _y = 200;
    return 0;
}

void GUIView::setModel(Model *model) {
    std::cout << "GUIView(" << _x << ", " << _y << ") set Model called\n";
    _model = model;
}

void GUIView::draw(sf::Sprite& bun, sf::Sprite& snk) {
    std::cout << "GUIView(" << _x << ", " << _y << ") draw called\n";
    _model->Update();

    clear();

    for (coord &curr : _model->rabbits) {
        bun.setPosition((float) (curr.first * 20), (float) (curr.second * 20));
        window.draw(bun);
    }

    for (coord &curr : _model->snake.body) {
        snk.setPosition((float) (curr.first * 20), (float) (curr.second * 20));
        window.draw(snk);
    }

    window.display();
}

void GUIView::loop(void) {
    std::cout << "GUIView(" << _x << ", " << _y << ") loop called\n";

    sf::Sprite bun;
    sf::Sprite snk;

    bun.setTextureRect(sf::Rect<int>(29, 52, 19, 26));
    bun.setTexture(bunnyTex);
    bun.setScale(1, 1);

    snk.setTextureRect(sf::Rect<int>(124, 41, 33, 37));
    snk.setTexture(snakeTex);
    snk.setScale(1, 1);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        draw(bun, snk);
    }
}

void GUIView::subTimer(const long interval, hndlr func) {
    (void) interval;
    (void) func;
    std::cout << "GUIView(" << _x << ", " << _y << ") clear called\n";
}

inline void GUIView::clear(void) {
    window.clear(sf::Color::Cyan);
}
