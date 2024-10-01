#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class progressBar
{
private:
    int percentage = 0;
    float songDuaration;
    sf::Texture progressTexture;
    sf::Texture seekerTexture;
    sf::Sprite progressSprite;
    sf::Sprite seekerSprite;

public:
    progressBar(sf::SoundBuffer &song);

    void addTextures(std::string progressTexFilename, std::string seekerTexFilename);

    void addPosition(sf::Vector2f position);

    void seek(sf::Sound &sound, sf::Vector2f seekPos);

    sf::FloatRect getBounds();

    void updateSongDuration(sf::SoundBuffer &buffer);

    void updateProgress(sf::RenderWindow &window, sf::Sound &sound);

    void update(sf::RenderWindow &window);
};