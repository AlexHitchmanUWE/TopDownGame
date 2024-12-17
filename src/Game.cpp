#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
    // Starts in the menu
    in_menu = true;
    // Starts the clock
    sf::Time time = clocku.restart();
    float dt = time.asSeconds();
    // Initialising all on screen elements
	initSprites();
	initText();

	return true;
}

void Game::update(float dt)
{
    //handlls key, player and door collisions at runtime
    keyCollision(key.get(), player.get());
    if (holding_key)
    {
        holdKey(key.get(), player.get());
    }
    keyDoorCollision(key.get(), door.get());

}

void Game::render()
{
    if (in_menu)
    {
        window.draw(menu_background);
        window.draw(menu_text);
        window.draw(play_option);
        window.draw(quit_option);
    }
    else if (in_room && !in_room_2)// whilst in first room
    {
        window.draw(*room);
        window.draw(*door);
        window.draw(*player);
        window.draw(*key);

    }
    else if (in_room_2)// whilst in end room
    {
        window.draw(*room);
        window.draw(*player);
        window.draw(menu_text);
    }
    else
    {// if in street
        window.draw(background);
        window.draw(streetlights);
        window.draw(*click_box1);
        window.draw(house);
        window.draw(*door);
        if (!door_open) 
        {
            window.draw(*key);
        }
        window.draw(*player);
    }
}

void Game::mouseClicked(sf::Event event)
{
    sf::Vector2i click = sf::Mouse::getPosition(window);
    
    if (collisionCheck(click, *click_box1))// if mouse clicks the clickzone
    {
        if (true)
        {
            std::cout << click.x << " " << click.y << std::endl;;// outputs position that mouse clicked
            player->setPosition(click.x- player->getGlobalBounds().width/2, click.y - player->getGlobalBounds().height);// sets cat to click position
        }

    }
}

void Game::initSprites()
{
    player = std::make_unique<sf::Sprite>();
    click_box1 = std::make_unique<sf::Sprite>();
    room = std::make_shared<sf::Sprite>();
    door = std::make_shared<sf::Sprite>();
    key = std::make_unique<sf::Sprite>();

    //Loading Textures
	if (!background_texture.loadFromFile("../Data/Images/Custom/CityBackgrounds/city 1/10.png"))
	{
		std::cout << "\n background is not loading";
	}
    if (!menu_background_texture.loadFromFile("../Data/Images/Custom/CityBackgrounds/city 1/1.png"))
    {
        std::cout << "\n menu background is not loading";
    }
	if (!player_texture.loadFromFile("../Data/Images/Custom/AnimalPack/3 Cat/cats_idle-png/Cat_idle1.png"))
	{
		std::cout << "\n player is not loading";
	}
    if (!streetlight_texture.loadFromFile("../Data/Images/Custom/StreetBackgrounds/PNG/City2/Pale/road&lamps_pale.png"))
    {
        std::cout<< "\n street lights are not loading";
    }
    if (!house_texture.loadFromFile("../Data/Images/Custom/StreetBackgrounds/PNG/City2/Bright/houses3.png"))
    {
        std::cout<< "\n house is not loading";
    }
    if (!click_box1_texture.loadFromFile("../Data/Images/Custom/StreetBackgrounds/PNG/City2/Bright/sky.png"))
    {
        std::cout << "\n click box is not loading";
    }
    // smart vector texture loading
    if (!rooms.emplace_back(std::make_unique<sf::Texture>())->loadFromFile("../Data/Images/room.png"))
    {
        std::cout <<"\n room 1 is not loading";
    }
    if (!rooms.emplace_back(std::make_unique<sf::Texture>())->loadFromFile("../Data/Images/room2.png"))
    {
        std::cout << "\n room 2 is not loading";
    }
    if (!doors.emplace_back(std::make_unique<sf::Texture>())->loadFromFile("../Data/Images/door_closed.png"))
    {
        std::cout<< "\n door1 is not loading";
    }
    if (!doors.emplace_back(std::make_unique<sf::Texture>())->loadFromFile("../Data/Images/door_open.png"))
    {
        std::cout << "\n door2 is not loading";
    }
    // end of smart vector texture loading
    if (!key_texture.loadFromFile("../Data/Images/key.png"))
    {
        std::cout << "\n key is not loading";
    }

    setStreetValues();
}
void Game::initText()
{
    if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
    {
        std::cout << "font did not load \n";
    }

     // Initialize menu text font, size, colour, string, position
    menu_text.setFont(font);
    menu_text.setCharacterSize(80); 
    menu_text.setFillColor(sf::Color::White);
    menu_text.setString("Cat Trap");
    menu_text.setPosition(window.getSize().x / 2 - menu_text.getGlobalBounds().width /2, 30);

    // Initialize Play option text + attributes
    play_option.setFont(font);
    play_option.setCharacterSize(60); 
    play_option.setFillColor(sf::Color::Yellow); 
    play_option.setString("Play");
    play_option.setPosition(window.getSize().x / 2 - play_option.getGlobalBounds().width / 2.2, 300);

    // Initialize Quit option text
    quit_option.setFont(font);
    quit_option.setCharacterSize(60);
    quit_option.setFillColor(sf::Color(255, 255, 0, 125));
    quit_option.setString("Quit"); // Text for the Quit option
    quit_option.setPosition(window.getSize().x / 2 - quit_option.getGlobalBounds().width / 2.2, 400);

}
void Game::keyPressed(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
    {
        play_selected = !play_selected;
        // highlights menu options
        if (play_selected)
        {
            play_option.setFillColor(sf::Color(255, 255, 0, 255));
            quit_option.setFillColor(sf::Color(255, 255, 0, 125));
        }
        else
        {
            play_option.setFillColor(sf::Color(255, 255, 0, 125));
            quit_option.setFillColor(sf::Color(255, 255, 0, 255));
        }
    }
    else if (event.key.code == sf::Keyboard::Enter)
    {
        if (play_selected)
        {
            // Perform the action for Play
            in_menu = false;
        }
        else
        {
            // Perform the action for Quit
            window.close();
        }
    }
}

void Game::keyCollision(sf::Sprite *key, sf::Sprite *player)
{
    // if cat collides with key
    if (player->getGlobalBounds().intersects(key->getGlobalBounds()))
    {
        holding_key = true;
    }
}
void Game::holdKey(sf::Sprite *key, sf::Sprite *player)
{
    // this is how the cat holds the key
   key->setPosition(player->getPosition().x, player->getPosition().y);
}

void Game::keyDoorCollision(sf::Sprite* key, sf::Sprite* door)
{
    if (key->getGlobalBounds().intersects(door->getGlobalBounds()) && !in_room)
    {
        // if key and door collide whilst in the street
        door->setTexture(*doors.at(1));// sets door texure to open
        door_open = true;
        if (clock.getElapsedTime() >= delay)
        {
            in_room = true;
            setRoomValues();
        }
    }
    else if (key->getGlobalBounds().intersects(door->getGlobalBounds()) && in_room)
    {
        // if key and door collide whilst in the room
        door->setTexture(*doors.at(1));
        door_open = true;
        delay = sf::seconds(5);
        if (clock.getElapsedTime() >= delay)
        {
            in_room_2 = true;
            room->setTexture(*rooms.at(1));
            room->setPosition(-30, -50);// just right position for room2
            room->setScale(2.7, 2.7);// just right scale for room2
            menu_text.setString("Cat Trapped");// play on words for the title (aesthetic)
            // makes the text look like its printed on wall (aesthetic)
            menu_text.setPosition(500, 100);
            menu_text.setRotation(-11);

        }
    }
    
}

void Game::setRoomValues()
{
    // door values
    door->setTexture(*doors.at(0));
    door->setPosition(200, 165);
    door->setScale(1.5, 1.5);
    //player values
    player->setScale(3, 3);
    player->setPosition(door->getPosition().x, door->getPosition().y + player->getGlobalBounds().height*2);
    // click box values
    click_box1->setScale(1, 0.5);
    click_box1->setPosition(0, 460);
    // boolean values
    door_open = false;
    holding_key = false;
    // key values
    key->setPosition(600, 500);
    key->setScale(0.06, 0.06);
}

void Game::setStreetValues()
{
    // this is what plays on init 
    // (would have been below everything on init sprites)
    
    // Sets all the texures
    background.setTexture(background_texture);
    menu_background.setTexture(menu_background_texture);
    player->setTexture(player_texture);
    streetlights.setTexture(streetlight_texture);
    house.setTexture(house_texture);
    click_box1->setTexture(click_box1_texture);
    room->setTexture(*rooms.at(0));
    door->setTexture(*doors.at(0));
    key->setTexture(key_texture);

    // Sets the scale for each sprite
    background.setScale(0.5, 0.5);
    menu_background.setScale(2, 2);
    player->setScale(1.5, 1.5);
    streetlights.setScale(0.565, 0.56);
    house.setScale(0.565, 0.56);
    click_box1->setScale(1, 0.05);
    key->setScale(0.03, 0.03);
    room->setScale(1.8, 1.6);
    door->setScale(0.4, 0.4);

    // Sets positions for each sprite

    streetlights.setPosition(streetlights.getPosition().x, 100);
    house.setPosition(100, 290);
    player->setPosition(20, 525);
    click_box1->setPosition(0, 560);
    key->setPosition(900, 550);
    door->setPosition(760, 504);
}

bool Game::collisionCheck(sf::Vector2i click, sf::Sprite sprite)
{
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    sf::Vector2f clickF(static_cast<float>(click.x), static_cast<float>(click.y));
    // if statement measures between two float values and sees if x and y (sprite box) detects a click within it
    if (clickF.x >= spriteBounds.left &&
        clickF.x <= spriteBounds.left + spriteBounds.width &&
        clickF.y >= spriteBounds.top &&
        clickF.y <= spriteBounds.top + spriteBounds.height)// AABB collisions
    {
        // statement that prints out when the object is hit
        std::cout << "Hit!" << std::endl;
    
        return true;
    }
    else
    {
        return false;
    }
}


