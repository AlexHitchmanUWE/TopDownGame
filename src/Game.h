
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

 private:
  sf::RenderWindow& window;
  //Sprites
  sf::Sprite ball;
  sf::Sprite background;
  //Textures
  sf::Texture ball_texture;
  sf::Texture background_texture

};

#endif // PLATFORMER_GAME_H
