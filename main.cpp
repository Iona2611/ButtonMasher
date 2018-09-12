// Included libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>



// entry point for the program
int main()
{
	//------------------------------------------------------
	// Game Setup
	//------------------------------------------------------
	
	// Make a variable called gameWindow of the type RenderWindow
	sf::RenderWindow gameWindow;
	gameWindow.create(sf::VideoMode ::getDesktopMode(), "Button Masher",
		sf::Style::Titlebar | sf::Style::Close);

	// Create Button Sprite		
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("graphics/button.png");

	sf::Sprite buttonSprite;
	buttonSprite.setTexture(buttonTexture);

	// centre the sprite on the screen 
	buttonSprite.setPosition(
		gameWindow.getSize().x / 2 - buttonTexture.getSize().x / 2, 
		gameWindow.getSize().y / 2 - buttonTexture.getSize().y / 2);

	// Create Music 
	sf::Music gameMusic;
	gameMusic.openFromFile("audio/music.ogg");
	//gameMusic.play();

	// Create Font
	sf::Font gameFont;
	gameFont.loadFromFile("fonts/mainFont.ttf");
	
	// Create Title 
	sf::Text titleText;
	titleText.setFont(gameFont);
	titleText.setString("Button Mahser!");
	titleText.setCharacterSize(40);
	titleText.setFillColor(sf::Color::Cyan);
	titleText.setStyle(sf::Text::Bold | sf::Text::Italic);
	titleText.setPosition(gameWindow.getSize().x / 2 
		- titleText.getLocalBounds().width / 2, 30);


	// Author Text
	sf::Text authorText;
	authorText.setFont(gameFont);
	authorText.setString("by Iona O'Donnell");
	authorText.setCharacterSize(20);
	authorText.setFillColor(sf::Color::Magenta);
	authorText.setStyle(sf::Text::Italic);
	authorText.setPosition(gameWindow.getSize().x / 2 - authorText.getLocalBounds().width / 2, 80);

	// Score
	int score = 0;
	
	// Score Text
	sf::Text scoreText;
	scoreText.setFont(gameFont);
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setCharacterSize(25);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(30, 30);

	// Timer Text
	sf::Text timerText;
	timerText.setFont(gameFont);
	timerText.setString("Time Remaining: 0");
	timerText.setCharacterSize(25);
	timerText.setFillColor(sf::Color::White);
	timerText.setPosition(gameWindow.getSize().x - timerText.getLocalBounds().width -50 / 2, 30);

	// Timer functionality 
	sf::Time timeLimit = sf::seconds(10.0f);
	sf::Time timeRemaining = timeLimit;
	sf::Clock gameClock;

	// click sound effect
	sf::SoundBuffer clickBuffer;
	clickBuffer.loadFromFile("audio/buttonclick.ogg");
	sf::Sound clickSound;
	clickSound.setBuffer(clickBuffer);

	//------------------------------------------------------
	// Game Loop
	//------------------------------------------------------
	
	// Runs every frame until the game window is closed 
	while (gameWindow.isOpen())
	{
		// Check for input 
		sf::Event gameEvent;
		while (gameWindow.pollEvent(gameEvent))
		{
			// Process events 
			// check if the event is a mouse button pressed event

			
			if (gameEvent.type == sf::Event::MouseButtonPressed)

			{

				if (buttonSprite.getGlobalBounds().contains(gameEvent.mouseButton.x, gameEvent.mouseButton.y))
				{
					// we clicked the button!!!
					score = score + 1;

					// play the click sound 
					clickSound.play();

				}
			}

			// Check if the event is the closed event 
			if (gameEvent.type == sf::Event::Closed)
			{

				// close the game window
				gameWindow.close();
			}
		}


		// Update game state

		sf::Time frameTime = gameClock.restart();
		timeRemaining = timeRemaining - frameTime;
		timerText.setString("Time Remaining: " + std::to_string((int)timeRemaining.asSeconds()));

		
		scoreText.setString("Score: " + std::to_string(score));
		



		// Draw graphics 
		gameWindow.clear(sf::Color::Black);
	
		// Draw everything
		gameWindow.draw(buttonSprite);
		gameWindow.draw(titleText);
		gameWindow.draw(authorText);
		gameWindow.draw(scoreText);
		gameWindow.draw(timerText);

		// Display the window contents on the screen 
		gameWindow.display();
	}

	// exit point for the program
	return 0;
}