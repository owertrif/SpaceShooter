//
// Created by Rabadon on 12.03.2023.
//

#include "Player.h"

//Constructor/Destructor
Player::Player(float x, float y) {
    this->initSprite();
    this->initVariables();
    this->setPos(x,y);
}

Player::~Player()
{
    this->magazine.clear();
}

//Private functions
void Player::initVariables() {
    this->speed = 5.f;
    this->time = 0.f;
    this->shootFrame = 1.f;
    this->maxHp = 10;
    this->Hp = this->maxHp;
    this->isDead = false;
}

void Player::initSprite() {
    /*
     -Loading texture from file.
     -Setting texture to a sprite.
     */
    this->playerTexture.loadFromFile("./textures/playerTileset.png");
    this->playerSprite.setTexture(this->playerTexture);
    this->playerSprite.setTextureRect(sf::IntRect (0.f,0.f,64.f,64.f));
}

//Public functions

void Player::shootBomb() {
    //Shoot the projectile
    if(this->shootFrame >= 0.25) this->shootFrame = 0.25f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if(this->shootFrame >= 0.25f) {
                this->shootFrame = 0;
                Bomb bomb(sf::Vector2f (this->playerSprite.getPosition().x + this->playerSprite.getGlobalBounds().width/2 - 8.f,
                                        this->playerSprite.getPosition().y));
                this->magazine.push_back(bomb);
            }
    }
    //Move projectile
    if(this->magazine.size() != 0) {
        for (int i = 0; i < magazine.size(); i++) {
            this->magazine[i].setPos(this->magazine[i].getSprite().getPosition().x,
                                     this->magazine[i].getSprite().getPosition().y-this->magazine[i].getSpeed());
            if (this->magazine[i].getSprite().getGlobalBounds().top <= 0.f)
                this->magazine.erase(this->magazine.begin() + i);
        }
    }
}

void Player::damaging(int damage) {
    this->Hp -= damage;
    if(this->Hp < 0) this->Hp =0;
}

void Player::heal(int heal) {
   this->Hp+=heal;
    if(this->Hp > this->maxHp) this->Hp = this->maxHp;
}

//Update
void Player::update(sf::RenderTarget* target) {
    this->updatePosition();
    this->updateWindowBounds(target);
    this->updateTime();
    this->updateSprite();
    this->shootBomb();
    this->updateCondition();
}

void Player::updatePosition()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->playerSprite.move(this->speed,0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->playerSprite.move(-this->speed,0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->playerSprite.move(0.f,-this->speed);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->playerSprite.move(0.f,this->speed);
}

void Player::updateTime() {
    this->time = this->clock.getElapsedTime().asSeconds();
    this->clock.restart();
    this->spriteFrame += time;
    this->shootFrame += time;
}

void Player::updateSprite() {
    if(this->spriteFrame > 1.5) this->spriteFrame = 0;
    this->playerSprite.setTextureRect(sf::IntRect(0.f + static_cast<unsigned>(this->spriteFrame*2)*64,
                                                  0.0f,64.f,64.f));
}

void Player::updateWindowBounds(sf::RenderTarget* target) {
    //Left
    if (this->playerSprite.getGlobalBounds().left <= 0.f)
        this->playerSprite.setPosition(0.f, this->playerSprite.getGlobalBounds().top);
    //Right
    if (this->playerSprite.getGlobalBounds().left + this->playerSprite.getGlobalBounds().width >= target->getSize().x)
        this->playerSprite.setPosition(target->getSize().x - this->playerSprite.getGlobalBounds().width,
                                       this->playerSprite.getGlobalBounds().top);
    //Top
    if (this->playerSprite.getGlobalBounds().top <= 0.f)
        this->playerSprite.setPosition(this->playerSprite.getGlobalBounds().left, 0.f);
    //Bottom
    if (this->playerSprite.getGlobalBounds().top + this->playerSprite.getGlobalBounds().height >= target->getSize().y)
        this->playerSprite.setPosition(this->playerSprite.getGlobalBounds().left,
                                       target->getSize().y - this->playerSprite.getGlobalBounds().height);

}

void Player::updateCondition() {
    if(this->Hp == 0 )
    {
        this->isDead = true;
    }
}

//Render
void Player::render(sf::RenderTarget* target) {
    //rendering player sprite
    if(this->magazine.size() != 0) {
        for (auto bmb: this->magazine)
            bmb.render(target);
    }
    target->draw(this->playerSprite);
}

//Accessors
void Player::setPos(float x, float y) {
    //Setting player position
    this->playerSprite.setPosition(x,y);
}

const sf::Sprite& Player::getSprite() const {
    //Getting player sprite
    return this->playerSprite;
}

void Player::setHp(int Hp) {
    this->Hp = Hp;
}

const unsigned& Player::getHp()const {
    return this->Hp;
}

const unsigned& Player::getMaxHp()const {
    return this->maxHp;
}

const bool &Player::getCondition() const {
    return this->isDead;
}

void Player::deleteBomb(int i) {
    this->magazine.erase(this->magazine.begin()+i);
}

const Bomb &Player::getBomb(int i) {
    return this->magazine[i];
}

const std::vector<Bomb> &Player::getMagazine() {
    return this->magazine;
}

void Player::setCondition(bool condition) {
    this->isDead = condition;
}






















