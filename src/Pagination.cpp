//
// Created by Rabadon on 28.05.2023.
//

#include "Pagination.h"

//Constructor/Destructor
Pagination::Pagination(sf::Texture tx, sf::IntRect TxTrect, sf::IntRect BTrect, sf::Font font) {
this->initButtons(tx, TxTrect, BTrect);
this->initText(font);
}

Pagination::~Pagination() {
    delete this->leftBt;
    delete this->rightBt;
    delete this->textBox;
    delete this->btTexture;
    delete this->optionTx;
}

//Private functions
void Pagination::initButtons(sf::Texture tx, sf::IntRect TxTrect, sf::IntRect LBTrect) {
    this->textBox = new sf::Sprite;
    this->btTexture = new sf::Texture(tx);
    this->textBox->setTexture(*this->btTexture);
    this->textBox->setTextureRect(TxTrect);
    this->leftBt = new Button(LBTrect,*this->btTexture);
    this->rightBt = new Button(sf::IntRect(LBTrect.left,LBTrect.top+LBTrect.width,LBTrect.width,LBTrect.height),*this->btTexture);
    this->leftBt->setScale(sf::Vector2f (3.f,3.f));
    this->rightBt->setScale(sf::Vector2f (3.f,3.f));
    this->textBox->setScale(sf::Vector2f (3.f,3.f));
}

void Pagination::initText(sf::Font font) {
    this->optionTx = new sf::Text;
    this->font = font;
    this->optionTx->setFont(this->font);
    this->optionTx->setCharacterSize(24);
    this->optionTx->setPosition(this->textBox->getGlobalBounds().left + this->textBox->getGlobalBounds().width/2.f - this->optionTx->getGlobalBounds().width/2.f,
                                this->textBox->getGlobalBounds().top + this->textBox->getGlobalBounds().height/2.f - this->optionTx->getGlobalBounds().height/2.f);
    this->optionTx->setString("NONE");
}

//Public Functions
void Pagination::setPosition(sf::Vector2f pos) {
    this->textBox->setPosition(pos);
    this->leftBt->setPosition(sf::Vector2f(pos.x - this->leftBt->getSprite().getGlobalBounds().width - 5, pos.y));
    this->rightBt->setPosition(sf::Vector2f(pos.x + this->textBox->getGlobalBounds().width + 5, pos.y));
}

void Pagination::render(sf::RenderTarget *target) {
    this->leftBt->render(target);
    this->rightBt->render(target);
    target->draw(*this->textBox);
}

void Pagination::update(sf::Vector2f mousePos) {
    this->rightBt->update(mousePos);
    this->leftBt->update(mousePos);
}

const sf::Sprite Pagination::getSprite() const {
    return *this->textBox;
}






