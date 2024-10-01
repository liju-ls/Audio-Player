#include "listSongs.h"
#include <iostream>
#include "discoverSongs.h"

SongList::SongList(sf::RenderWindow &window, std::vector<Song *> &songLib)
{
    for (auto song : songLib)
    {
        sf::Font font;
        font.loadFromFile("C:/Users/LIJU/Desktop/Music Player/assets/Helvetica.ttf");
        sf::Text name;
        name.setFont(font);
        name.setString(song->name);
        name.setCharacterSize(16);
    }
}

void SongList::update(sf::RenderWindow &window)
{
}