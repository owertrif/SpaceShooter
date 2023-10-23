//
// Created by Rabadon on 12.03.2023.
//

#include "Game.h"

//Creator/Destructor
Game::Game() {
    this->initWindow();
    this->initVariables();
    this->setPlayerPosition();
    this->initStars();
    this->initFont();
    this->initUi(this->window);
    this->initMainMenuBt();
    this->initPauseMenuBt();
    this->initEndGameMenuBt();
    this->initOptionsMenuBt();
    this->initBackGrnd();
    this->initFiles();
}

Game::~Game() {
    for(auto mt : this->meteors)
    {
        delete mt;
    }
    this->stars.clear();
    delete this->window;
    for(int i = 0; i< this->mainMenuButtons.size();i++)
    {
        delete this->mainMenuButtons[i];
    }
    for(int i = 0; i< this->pauseMenuButtons.size();i++)
    {
        delete this->pauseMenuButtons[i];
    }
    for(int i = 0; i< this->endGameMenuButtons.size();i++)
    {
        delete this->endGameMenuButtons[i];
    }
    for(int i = 0; i< this->optionsMenuButtons.size();i++)
    {
        delete this->optionsMenuButtons[i];
    }
    for(int i = 0; i< this->optionsMenuPaginations.size();i++)
    {
        delete this->optionsMenuPaginations[i];
    }
}

//Private functions
void Game::initWindow() {
    this->videoMode = sf::VideoMode(960.f,640.f);
    this->window = new sf::RenderWindow(videoMode,"Test", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initVariables() {
    this->maxMeteors = 55;
    this->numberOfMeteors = 0;
    this->points = 0;
    this->CurrScene = MAIN_MENU;
    this->backGrndAnimationFrame = 0;
}

void Game::initStars() {
    this->star.setFillColor(sf::Color::White);
    this->star.setSize(sf::Vector2f (2.f,2.f));
    for(int i{0}; i < 100; i++)
    {
        this->star.setPosition(rand()%this->window->getSize().x,rand()%this->window->getSize().y);
        this->stars.push_back(this->star);
    }
}

void Game::setPlayerPosition() {
    this->player.setPos(this->window->getSize().x/2 - this->player.getSprite().getGlobalBounds().width/2,
                        this->window->getSize().y - this->player.getSprite().getGlobalBounds().height - 10.f
    );
    this->startPlayerPos = this->player.getSprite().getPosition();
}

void Game::initUi(sf::RenderTarget* target) {
    this->initHpBar(target);
    this->initUiText(target);
}

void Game::initHpBar(sf::RenderTarget* target) {
    this->maxHpBar.setSize(sf::Vector2f (this->player.getMaxHp()*20,50));
    this->maxHpBar.setOutlineThickness(3.f);
    this->maxHpBar.setOutlineColor(sf::Color::White);
    this->maxHpBar.setFillColor(sf::Color::Transparent);
    this->maxHpBar.setPosition(target->getSize().x - this->maxHpBar.getGlobalBounds().width,3.f);

    this->hpCell.setSize(sf::Vector2f (16,46));
    this->hpCell.setFillColor(sf::Color::Cyan);
    this->hpCell.setOutlineThickness(2.f);
    this->hpCell.setOutlineColor(sf::Color::Black);
}

void Game::initUiText(sf::RenderTarget* target) {
    this->pointsText.setFont(this->font);
    this->pointsText.setCharacterSize(24);
    this->pointsText.setPosition(0.f,0.f);
    this->pointsText.setString("NONE");
    this->highScoreText.setFont(this->font);
    this->highScoreText.setCharacterSize(24);
    this->highScoreText.setPosition(0.f,24.f);
    this->highScoreText.setString("NONE");
}

void Game::initFont() {
    this->font.loadFromFile("./fonts/Cabin-Regular-TTF.ttf");
}


void Game::initMainMenuBt() {
    this->buttonTextures.loadFromFile("./textures/MainMenuBt.png");
    for(int i = 0; i < 3; i++)
    {

        Button *button = new Button(sf::IntRect (48.f, 0.f + i*16.f, 48.f,16.f), this->buttonTextures);
        button->setScale(sf::Vector2f(4.f,4.f));

        button->setPosition(
                sf::Vector2f(this->window->getSize().x / 2.f - button->getSprite().getGlobalBounds().width / 2.f,
                             this->window->getSize().y / 2.f - button->getSprite().getGlobalBounds().height * 2.f +
                             i * (button->getSprite().getGlobalBounds().height + 16.f)));
        this->mainMenuButtons.push_back(button);

    }
}

void Game::initPauseMenuBt() {
    this->buttonTextures.loadFromFile("./textures/PauseMenuBt.png");
    for(int i = 0; i < 2; i++)
    {

        Button *button = new Button(sf::IntRect (48.f, 0.f + i*16.f, 48.f,16.f), this->buttonTextures);
        button->setScale(sf::Vector2f(4.f,4.f));
        button->setPosition(
                sf::Vector2f(this->window->getSize().x / 2.f - button->getSprite().getGlobalBounds().width / 2.f,
                             this->window->getSize().y / 2.f - button->getSprite().getGlobalBounds().height * 2.f +
                             i * (button->getSprite().getGlobalBounds().height + 16.f)));
        this->pauseMenuButtons.push_back(button);

    }
}

void Game::initEndGameMenuBt() {
    this->buttonTextures.loadFromFile("./textures/EndGameMenuBt.png");
    for(int i = 0; i < 2; i++)
    {

        Button *button = new Button(sf::IntRect (48.f, 0.f + i*16.f, 48.f,16.f), this->buttonTextures);
        button->setScale(sf::Vector2f(4.f,4.f));
        button->setPosition(
                sf::Vector2f(this->window->getSize().x / 2.f - button->getSprite().getGlobalBounds().width / 2.f,
                             this->window->getSize().y / 2.f - button->getSprite().getGlobalBounds().height * 2.f +
                             i * (button->getSprite().getGlobalBounds().height + 16.f)));
        this->endGameMenuButtons.push_back(button);

    }
}


void Game::initOptionsMenuBt() {
    this->buttonTextures.loadFromFile("./textures/optionsMenuBt.png");
    Button *button = new Button(sf::IntRect (48.f, 0.f, 48.f,16.f), this->buttonTextures);
    button->setScale(sf::Vector2f(4.f,4.f));
    button->setPosition(sf::Vector2f(this->window->getSize().x / 2.f - button->getSprite().getGlobalBounds().width / 2.f,
                                     this->window->getSize().y - button->getSprite().getGlobalBounds().height * 2.f - 10.f ));
    this->optionsMenuButtons.push_back(button);

    Pagination* pag = new Pagination(this->buttonTextures, sf::IntRect (0.f, 48.f, 95.f,16.f),
                                     sf::IntRect (16.f, 16.f, 16.f,16.f), this->font);
    pag->setPosition(sf::Vector2f(this->window->getSize().x / 2.f - pag->getSprite().getGlobalBounds().width / 2.f,
                                  this->window->getSize().y / 2.f - pag->getSprite().getGlobalBounds().height * 2.f));
    this->optionsMenuPaginations.push_back(pag);
}

void Game::initBackGrnd() {
    this->mainMenuBackGrndTexture.loadFromFile("./textures/animated_back/flipBook.png");
    this->mainMenuBakcGrndSprite.setTexture(this->mainMenuBackGrndTexture);
    this->mainMenuBakcGrndSprite.setTextureRect(sf::IntRect(0,0,960,640));
}

void Game::initFiles() {
    this->HighScore.open("./data/HighScore.txt");
    if(!this->HighScore.is_open())std::cout<<"Error opening file \n";
    this->HighScore.close();
}

//Public functions

void Game::poolEvent() {
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    if(this->CurrScene == LEVEL_1) this->CurrScene = PAUSE_MENU;
                else if (this->ev.key.code == sf::Keyboard::Escape)
                    if(this->CurrScene == PAUSE_MENU) this->CurrScene = LEVEL_1;
                else
                    this->window->close();
                break;
            case sf::Event::MouseButtonReleased:
                if(ev.mouseButton.button == sf::Mouse::Left)
                this->updateButtonClick(this->ev);
                break;
        }
    }
}

bool Game::running() {
    return this->window->isOpen();
}

//Render
void Game::render() {
    this->window->clear();

    switch (CurrScene) {
        case MAIN_MENU:
            this->window->draw(this->mainMenuBakcGrndSprite);
            for(int i = 0; i < this->mainMenuButtons.size();i++)
            {
                this->mainMenuButtons[i]->render(this->window);
            }
            break;
        case LEVEL_1:
            this->renderStars(this->window);
            this->renderMeteors(this->window);
            this->player.render(this->window);
            this->renderUi(this->window);
            break;
        case PAUSE_MENU:
            this->renderStars(this->window);
            this->renderMeteors(this->window);
            this->player.render(this->window);
            this->renderUi(this->window);
            for(int i = 0; i < this->pauseMenuButtons.size();i++)
            {
                this->pauseMenuButtons[i]->render(this->window);
            }
            break;
        case END_GAME_MENU:
            this->renderStars(this->window);
            this->renderMeteors(this->window);
            this->player.render(this->window);
            this->renderUi(this->window);
            for(int i = 0; i < this->endGameMenuButtons.size();i++)
            {
                this->endGameMenuButtons[i]->render(this->window);
            }
            break;
        case OPTIONS:
            this->window->draw(this->mainMenuBakcGrndSprite);
            for(int i = 0; i < this->optionsMenuButtons.size();i++)
            {
                this->optionsMenuButtons[i]->render(this->window);
            }
            for(int i = 0; i < this->optionsMenuPaginations.size();i++)
            {
                this->optionsMenuPaginations[i]->render(this->window);
            }
            break;
    }


    this->window->display();
}

void Game::renderStars(sf::RenderTarget* target) {
    for (auto st : this->stars)
        target->draw(st);
}

void Game::renderMeteors(sf::RenderTarget *target) {
    for(auto mt: this->meteors)
        target->draw(mt->getShape());
}

void Game::renderUi(sf::RenderTarget *target) {
    target->draw(this->pointsText);
    target->draw(this->highScoreText);
    target->draw(this->maxHpBar);
    for(auto hc : currentHpBar)
        target->draw(hc);
}

//Update
void Game::update() {
    this->poolEvent();
    this->updateTime();
    switch (CurrScene) {
        case MAIN_MENU:
            this->updateBackGrnd();
            this->updateButtons();
            break;
        case LEVEL_1:

            if(this->player.getCondition())
                this->CurrScene = END_GAME_MENU;

            this->player.update(this->window);
            this->updateStars();
            this->updateMeteores(this->window);
            this->updateCollision(this->window);
            this->updateHpBar(this->window);
            this->updatePoints();
            this->updateHighScore();

            break;
        case PAUSE_MENU:
            this->updateButtons();
            break;
        case END_GAME_MENU:
            this->updateButtons();
            break;
        case OPTIONS:
            this->updateButtons();
            this->updateBackGrnd();
            for(int i = 0; i < this->optionsMenuPaginations.size();i++)
                this->optionsMenuPaginations[i]->update(this->mousePos);
            break;
    }


}

void Game::updateTime() {
    this->time = this->clock.getElapsedTime().asSeconds();
    this->spawnMeteorFrame +=time;
    this->backGrndAnimationFrame +=time;
    this->clock.restart();

}

void Game::updateCollision(sf::RenderTarget* target) {
    this->updateCollisionForMeteores(target);

    this->destroyMeteores();
}

void Game::updateStars() {
    for(auto &st: this->stars)
    {
        st.move(0.f,1.f);
        if (st.getGlobalBounds().top + st.getGlobalBounds().height >= this->window->getSize().y)
            st.setPosition(rand() % this->window->getSize().x, -rand() % 50);
    }

}

void Game::moveMeteores() {
    for(auto& mt : this->meteors)
    {
        mt->setPosition(mt->getShape().getPosition().x,mt->getShape().getPosition().y + mt->getSpeed());
    }
}



void Game::spawnMeteors(sf::RenderTarget *target) {
    if(this->numberOfMeteors < this->maxMeteors)
    {
        if(this->spawnMeteorFrame >= 0.05) {
            this->spawnMeteorFrame = 0;
            this->numberOfMeteors++;
            Meteor* meteor = new Meteor(target);


            this->meteors.push_back(meteor);
        }
    }
    else
    {
        this->spawnMeteorFrame = 1;
    }
}

void Game::destroyMeteores() {
    //Destroy meteores
    for (int i = 0; i < this -> meteors.size(); ++i) {
        for(int j = 0; j < this->player.getMagazine().size();j++)
        {
            if(this->meteors[i]->getShape().getGlobalBounds().intersects(this->player.getBomb(j).getSprite().getGlobalBounds()))
            {

                this->meteors[i]->setHp(this->meteors[i]->getHp() - this->player.getBomb(j).getDamage());

                this->player.deleteBomb(j);
            }
        }
    }
}

void Game::updateCollisionForMeteores(sf::RenderTarget *target) {
    //Respawn meteores that got out of bounds
    for(int i = 0; i<this->meteors.size();i++)
    {
        if(this->meteors[i]->getShape().getGlobalBounds().top >= target->getSize().y) {
            delete this->meteors[i];
            this->meteors.erase(this->meteors.begin() + i);
            this->numberOfMeteors--;
        }

    }

    //Decrese hero hp when collapsing with meteor
    for(int i = 0; i<this->meteors.size();i++)
    {
        if(this->player.getSprite().getGlobalBounds().intersects(this->meteors[i]->getShape().getGlobalBounds())) {
            if(this->meteors[i]->getDamage() > this->player.getHp()) this->meteors[i]->setDamage(this->player.getHp());
            if(meteors[i]->getType() == HEALING) {
                this->player.heal(1);
                this->points+= this->meteors[i]->getPoints();
            }
            else
             this->player.damaging(this->meteors[i]->getDamage());
            delete this->meteors[i];
            this->meteors.erase(this->meteors.begin() + i);
            this->numberOfMeteors--;
        }
    }
}

void Game::updateHpBar(sf::RenderTarget* target) {
    this->currentHpBar.clear();
    for(int i{0};i<this->player.getHp();i++)
    {
        this->currentHpBar.push_back(hpCell);
        this->currentHpBar[i].setPosition(target->getSize().x - this->currentHpBar[i].getGlobalBounds().width*this->currentHpBar.size() - 4.f,
                                          5.f);
    }
}

void Game::updateMeteores(sf::RenderTarget* target) {
    this->spawnMeteors(target);
    this->moveMeteores();

    for(int i{0}; i<this->meteors.size();i++)
    {
        this->meteors[i]->update();
        if(this->meteors[i]->getHp()<=0) {
            if(meteors[i]->getType() != HEALING)
            this->points+= this->meteors[i]->getPoints();
            delete this->meteors[i];
            this->meteors.erase(this->meteors.begin() + i);
            this->numberOfMeteors--;
        }
    }
}

void Game::updatePoints() {
    std::stringstream ss;
    ss<<"Points: "<<this->points<<'\n';
    this->pointsText.setString(ss.str());

    std::stringstream hs;
    hs<<"High Score: "<<this->highScore<<'\n';
    this->highScoreText.setString(hs.str());
}

void Game::updateMousePos() {
    this->mousePos = sf::Vector2f (sf::Mouse::getPosition(*this->window).x,sf::Mouse::getPosition(*this->window).y);
}

void Game::updateButtons() {
    if(this->CurrScene == MAIN_MENU) {
        for (auto button: this->mainMenuButtons) {
            this->updateMousePos();
            button->update(this->mousePos);
        }
    }
    else if(this->CurrScene == PAUSE_MENU)
    {
        for (auto button: this->pauseMenuButtons) {
            this->updateMousePos();
            button->update(this->mousePos);
        }
    }
    else if(this->CurrScene == END_GAME_MENU)
    {
        for (auto button: this->endGameMenuButtons) {
            this->updateMousePos();
            button->update(this->mousePos);
        }
    }
    else if(this->CurrScene == OPTIONS)
    {
        for (auto button: this->optionsMenuButtons) {
            this->updateMousePos();
            button->update(this->mousePos);
        }
    }
}

void Game::updateButtonClick(sf::Event event) {
    if(this->CurrScene == MAIN_MENU) {
        for (int i = 0; i < this->mainMenuButtons.size();i++) {
            if (this->mainMenuButtons[i]->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y) && event.type == sf::Event::MouseButtonReleased) {
                if(i == 0) this->CurrScene = LEVEL_1;
                if(i == 1) this->CurrScene = OPTIONS;
                if(i == 2) this->window->close();
            }
        }
    }
    else if(this->CurrScene == PAUSE_MENU) {
        for (int i = 0; i < this->pauseMenuButtons.size();i++) {
            if (this->pauseMenuButtons[i]->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y) && event.type == sf::Event::MouseButtonReleased) {
                if(i == 0) this->CurrScene = LEVEL_1;
                if(i == 1)
                {
                    this->CurrScene = MAIN_MENU;
                    this->resetLevelOne();
                }
            }
        }
    }
    else if(this->CurrScene == END_GAME_MENU) {
        for (int i = 0; i < this->endGameMenuButtons.size();i++) {
            if (this->endGameMenuButtons[i]->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y) && event.type == sf::Event::MouseButtonReleased) {
                if(i == 0)
                {
                    this->CurrScene = LEVEL_1;
                    this->resetLevelOne();
                }
                if(i == 1) {
                    this->CurrScene = MAIN_MENU;
                    this->resetLevelOne();
                }
            }
        }
    }
    else if(this->CurrScene == OPTIONS) {
        for (int i = 0; i < this->optionsMenuButtons.size();i++) {
            if (this->optionsMenuButtons[i]->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y) && event.type == sf::Event::MouseButtonReleased) {
                if(i == 0)
                {
                    this->CurrScene = MAIN_MENU;
                }
            }
        }
    }
}

void Game::updateBackGrnd() {
    if(this->backGrndAnimationFrame >1.25f)
    {
        this->backGrndAnimationFrame =0.f;
    }
    this->mainMenuBakcGrndSprite.setTextureRect(sf::IntRect(0 + 960*static_cast<int>(this->backGrndAnimationFrame*4),
                                                                0,960,640));
}

void Game::resetLevelOne() {
    this->player.setHp(this->player.getMaxHp());
    this->player.setCondition(false);
    this->player.setPos(this->startPlayerPos.x,this->startPlayerPos.y);
    for(int i = 0; i < this->player.getMagazine().size();i++)
    {
        this->player.deleteBomb(i);
    }
    this->points = 0;
    this->meteors.erase(this->meteors.begin(), this->meteors.end());
    this->numberOfMeteors =0;
}

void Game::updateHighScore() {
    this->HighScore.open("./data/HighScore.txt");
    this->highScore.clear();
    std::getline(this->HighScore,this->highScore);
    this->HighScore.close();
    if(std::stoi(this->highScore)< points) {
        this->HighScore.open("./data/HighScore.txt");
        this->HighScore << points;
    }
    this->HighScore.close();
}










































