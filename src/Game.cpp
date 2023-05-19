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
    this->initButtons();
    this->initBackGrnd();
    this->initFiles();
}

Game::~Game() {
    this->meteors.clear();
    this->stars.clear();
    delete this->window;
    for(int i = 0; i< this->mainMenuButtons.size();i++)
    {
        delete this->mainMenuButtons[i];
    }
}

//Private functions
void Game::initWindow() {
    this->videoMode = sf::VideoMode(800.f,600.f);
    this->window = new sf::RenderWindow(videoMode,"Test",sf::Style::Close|sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initVariables() {
    this->maxMeteors = 30;
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
}

void Game::initFont() {
    this->font.loadFromFile("./fonts/Cabin-Regular-TTF.ttf");
}

void Game::initButtons() {
    this->buttonTextures.loadFromFile("./textures/Buttons.png");
    for(int i = 0; i < 4; i++)
    {
        //TODO FIX IT
        Button *button = new Button(sf::Vector2f(48.f, 0.f + i * 16.f), this->buttonTextures);
        button->setScale(4);
        if(i < 2) {
            button->setPosition(
                    sf::Vector2f(this->window->getSize().x / 2.f - button->getSprite().getGlobalBounds().width / 2.f,
                                 this->window->getSize().y / 2.f - button->getSprite().getGlobalBounds().height * 2.f +
                                 i * (button->getSprite().getGlobalBounds().height + 16.f)));
            mainMenuButtons.push_back(button);
        }
        else if(i == 2)
        {
            button->setPosition(sf::Vector2f(this->window->getSize().x / 2.f - button->getSprite().getGlobalBounds().width / 2.f,
                                 this->window->getSize().y / 2.f - button->getSprite().getGlobalBounds().height * 2.f));
            this->pauseMenuButtons.push_back(button);
            this->pauseMenuButtons.push_back(this->mainMenuButtons[1]);
            this->pauseMenuButtons[1]->setPosition(sf::Vector2f(this->window->getSize().x / 2.f - button->getSprite().getGlobalBounds().width / 2.f,
                                                                this->window->getSize().y / 2.f - button->getSprite().getGlobalBounds().height * 2.f +
                                                                (button->getSprite().getGlobalBounds().height + 16.f)));
        }
        else if(i == 3)
        {
            button->setPosition(sf::Vector2f(this->window->getSize().x / 2.f - button->getSprite().getGlobalBounds().width / 2.f,
                                             this->window->getSize().y / 2.f - button->getSprite().getGlobalBounds().height * 2.f));
            this->endGameMenuButtons.push_back(button);
            this->endGameMenuButtons.push_back(this->mainMenuButtons[1]);
            this->endGameMenuButtons[1]->setPosition(sf::Vector2f(this->window->getSize().x / 2.f - button->getSprite().getGlobalBounds().width / 2.f,
                                                                this->window->getSize().y / 2.f - button->getSprite().getGlobalBounds().height * 2.f +
                                                                (button->getSprite().getGlobalBounds().height + 16.f)));
        }
    }
}

void Game::initBackGrnd() {
    this->mainMenuBackGrndTexture.loadFromFile("./textures/animated_back/flipBook.png");
    this->mainMenuBakcGrndSprite.setTexture(this->mainMenuBackGrndTexture);
    this->mainMenuBakcGrndSprite.setTextureRect(sf::IntRect(0,0,960,640));
}

void Game::initFiles() {
    this->HighScore.open("./data/HighScore.txt");
    if(!this->HighScore.is_open())std::cout<<"Error opening file \n";
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
    }


    this->window->display();
}

void Game::renderStars(sf::RenderTarget* target) {
    for (auto st : this->stars)
        target->draw(st);
}

void Game::renderMeteors(sf::RenderTarget *target) {
    for(auto mt: this->meteors)
        target->draw(mt.getShape());
}

void Game::renderUi(sf::RenderTarget *target) {
    target->draw(this->pointsText);
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

            break;
        case PAUSE_MENU:
            this->updateButtons();
            break;
        case END_GAME_MENU:
            this->updateButtons();
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
            st.setPosition(rand() % this->window->getSize().x, 0.f);
    }

}

void Game::moveMeteores() {
    for(auto& mt : this->meteors)
    {
        mt.setPosition(mt.getShape().getPosition().x,mt.getShape().getPosition().y + mt.getSpeed());
    }
}



void Game::spawnMeteors(sf::RenderTarget *target) {
    if(this->numberOfMeteors < this->maxMeteors)
    {
        if(this->spawnMeteorFrame >= 0.1) {
            this->spawnMeteorFrame = 0;
            this->numberOfMeteors++;
            Meteor meteor(target);
            for(int i = 0; i < this->meteors.size();i++) {
                if (this->meteors[i].getShape().getGlobalBounds().intersects(meteor.getShape().getGlobalBounds())) {
                    this->meteors.erase(this->meteors.begin() + i);
                    this->numberOfMeteors--;
                }
            }

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
    for (int i = 0; i < this->player.getMagazine().size(); ++i) {
        for(int j = 0; j < this -> meteors.size();j++)
        {
            if(this->meteors[j].getShape().getGlobalBounds().intersects(this->player.getBomb(i).getSprite().getGlobalBounds()))
            {

                this->meteors[j].setHp(this->meteors[j].getHp() - this->player.getBomb(i).getDamage());

                this->player.deleteBomb(i);
            }
        }
    }
}

void Game::updateCollisionForMeteores(sf::RenderTarget *target) {
    //Respawn meteores that got out of bounds
    for(int i = 0; i<this->meteors.size();i++)
    {
        if(this->meteors[i].getShape().getGlobalBounds().top + this->meteors[i].getShape().getGlobalBounds().height >= target->getSize().y) {
            this->meteors.erase(this->meteors.begin()+i);
            this->numberOfMeteors--;
        }

    }

    //Decrese hero hp when collapsing with meteor
    for(int i = 0; i<this->meteors.size();i++)
    {
        if(this->player.getSprite().getGlobalBounds().intersects(this->meteors[i].getShape().getGlobalBounds())) {
            if(this->meteors[i].getDamage() > this->player.getHp()) this->meteors[i].setDamage(this->player.getHp());
            this->player.damaging(this->meteors[i].getDamage());
            this->meteors.erase(this->meteors.begin()+i);
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
        if(this->meteors[i].getHp()<=0) {
            if(meteors[i].getType() == HEALING) this->player.heal(1);
            this->points+= this->meteors[i].getPoints();
            this->meteors.erase(this->meteors.begin()+i);
            this->numberOfMeteors--;
        }
    }
}

void Game::updatePoints() {
    std::stringstream ss;
    ss<<"Points: "<<this->points<<'\n';
    this->pointsText.setString(ss.str());
}

void Game::updateMousePos() {
    this->mousePos = sf::Vector2f (sf::Mouse::getPosition(*this->window).x,sf::Mouse::getPosition(*this->window).y);
}

void Game::updateButtons() {
    if(this->CurrScene == MAIN_MENU) {
        for (auto button: this->mainMenuButtons) {
            this->updateMousePos();
            if (button->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                button->setSpriteRect(sf::Vector2f(button->getSprite().getTextureRect().left + 48.f,
                                                   button->getSprite().getTextureRect().top));
            } else if (button->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                       !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                button->setSpriteRect(sf::Vector2f(button->getSprite().getTextureRect().left - 48.f,
                                                   button->getSprite().getTextureRect().top));
            } else {
                button->setSpriteRect(sf::Vector2f(button->getRect().left, button->getRect().top));
            }
        }
    }
    else if(this->CurrScene == PAUSE_MENU)
    {
        for (auto button: this->pauseMenuButtons) {
            this->updateMousePos();
            if (button->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                button->setSpriteRect(sf::Vector2f(button->getSprite().getTextureRect().left + 48.f,
                                                   button->getSprite().getTextureRect().top));
            } else if (button->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                       !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                button->setSpriteRect(sf::Vector2f(button->getSprite().getTextureRect().left - 48.f,
                                                   button->getSprite().getTextureRect().top));
            } else {
                button->setSpriteRect(sf::Vector2f(button->getRect().left, button->getRect().top));
            }
        }
    }
    else if(this->CurrScene == END_GAME_MENU)
    {
        for (auto button: this->endGameMenuButtons) {
            this->updateMousePos();
            if (button->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                button->setSpriteRect(sf::Vector2f(button->getSprite().getTextureRect().left + 48.f,
                                                   button->getSprite().getTextureRect().top));
            } else if (button->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                       !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                button->setSpriteRect(sf::Vector2f(button->getSprite().getTextureRect().left - 48.f,
                                                   button->getSprite().getTextureRect().top));
            } else {
                button->setSpriteRect(sf::Vector2f(button->getRect().left, button->getRect().top));
            }
        }
    }
}

void Game::updateButtonClick(sf::Event event) {
    if(this->CurrScene == MAIN_MENU) {
        for (int i = 0; i < this->mainMenuButtons.size();i++) {
            if (this->mainMenuButtons[i]->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y) && event.type == sf::Event::MouseButtonReleased) {
                if(i == 0) this->CurrScene = LEVEL_1;
                if(i == 1) this->window->close();
            }
        }
    }
    else if(this->CurrScene == PAUSE_MENU) {
        for (int i = 0; i < this->pauseMenuButtons.size();i++) {
            if (this->pauseMenuButtons[i]->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y) && event.type == sf::Event::MouseButtonReleased) {
                if(i == 0) this->CurrScene = LEVEL_1;
                if(i == 1) this->window->close();
            }
        }
    }
    else if(this->CurrScene == END_GAME_MENU) {
        for (int i = 0; i < this->pauseMenuButtons.size();i++) {
            if (this->pauseMenuButtons[i]->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y) && event.type == sf::Event::MouseButtonReleased) {
                if(i == 0)
                {
                    this->CurrScene = MAIN_MENU;
                    this->resetLevelOne();
                }
                if(i == 1) this->window->close();
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
    //std::cout<<this->mainMenuBakcGrndSprite.getTextureRect().left<<std::endl;
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




































