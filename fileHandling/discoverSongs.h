
#ifndef DISCOVER_SONGS_H
#define DISCOVER_SONGS_H

#include <SFML/Graphics.hpp>

struct Song
{
    std::string name;
    std::string path;

    Song(std::string name, std::string path);
};

int discoverSongs(sf::RenderWindow &window, std::string songDirectory, std::vector<Song *> &songsLib);

#endif