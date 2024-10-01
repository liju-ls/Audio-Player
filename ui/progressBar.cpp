#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "progressBar.h"
#include <iostream>

progressBar::progressBar(sf::SoundBuffer &song)
{
    this->songDuaration = song.getDuration().asSeconds();
    this->progressTexture.loadFromFile("C:/Users/LIJU/Desktop/Music Player/assets/progress-bar.png");
    this->seekerTexture.loadFromFile("C:/Users/LIJU/Desktop/Music Player/assets/progress-tracker.png");
    this->progressSprite.setTexture(progressTexture);
    this->seekerSprite.setTexture(seekerTexture);
    this->progressSprite.setPosition(sf::Vector2f(50, 500));
    this->seekerSprite.setPosition(sf::Vector2f(50, 500) + sf::Vector2f(0, -5));
}

void progressBar::seek(sf::Sound &sound, sf::Vector2f seekPos)
{
    float off = (seekPos.x - 50) / (700 / this->songDuaration);
    sf::Time seekTime = sf::seconds(off);
    sound.setPlayingOffset(seekTime);
}

sf::FloatRect progressBar::getBounds()
{
    return this->progressSprite.getGlobalBounds();
}

void progressBar::updateSongDuration(sf::SoundBuffer &buffer)
{
    this->songDuaration = buffer.getDuration().asSeconds();
}

void progressBar::updateProgress(sf::RenderWindow &window, sf::Sound &sound)
{

    if (sound.getStatus() == sf::Sound::Playing)
    {
        float increment = (700 / this->songDuaration) * sound.getPlayingOffset().asSeconds();
        this->seekerSprite.setPosition(sf::Vector2f(50 + increment, 495));
    }

    window.draw(this->progressSprite);
    window.draw(this->seekerSprite);
}

void progressBar::update(sf::RenderWindow &window)
{
    window.draw(this->progressSprite);
    window.draw(this->seekerSprite);
}
