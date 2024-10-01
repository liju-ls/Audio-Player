#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include "discoverSongs.h"
#include "folderOpen.h"

Song::Song(std::string name, std::string path)
{

    this->name = name;
    this->path = path;
}

int discoverSongs(sf::RenderWindow &window, std::string songDirectory, std::vector<Song *> &songsLib)
{

    for (auto dir : std::filesystem::recursive_directory_iterator(songDirectory))
    {
        if (dir.path().extension() == ".mp3")
        {
            Song *temp = new Song(dir.path().filename().string(), dir.path().string());
            songsLib.push_back(temp);
        }
    }

    return 0;
}