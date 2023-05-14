//
// Created by Rabadon on 13.05.2023.
//

#include "Button.h"

//Constructor/Destructor
Button::Button(sf::Vector2f rect, sf::Texture texture) {
    this->buttonTexture = texture;
    this->initSprite();
    this->buttonSprite.setTextureRect(sf::IntRect(rect.x,rect.y, 48.f, 16.f));
    this->defaultSpriteRect =  sf::IntRect(this->buttonSprite.getTextureRect());
}

Button::~Button() {
}

//Private functions
void Button::initSprite() {
    this->buttonSprite.setTexture(this->buttonTexture);
}


//Public functions

//Render
void Button::render(sf::RenderTarget *target) {
    target->draw(this->buttonSprite);
}


void Button::setSpriteRect(sf::Vector2f textureRect) {
    if( this->buttonSprite.getTextureRect().left - textureRect.x <= this->defaultSpriteRect.left - textureRect.x
    && this->buttonSprite.getTextureRect().left + textureRect.x >= this->defaultSpriteRect.left + textureRect.x
    || this->defaultSpriteRect.left == textureRect.x)
    this->buttonSprite.setTextureRect(sf::IntRect(textureRect.x,textureRect.y, 48.f, 16.f));
}

void Button::setPosition(sf::Vector2f pos) {
    this->buttonSprite.setPosition(pos);
}

const sf::Sprite Button::getSprite() const {
    return this->buttonSprite;
}

void Button::setScale(float scale) {
    this->buttonSprite.setScale(scale,scale);
}

const sf::IntRect Button::getRect() const {
    return this->defaultSpriteRect;
}
