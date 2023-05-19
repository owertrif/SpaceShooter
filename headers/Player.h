//
// Created by Rabadon on 12.03.2023.
//

#ifndef CLIONTEST_PLAYER_H
#define CLIONTEST_PLAYER_H

#include "Bomb.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <iostream>

class Player {
private:
    //Variables
    float speed;
    std::vector<Bomb> magazine;
    unsigned Hp;
    unsigned maxHp;
    bool isDead;

    //Clock
    sf::Clock clock;
    float time;
    float spriteFrame;
    float shootFrame;

    //Texture
    sf::Texture playerTexture;
    sf::Sprite  playerSprite;

    //Functions
    void initVariables();
    void initSprite();
public:
    //Constructor/Destructor
    Player(float x = 10.f,float y = 10.f);
    virtual ~Player();

    //Accessors
    const sf::Sprite& getSprite() const;
    void setPos(float x, float y);
    void setHp(int Hp);
    void setCondition(bool condition);
    void deleteBomb(int i);
    const unsigned& getHp()const;
    const unsigned& getMaxHp()const;
    const bool& getCondition()const;
    const Bomb& getBomb(int i);
    const std::vector<Bomb>& getMagazine();

    //Functions
    void shootBomb();
    void damaging(int damage);
    void heal(int heal);

    //Update
    void update(sf::RenderTarget* target);
    void updatePosition();
    void updateWindowBounds(sf::RenderTarget* target);
    void updateTime();
    void updateSprite();
    void updateCondition();

    //Render
    void render(sf::RenderTarget* target);
};


#endif //CLIONTEST_PLAYER_H
