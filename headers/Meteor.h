//
// Created by Rabadon on 13.03.2023.
//

#ifndef CLIONTEST_METEOR_H
#define CLIONTEST_METEOR_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

enum SELECT_TYPE{DEFAULT = 0, GIANT, HEALING, RICH, NROFTYPES};

class Meteor {
private:
    //Variables
    unsigned Hp;
    unsigned maxHp;
    unsigned damage;
    float speed;
    unsigned type;
    unsigned points;
    float rotateSpeed;

    //Textures
    sf::Texture meteorTexture;
    sf::Sprite meteorSprite;

    //Functions
    void initVariables();
    void initSprite();
public:
    //Constructor/Destrustor
    Meteor(sf::RenderTarget* target);
    virtual ~Meteor();

    //Accessors
    const sf::Sprite& getShape()const;
    void setPosition(float x,float y);
    const float getSpeed()const;
    void setHp(int Hp);
    void setMaxHp(int maxHp);
    void setDamage(int damage);
    const unsigned& getHp()const;
    const unsigned& getMaxHp()const;
    const unsigned& getDamage()const;
    const unsigned& getType()const;
    const unsigned& getPoints()const;

    //update
    void update();
    void rotate();
    //render

    void render(sf::RenderTarget* target);
};


#endif //CLIONTEST_METEOR_H
