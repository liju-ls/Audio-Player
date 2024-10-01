#include "playAndPause.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

PlayAndPause::PlayAndPause()
{
}

void PlayAndPause::addTexture(std::string playBtnFilename, std::string pauseBtnFilename, std::string nextBtnFilename, std::string prevBtnFilename)
{
    this->playTex.loadFromFile(playBtnFilename);
    this->pauseTex.loadFromFile(pauseBtnFilename);
    this->nextTex.loadFromFile(nextBtnFilename);
    this->prevTex.loadFromFile(prevBtnFilename);
    this->playAndPauseBtn.setTexture(playTex);
    this->nextBtn.setTexture(nextTex);
    this->prevBtn.setTexture(prevTex);
}

void PlayAndPause::addPosition(sf::Vector2f pos)
{
    this->playAndPauseBtn.setPosition(pos);
    float xScale = this->playAndPauseBtn.getScale().x;
    float xSize = this->playAndPauseBtn.getTexture()->getSize().x;

    this->nextBtn.setPosition(pos + sf::Vector2f(xSize / xScale, 0));
    this->prevBtn.setPosition(pos - sf::Vector2f(xSize / xScale, 0));
}

void PlayAndPause::addScale(float x, float y)
{
    this->playAndPauseBtn.setScale(x, y);
    this->nextBtn.setScale(x, y);
    this->prevBtn.setScale(x, y);
}

void PlayAndPause::updatePlayAndPause(sf::RenderWindow &window, sf::Sound &sound)
{

    if (sound.getStatus() == sf::Sound::Playing)
    {
        this->playAndPauseBtn.setTexture(this->pauseTex);
    }
    else
    {
        this->playAndPauseBtn.setTexture(this->playTex);
    }

    window.draw(playAndPauseBtn);
    window.draw(nextBtn);
    window.draw(prevBtn);
}

void PlayAndPause::update(sf::RenderWindow &window)
{
    window.draw(playAndPauseBtn);
    window.draw(nextBtn);
    window.draw(prevBtn);
}

sf::FloatRect PlayAndPause::getBounds()
{
    return this->playAndPauseBtn.getGlobalBounds();
}

sf::FloatRect PlayAndPause::getNextBounds()
{
    return this->nextBtn.getGlobalBounds();
}

sf::FloatRect PlayAndPause::getPrevBounds()
{
    return this->prevBtn.getGlobalBounds();
}

void PlayAndPause::getNext(sf::SoundBuffer &buffer, std::vector<Song *> songLib, int current)
{
    buffer.loadFromFile(songLib[current + 1]->path);
}

void PlayAndPause::getPrev(sf::SoundBuffer &buffer, std::vector<Song *> songLib, int current)
{
    buffer.loadFromFile(songLib[current - 1]->path);
}