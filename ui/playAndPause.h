#ifndef PLAY_AND_PAUSE_H
#define PLAY_AND_PAUSE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "../fileHandling/discoverSongs.h"

class PlayAndPause
{

private:
    bool isPlaying;
    sf::Texture playTex;
    sf::Texture pauseTex;
    sf::Texture nextTex;
    sf::Texture prevTex;
    sf::Sprite playAndPauseBtn;
    sf::Sprite nextBtn;
    sf::Sprite prevBtn;

public:
    PlayAndPause();

    void addTexture(std::string playBtnFilename, std::string pauseBtnFilename, std::string nextBtnFilename, std::string prevBtnFilename);

    void addPosition(sf::Vector2f pos);

    void addScale(float x, float y);

    void updatePlayAndPause(sf::RenderWindow &window, sf::Sound &sound);

    void update(sf::RenderWindow &window);

    sf::FloatRect getBounds();

    sf::FloatRect getNextBounds();

    sf::FloatRect getPrevBounds();

    void getNext(sf::SoundBuffer &buffer, std::vector<Song *> songLib, int current);

    void getPrev(sf::SoundBuffer &buffer, std::vector<Song *> songLib, int current);
};

#endif