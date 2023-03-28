#ifndef GUIVIEW_H
#define GUIVIEW_H

#include "view.h"
#include <SFML/Graphics.hpp>

class GUIView final : public View {
public:
    void loop    (void)         override;
    void clear   (void)         override;
    int  WinXY   (void)         override;
    void setModel(Model* model) override;

    int  getKey() override { 
        return -1;
    }

    GUIView(unsigned x, unsigned y);
    
    ~GUIView()
    {}

    void subTimer(const long interval, hndlr func) override;

private:
    void draw(sf::Sprite& bun, sf::Sprite& snk);

    sf::Texture      bunnyTex;
    sf::Texture      snakeTex;
    sf::RenderWindow window;
};

#endif // GUIVIEW_H
