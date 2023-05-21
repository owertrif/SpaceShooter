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
    this->speed = (static_cast<float>(rand()%13) + 2.f)/10;
    this->rotateSpeed = (static_cast<float>(rand()%13) + 2.f)/10;
    this->type = DEFAULT;
    this->points = 1;
}

void Meteor::initSprite() {
    this->meteorTexture.loadFromFile("./textures/Entity.png");
    this->meteorSprite.setTexture(this->meteorTexture);
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
            this->meteorSprite.setTextureRect(sf::IntRect(0,0,32,32));
            this->maxHp = 2;
            this->Hp = this->maxHp;
            this->damage = 1;
            this->points = 1;
            break;
        case GIANT:
            this->meteorSprite.setTextureRect(sf::IntRect(0,0,32,32));
            this->meteorSprite.setScale(2,2);
            this->maxHp = 5;
            this->Hp = this->maxHp;
            this->damage = 5;
            this->points = 3;
            break;
        case HEALING:
            this->meteorSprite.setTextureRect(sf::IntRect(32,0,32,32));
            this->maxHp = 4;
            this->Hp = this->maxHp;
            this->damage = 3;
            this->points = 2;
            break;
        case RICH:
            this->meteorSprite.setTextureRect(sf::IntRect(64,0,32,32));
            this->maxHp = 5;
            this->Hp = this->maxHp;
            this->damage = 4;
            this->points = 5;
            break;
    }
}

void Meteor::update() {
    this->rotate();
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

const sf::Sprite &Meteor::getShape()const {
    return this->meteorSprite;
}

const unsigned &Meteor::getPoints() const {
    return this->points;
}

void Meteor::rotate() {
    this->meteorSprite.setRotation(this->meteorSprite.getRotation() + this->rotateSpeed);
}

