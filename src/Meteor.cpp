//
// Created by Rabadon on 13.03.2023.
//

#include "Meteor.h"

//Constructor/Destrustor

Meteor::Meteor(sf::RenderTarget* target) {
    this->initVariables();
    this->initSprite();
    this->meteorSprite.setPosition(rand()%target->getSize().x,-150.f);
}

Meteor::~Meteor() {

}

//Private functions
void Meteor::initVariables() {
    this->maxHp = 2;
    this->Hp = this->maxHp;
    this->damage = 1;
    this->speed = 1.5f;
    this->type = DEFAULT;
    this->points = 1;
}

void Meteor::initSprite() {
    int rnd = rand()%101;

    if(rnd > 50 && rnd <= 80)
        this->type = GIANT;
    else if(rnd > 80 && rnd <= 90)
        this->type = HEALING;
    else if(rnd > 90 && rnd <= 100)
        this->type = RICH;
    else
        this->type = DEFAULT;

    switch(this->type)
    {
        case DEFAULT:
            this->meteorSprite.setFillColor(sf::Color(122, 122, 122));
            this->meteorSprite.setRadius(15.f);
            this->meteorSprite.setOutlineColor(sf::Color(51, 51, 51));
            this->meteorSprite.setOutlineThickness(5.f);
            this->maxHp = 2;
            this->Hp = this->maxHp;
            this->damage = 1;
            this->points = 1;
            break;
        case GIANT:
            this->meteorSprite.setFillColor(sf::Color(122, 122, 122));
            this->meteorSprite.setRadius(30.f);
            this->meteorSprite.setOutlineColor(sf::Color(51, 51, 51));
            this->meteorSprite.setOutlineThickness(10.f);
            this->maxHp = 5;
            this->Hp = this->maxHp;
            this->damage = 3;
            this->points = 3;
            break;
        case HEALING:
            this->meteorSprite.setFillColor(sf::Color(122, 122, 122));
            this->meteorSprite.setRadius(15.f);
            this->meteorSprite.setOutlineColor(sf::Color::Green);
            this->meteorSprite.setOutlineThickness(5.f);
            this->maxHp = 4;
            this->Hp = this->maxHp;
            this->damage = 2;
            this->points = 2;
            break;
        case RICH:
            this->meteorSprite.setFillColor(sf::Color(122, 122, 122));
            this->meteorSprite.setRadius(15.f);
            this->meteorSprite.setOutlineColor(sf::Color::Yellow);
            this->meteorSprite.setOutlineThickness(5.f);
            this->maxHp = 5;
            this->Hp = this->maxHp;
            this->damage = 2;
            this->points = 5;
            break;
    }
}

void Meteor::update() {

}

void Meteor::render(sf::RenderTarget *target) {
    target->draw(this->meteorSprite);
}

//Accessors
void Meteor::setPosition(float x,float y) {
    this->meteorSprite.setPosition(x,y);
}

void Meteor::setHp(int Hp) {
    this->Hp = Hp;
}

void Meteor::setMaxHp(int maxHp) {
    this->maxHp = maxHp;
}

void Meteor::setDamage(int damage) {
    this->damage = damage;
}

const unsigned& Meteor::getHp() const {
    return this->Hp;
}

const unsigned& Meteor::getMaxHp()const {
    return this->maxHp;
}

const unsigned &Meteor::getDamage() const {
    return this->damage;
}

const unsigned &Meteor::getType() const {
    return this->type;
}

const float Meteor::getSpeed() const {
    return this->speed;
}

const sf::CircleShape &Meteor::getShape()const {
    return this->meteorSprite;
}

const unsigned &Meteor::getPoints() const {
    return this->points;
}

