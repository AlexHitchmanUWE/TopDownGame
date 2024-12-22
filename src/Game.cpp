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
    else
    {
        window.draw(background);
        window.draw(*click_box1);
    }
}

void Game::mouseClicked(sf::Event event)
{
    sf::Vector2i click = sf::Mouse::getPosition(window);
    
    if (collisionCheck(click, *click_box1))// if mouse clicks the clickzone
    {
        if (true)
        {
            std::cout << click.x << " " << click.y << std::endl;
            player->setPosition(click.x- player->getGlobalBounds().width/2, click.y - player->getGlobalBounds().height);
        }

    }
}

void Game::initSprites()
{
    player = std::make_unique<sf::Sprite>();
    click_box1 = std::make_unique<sf::Sprite>();

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
    if (!click_box1_texture.loadFromFile("../Data/Images/Custom/StreetBackgrounds/PNG/City2/Bright/sky.png"))
    {
        std::cout << "\n click box is not loading";
    }
    background.setTexture(background_texture);
    menu_background.setTexture(menu_background_texture);
    player->setTexture(player_texture);
    click_box1->setTexture(click_box1_texture);

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
    menu_text.setString("Mouse Hunt");
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


