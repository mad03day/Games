#pragma once
#include <SFML/Graphics.hpp>

#define player_h
#ifdef player_h

using namespace sf;

class player {
public:

    float dx, dy, CurrentFrame;
    Sprite sprite;
    FloatRect rect;

    player(Texture& texture, FloatRect rectangle);
    void update(float time, int ofsetX, int ofsetY);
    
};


#endif