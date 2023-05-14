//
// Created by Rabadon on 12.03.2023.
//
#ifndef CLIONTEST_GAME_H
#define CLIONTEST_GAME_H

#include "Player.h"
#include "Meteor.h"
#include "Button.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <sstream>

enum Scenes{MAIN_MENU,LEVEL_1,PAUSE_MENU,NUMBEROFENUM};

class Game {
private:
    //Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;

    //Variables
    sf::Event ev;
    unsigned maxMeteors;
    unsigned numberOfMeteors;
    sf::Clock clock;
    float time;
    float spawnMeteorFrame;
    unsigned points;
    int CurrScene;
    sf::Vector2f mousePos;
    sf::Texture buttonTextures;
    float backGrndAnimationFrame;

    //Objects
    Player player;
    std::vector<Meteor> meteors;
    sf::RectangleShape star;
    std::vector<sf::RectangleShape> stars;
    std::vector<Button*> mainMenuButtons;
    sf::Texture mainMenuBackGrndTexture;
    sf::Sprite mainMenuBakcGrndSprite;

    //UI
    sf::RectangleShape maxHpBar;
    sf::RectangleShape hpCell;
    std::vector<sf::RectangleShape> currentHpBar;
    sf::Font font;
    sf::Text pointsText;

    //Functions
    void initWindow();
    void initVariables();
    void initStars();
    void setPlayerPosition();
    void initUi(sf::RenderTarget* target);
    void initHpBar(sf::RenderTarget* target);
    void initFont();
    void initUiText(sf::RenderTarget* target);
    void initButtons();
    void initBackGrnd();
public:
    //Creator/Destructor
    Game();
    ~Game();

    //Functions
    void poolEvent();
    bool running();
    void spawnMeteors(sf::RenderTarget* target);
    void moveMeteores();
    void destroyMeteores();

    //update
    void update();
    void updateStars();
    void updateTime();
    void updateCollision(sf::RenderTarget* target);
    void updateCollisionForMeteores(sf::RenderTarget* target);
    void updateHpBar(sf::RenderTarget* target);
    void updatePoints();
    void updateMeteores(sf::RenderTarget* target);
    void updateMousePos();
    void updateButtons();
    void updateButtonClick(sf::Event event);
    void updateBackGrnd();

    //render
    void render();
    void renderStars(sf::RenderTarget* target);
    void renderMeteors(sf::RenderTarget* target);
    void renderUi(sf::RenderTarget* target);
};


#endif //CLIONTEST_GAME_H
