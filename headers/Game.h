//
// Created by Rabadon on 12.03.2023.
//
#ifndef CLIONTEST_GAME_H
#define CLIONTEST_GAME_H

#include "Player.h"
#include "Meteor.h"
#include "Button.h"
#include "Pagination.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <sstream>
#include <fstream>

enum Scenes{MAIN_MENU,LEVEL_1,PAUSE_MENU,END_GAME_MENU,OPTIONS,NUMBEROFENUM};

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
    sf::Vector2f startPlayerPos;
    std::string highScore;
    std::fstream HighScore;

    //Objects
    Player player;
    std::vector<Meteor*> meteors;
    sf::RectangleShape star;
    std::vector<sf::RectangleShape> stars;
    std::vector<Button*> mainMenuButtons;
    std::vector<Button*> pauseMenuButtons;
    std::vector<Button*> endGameMenuButtons;
    std::vector<Button*> optionsMenuButtons;
    std::vector<Pagination*> optionsMenuPaginations;
    sf::Texture mainMenuBackGrndTexture;
    sf::Sprite mainMenuBakcGrndSprite;

    //UI
    sf::RectangleShape maxHpBar;
    sf::RectangleShape hpCell;
    std::vector<sf::RectangleShape> currentHpBar;
    sf::Font font;
    sf::Text pointsText;
    sf::Text highScoreText;

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
    void initFiles();
    void initMainMenuBt();
    void initPauseMenuBt();
    void initEndGameMenuBt();
    void initOptionsMenuBt();
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
    void resetLevelOne();

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
    void updateHighScore();

    //render
    void render();
    void renderStars(sf::RenderTarget* target);
    void renderMeteors(sf::RenderTarget* target);
    void renderUi(sf::RenderTarget* target);
};


#endif //CLIONTEST_GAME_H
