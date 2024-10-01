#include <SFML/Window.hpp>
#include <filesystem>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "custom/fileHandling.h"
#include "ui/progressBar.h"
#include "ui/playAndPause.h"
#include "fileHandling/discoverSongs.h"
#include "fileHandling/folderOpen.h"
// #include "fileHandling/listSongs.h"

int main()
{

  sf::RenderWindow window(sf::VideoMode(800, 600), "Music Player");
  sf::SoundBuffer buffer;
  sf::Sound sound;

  std::vector<Song *> songsLib;
  std::vector<sf::Text> songText;
  std::vector<sf::RectangleShape> songRect;

  std::string songDir;
  sf::Font font;

  font.loadFromFile("C:/Users/LIJU/Desktop/Music Player/assets/Helvetica.ttf");

  bool isLoaded = false;
  int currentPlayingSong = 0;

  progressBar progress(buffer);
  PlayAndPause playBtn;

  playBtn.addTexture("C:/Users/LIJU/Desktop/Music Player/assets/Play-Idle.png", "C:/Users/LIJU/Desktop/Music Player/assets/Pause-Idle.png", "C:/Users/LIJU/Desktop/Music Player/assets/nextArrow.png", "C:/Users/LIJU/Desktop/Music Player/assets/prevArrow.png");
  playBtn.addPosition(sf::Vector2f(400, 530));
  playBtn.addScale(0.5, 0.5);

  // SongList songsList(window, songsLib);

  while (window.isOpen())
  {

    // initializing events in SFML Window
    sf::Event event;

    // Clearing SFML window before render
    window.clear(sf::Color(255, 255, 255, 255));

    // Drawing play, pause and progress UI
    playBtn.updatePlayAndPause(window, sound);
    progress.updateProgress(window, sound);

    // Drawing songs list and background rectangle for hover effect
    for (int i = 0; i < songText.size(); i++)
    {
      window.draw(songRect[i]);
      window.draw(songText[i]);
    }

    while (window.pollEvent(event))
    {

      // event for close window
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }

      // event for hover effect
      if (event.type == sf::Event::MouseMoved)
      {

        sf::Vector2f mousePos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
        for (int i = 0; i < songText.size(); ++i)
        {

          sf::FloatRect rect = songRect[i].getGlobalBounds();
          if (rect.contains(mousePos))
          {
            songRect[i].setFillColor(sf::Color::Cyan);
          }
          else
          {
            songRect[i].setFillColor(sf::Color::White);
          }
        }
      }

      // event for mouse button clicks
      if (event.type == sf::Event::MouseButtonPressed)
      {

        // play and pause
        if (event.mouseButton.button == sf::Mouse::Left)
        {
          sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
          sf::FloatRect pos = playBtn.getBounds();

          if (pos.contains(mousePos))
          {
            if (sound.getStatus() == sf::Sound::Playing)
            {
              sound.pause();
              playBtn.updatePlayAndPause(window, sound);
            }
            else
            {
              sound.play();
              playBtn.updatePlayAndPause(window, sound);
            }
          }

          // seeking music
          sf::FloatRect progressRect = progress.getBounds();

          if (progressRect.contains(mousePos))
          {
            progress.seek(sound, mousePos);
          }

          // prev and next song
          sf::Vector2f nextBtnMousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
          sf::FloatRect nextBtnRect = playBtn.getNextBounds();

          if (nextBtnRect.contains(nextBtnMousePos))
          {
            if (currentPlayingSong < songsLib.size() - 1)
            {
              playBtn.getNext(buffer, songsLib, currentPlayingSong);
              progress.updateSongDuration(buffer);
              sound.play();
              currentPlayingSong += 1;
              std::cout << currentPlayingSong << std::endl;
            }
          }

          sf::FloatRect prevBtnRect = playBtn.getPrevBounds();

          if (prevBtnRect.contains(nextBtnMousePos))
          {
            if (currentPlayingSong > 0)
            {

              playBtn.getPrev(buffer, songsLib, currentPlayingSong);
              progress.updateSongDuration(buffer);
              sound.play();
              currentPlayingSong -= 1;
              std::cout << currentPlayingSong << std::endl;
            }
          }

          for (size_t i = 0; i < songsLib.size(); ++i)
          {
            sf::FloatRect textRect = songText[i].getGlobalBounds();
            if (textRect.contains(event.mouseButton.x, event.mouseButton.y))
            {
              currentPlayingSong = i;
              buffer.loadFromFile(songsLib[i]->path);
              progress.updateSongDuration(buffer);
              sound.play();
            }
          }
        }
      }
    }

    // check is songs loaded and if not load it and create songText and songRect
    if (!isLoaded)
    {
      songDir = OpenFolder(window.getSystemHandle());
      if (discoverSongs(window, songDir, songsLib) == 0)
      {
        isLoaded = true;
        std::cout << "loaded...";
        buffer = loadMusic(songsLib[0]->path);
        sound.setBuffer(buffer);
        currentPlayingSong += 1;
      }

      for (auto song : songsLib)
      {
        sf::Text text(song->name, font, 18);
        text.setFillColor(sf::Color(9, 12, 2, 255));
        text.setPosition(20, 20 + songText.size() * 50);
        songText.push_back(text);

        int windowX = window.getSize().x;
        int windowY = window.getSize().y;
        sf::RectangleShape shape(sf::Vector2f(100, 50));
        shape.setFillColor(sf::Color(187, 197, 170, 255));
        shape.setSize(sf::Vector2f(windowX * 0.95, text.getGlobalBounds().getSize().y + 20));
        shape.setPosition(text.getGlobalBounds().getPosition() + sf::Vector2f(-10, -10));
        songRect.push_back(shape);
      }
    }

    // update drawn sprites in SFML Window
    window.display();
  }
  return 0;
}