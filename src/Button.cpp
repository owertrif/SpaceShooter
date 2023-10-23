//
// Created by Rabadon on 13.05.2023.
//

#include "Button.h"


//Constructor/Destructor
Button::Button(sf::IntRect rect, sf::Texture texture) {
    this->buttonTexture = texture;
    this->initSprite();
    this->buttonSprite.setTextureRect(rect);
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
    this->buttonSprite.setTextureRect(sf::IntRect(textureRect.x,textureRect.y, this->buttonSprite.getTextureRect().width, this->buttonSprite.getTextureRect().height));

}

void Button::setPosition(sf::Vector2f pos) {
    this->buttonSprite.setPosition(pos);
}

const sf::Sprite Button::getSprite() const {
    return this->buttonSprite;
}

void Button::setScale(sf::Vector2f scale) {
    this->buttonSprite.setScale(scale.x,scale.y);
}

const sf::IntRect Button::getRect() const {
    return this->defaultSpriteRect;
}

void Button::update(sf::Vector2f mousePos) {
    if (this->buttonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
        sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->setSpriteRect(sf::Vector2f(this->buttonSprite.getTextureRect().left + this->buttonSprite.getTextureRect().width,
                                         this->buttonSprite.getTextureRect().top));
    }
    if (this->buttonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
               !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->setSpriteRect(sf::Vector2f(this->buttonSprite.getTextureRect().left - this->buttonSprite.getTextureRect().width,
                                           this->buttonSprite.getTextureRect().top));
    }
    if(!this->buttonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
       !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->setSpriteRect(sf::Vector2f(this->getRect().left, this->getRect().top));
    }
}
