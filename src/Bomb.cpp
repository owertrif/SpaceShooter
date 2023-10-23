//
// Created by Rabadon on 12.03.2023.
//

#include "Bomb.h"

//constructor/Destructor
Bomb::Bomb(sf::Vector2f pos) {
    this->initVariables();
    this->initSprite();
    this->bombSprite.setPosition(pos);
}

Bomb::~Bomb() {

}

//Private functions
void Bomb::initVariables() {
    this->speed = 8.f;
    this->damage = 1;
}

void Bomb::initSprite() {
   this->bombSprite.setFillColor(sf::Color::Red);
   this->bombSprite.setRadius(4.f);
   this->bombSprite.setOutlineColor(sf::Color::Magenta);
   this->bombSprite.setOutlineThickness(2.f);
}

//Update
void Bomb::update(sf::RenderTarget* target) {

}

//Render
void Bomb::render(sf::RenderTarget *target) {
    target->draw(this->bombSprite);
}

//Accessors
const sf::CircleShape& Bomb::getSprite()const {
    return this->bombSprite;
}

const float& Bomb::getSpeed() const {
    return speed;
}

void Bomb::setPos(float x, float y) {
    this->bombSprite.setPosition(x,y);
}

const unsigned &Bomb::getDamage() const {
    return this->damage;
}


