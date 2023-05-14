//
// Created by Rabadon on 12.03.2023.
//

#ifndef CLIONTEST_BOMB_H
#define CLIONTEST_BOMB_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include <iostream>

class Bomb {
private:
//Variables
float speed;
unsigned damage;

//Textures
sf::CircleShape bombSprite;

//Functions
void initVariables();
void initSprite();

public:
    //Constructor/Destructor
    Bomb(sf::Vector2f pos);
    virtual ~Bomb();

    //Accessors
    const sf::CircleShape& getSprite() const;
    const float& getSpeed()const;
    const unsigned& getDamage()const;
    void setPos(float x,float y);

    //update
    void update(sf::RenderTarget* target);

    //render
    void render(sf::RenderTarget* target);

};


#endif //CLIONTEST_BOMB_H
