#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include "player.h"
#include "Block.h"
#include "Map.h"

#pragma warning(disable : 4996)

#define speed 0.95
#define Speed_Animation 0.007 //  Чем меньше число тем больше время между кадрами

float** Create_matrix(int height, int width);

using namespace sf;
using namespace std;

const int Y_map = 1000;
const int X_map = 1000;

float ofsetX = 0;
float ofsetY = 0;

int main(void)
{
    srand(time(0));
    int octaves = 1;
    Perlin2D* noise = new Perlin2D(octaves);
    //noise->get();

    Block water = set_block(1, 0);
    water.texture.loadFromFile("img/ground.png");
    water.sprite.setTexture(water.texture);
    water.sprite.setTextureRect(IntRect(0, 0, 32, 32));
    //Block ground1 = set_block(0, 10, 30, 0);
    //Block road1 = set_block(1, 1, 1, 0);
    //road1.texture.loadFromFile("img/road_1.png");
    //road1.sprite.setTexture(road1.texture);
    
    Map save;
    //save.save_block_in_file(ground1);

    float** map = Create_matrix(X_map, Y_map);
    for (int i = 0; i < X_map; i++)
    {
        for (int j = 0; j < Y_map; j++)
        {
            *(*(map + i) + j) = noise->get(i, j);// 0 - это блок земли на карте
            //if (*(*(map + i) + j) < -0.5)
            //cout << *(*(map + i) + j) << "\n";
        }
    }

    Vector2f resol;
    resol.x = VideoMode::getDesktopMode().width;
    resol.y = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(resol.x, resol.y), "Nya", Style::Fullscreen);
    window.setVerticalSyncEnabled(1);
    window.setFramerateLimit(60);


    Vector2f pers_pos;
    Image pers, ground;
    Texture pers_t, ground_t;
    //Sprite pers_s;

    Clock clk;

    Font font;
    Text text;
    font.loadFromFile("f.ttf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setColor(Color::Green);
    
    pers.loadFromFile("img/Archer_pers.png");
    ground.loadFromFile("img/ground.png");

    pers_t.loadFromImage(pers);
    ground_t.loadFromImage(ground);

    player archer (pers_t, FloatRect(100, 100, 94, 138));

    Sprite ground_s(ground_t);
    ground_s.setTextureRect(IntRect(32, 32, 32, 32));
    //ground_s.setScale(2.0f, 2.0f);
    float CurrentFrame = 0;

    uint8_t count = 0;

    while (window.isOpen())
    { 

        float time = clk.getElapsedTime().asMicroseconds();
        float framerate = 1000000 / clk.getElapsedTime().asMicroseconds();
        clk.restart();
        time /= 800;

        if (count == 10)
        { 
        ostringstream fps;
        //cout << framerate << "\n";
        fps << framerate;
        text.setString(fps.str());
        text.setPosition(10, 0);
        count = 0;
        }
        else
        count++;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }    

        if (Keyboard::isKeyPressed(Keyboard::D)) 
            { 
                archer.dx = speed;

                CurrentFrame -= time * Speed_Animation;
                if (CurrentFrame < -0.25)
                    CurrentFrame += 4;
                archer.sprite.setTextureRect(IntRect(((int)CurrentFrame + 1) * 95, 138, -94, 138));
            }
        
        if (Keyboard::isKeyPressed(Keyboard::A))
            {
            archer.dx = -speed;
                CurrentFrame -= time * Speed_Animation;
                if (CurrentFrame < -0.25)
                    CurrentFrame = 4;
                archer.sprite.setTextureRect(IntRect((int)CurrentFrame * 95, 138, 94, 138));
            }
        
        if (Keyboard::isKeyPressed(Keyboard::W)) 
            {
                archer.dy = -speed;
            }
        
        if (Keyboard::isKeyPressed(Keyboard::S))
            {
                archer.dy = speed;
            }
        
        if (Keyboard::isKeyPressed(Keyboard::Escape))       // Выход из приложения
            {
                window.close();
            }   
       
        ofsetX = archer.rect.left - (resol.x / 2);      // Движение камеры по Х
        ofsetY = archer.rect.top - (resol.y / 2);       // Движение камеры по У

        archer.update(time, ofsetX, ofsetY);
        window.clear();
        
        for (int i = 0; i < X_map; i++)
        {
            for (int j = 0; j < Y_map; j++)
            {
                
                if (((i * 32 - ofsetX) > -resol.x) && ((i * 32 - ofsetX) < resol.x) && ((j * 32 - ofsetY) > -resol.y) && ((j * 32 - ofsetY) < resol.y))
                if (*(*(map + i) + j) < -0.28 ||(*(*(map + i) + j) > 0.15 && *(*(map + i) + j) < 0.25) )
                {
                    water.sprite.setPosition(i * 32 - ofsetX, j * 32 - ofsetY);

                    window.draw(water.sprite);
                }
                else
                if (*(*(map + i) + j) < 0.15)
                {
                    ground_s.setPosition(i * 32 - ofsetX, j * 32 - ofsetY);

                    window.draw(ground_s);
                }
                
            }
        }
        window.draw(text);
        window.draw(archer.sprite);
        window.display();
    }
    delete noise;
    return 0;
}

float** Create_matrix(int height, int width)
{
    float** matrix = (float**)malloc(sizeof(float*) * height);
    for (int i = 0; i < height; i++)
    {
        *(matrix + i) = (float*)malloc(sizeof(float) * width);
    }
    return matrix;
}