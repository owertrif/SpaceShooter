//
// Created by Rabadon on 28.05.2023.
//

#ifndef CLIONTEST_PAGINATION_H
#define CLIONTEST_PAGINATION_H
#include "Button.h"



class Pagination {
private:
    //Objects
    Button* leftBt;
    Button* rightBt;
    sf::Texture* btTexture;
    sf::Sprite* textBox;
    std::vector<std::string> options;
    sf::Font font;
    sf::Text* optionTx;
    

    //Functions
    void initButtons(sf::Texture tx,sf::IntRect TxTrect, sf::IntRect BTrect);
    void initText(sf::Font font);
public:
    //Constructor/Destructor
    Pagination(sf::Texture tx,sf::IntRect TxTrect, sf::IntRect BTrect, sf::Font font);
    virtual ~Pagination();

    const sf::Sprite getSprite() const;

    void setPosition(sf::Vector2f pos);

    void render(sf::RenderTarget* target);

    void update(sf::Vector2f mousePos);
};


#endif //CLIONTEST_PAGINATION_H
