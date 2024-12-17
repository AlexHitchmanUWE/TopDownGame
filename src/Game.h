
#ifndef POINTANDCLICKSFML_GAME_H
#define POINTANDCLICKSFML_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
	public:
		Game(sf::RenderWindow& window);
		~Game();
		bool init();
		void initSprites();
		void initText();
		void update(float dt);
		void render();
		void mouseClicked(sf::Event event);
		void mouseButtonPressed(sf::Event event);
		void mouseButtonReleased(sf::Event event);
		void keyPressed(sf::Event event);
		void keyCollision(sf::Sprite *key, sf::Sprite *player);
		void holdKey(sf::Sprite *key, sf::Sprite *player);
		void keyDoorCollision(sf::Sprite* key, sf::Sprite* door);
		void setRoomValues();
		void setStreetValues();


	private:

		bool collisionCheck(sf::Vector2i click, sf::Sprite sprite);

		//window and clock - come with repository
		sf::RenderWindow& window;
		sf::Clock clocku;

		// regular sprites
		sf::Sprite background;
		sf::Sprite menu_background;
		sf::Sprite streetlights;
		sf::Sprite house;

		//sprite smart pointers
		std::unique_ptr<sf::Sprite> player;
		std::unique_ptr<sf::Sprite> click_box1;
		std::shared_ptr<sf::Sprite> room;
		std::shared_ptr<sf::Sprite> door;
		std::unique_ptr<sf::Sprite> key;

		// texture smart vectors
		std::vector<std::unique_ptr<sf::Texture>> rooms;
		std::vector<std::unique_ptr<sf::Texture>> doors;

		// Regular textures
		sf::Texture background_texture;
		sf::Texture menu_background_texture;
		sf::Texture player_texture;
		sf::Texture streetlight_texture;
		sf::Texture house_texture;
		sf::Texture click_box1_texture;
		sf::Texture room_texture;
		sf::Texture key_texture;

		// font and text
		sf::Font font;
		sf::Text menu_text;
		sf::Text play_option;
		sf::Text quit_option;

		// booleans
		bool in_menu;
		bool in_room = false;
		bool play_selected = true;
		bool holding_key = false;
		bool door_open = false;
		bool in_room_2 = false;


		sf::Clock clock;
		// time delay for the door opening
		sf::Time delay = sf::seconds(3);
		
};

#endif // PLATFORMER_GAME_H
