#include "player.h"

player :: player(Texture& texture, FloatRect rectangle)
{
    dx = 0;
    dy = 0;
    CurrentFrame = 0;
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, 94, 138));
    rect = rectangle;
}

void player :: update(float time, int ofsetX, int ofsetY)
{
    rect.left += dx * time;
    rect.top += dy * time;

    if ((dx == 0) && (dy == 0))
    {
        CurrentFrame += time * 0.001;
        if (CurrentFrame > 4)
            CurrentFrame = 0;
        sprite.setTextureRect(IntRect((int)CurrentFrame * 95, 0, 94, 138));
    }

    sprite.setPosition(rect.left - ofsetX, rect.top - ofsetY);
    dx = 0;
    dy = 0;
}