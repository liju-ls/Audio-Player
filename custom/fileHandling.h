#include <SFML/Audio.hpp>
#include <string>

using std::string;

sf::SoundBuffer loadMusic(string filename)
{
    sf::SoundBuffer buffer;
    buffer.loadFromFile(filename);
    return buffer;
}

sf::Texture loadTexture(string filename)
{
    sf::Texture tex;
    tex.loadFromFile(filename);
    return tex;
}

sf::Sprite textureToSprite(sf::Texture &textureData)
{
    sf::Sprite sprite(textureData);
    return sprite;
}

sf::Sprite loadTextureAsSprite(string filename)
{
    sf::Texture tex;
    tex.loadFromFile(filename);
    sf::Sprite sprite(tex);
    return sprite;
}