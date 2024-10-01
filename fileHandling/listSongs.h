#ifndef LIST_SONGS_H
#define LIST_SONGS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "discoverSongs.h"

class SongList
{
public:
    SongList(sf::RenderWindow &window, std::vector<Song *> &songLib);

    void update(sf::RenderWindow &window);
};

#endif