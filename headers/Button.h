//
// Created by Rabadon on 13.05.2023.
//

#ifndef CLIONTEST_BUTTON_H
#define CLIONTEST_BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

class Button {
private:
    //Sprite
    sf::Texture buttonTexture;
    sf::Sprite buttonSprite;
    sf::IntRect defaultSpriteRect;
    //Functions
    void initSprite();
public:
    //Constructor/Destructor
    Button(sf::IntRect rect, sf::Texture texture);
    virtual ~Button();

    void update(sf::Vector2f mousePos);

    //Render
    void render(sf::RenderTarget* target);


    void setSpriteRect(sf::Vector2f textureRect);
    void setPosition(sf::Vector2f pos);
    void setScale(sf::Vector2f scale);

    const sf::Sprite getSprite()const;
    const sf::IntRect getRect()const;
};


#endif //CLIONTEST_BUTTON_H
