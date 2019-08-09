#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream> 
#include <string>
using namespace std;

// Class for the Sprite tiles
class Tile
{
public:
	 
	sf::Sprite tile;

	int tilePosx;
	int tilePosy;

	int tileType = 0;
	
	// Creation of initial tiles
	void CreateTile(int setPosx, int setPosy)
	{
		tilePosx = setPosx;
		tilePosy = setPosy;
		tile.setPosition(sf::Vector2f(tilePosx, tilePosy));
	}

	// Updates int for the type of tile 
	void ChangeTileType()
	{
		tileType++;

		if (tileType > 2)
		{
			tileType = 0;
		}
	}

};

int main()
{
	// All the sprites loaded for textures
	sf::Texture sky;
	sky.loadFromFile("BlockSky.png");

	sf::Texture platform;
	platform.loadFromFile("BlockPlatform.png");

	sf::Texture lava;
	lava.loadFromFile("BlockLava.png");

	sf::Texture coin;
	coin.loadFromFile("Coin.png");

	sf::Texture door;
	door.loadFromFile("Door.png");

	sf::Texture enemyAlive;
	enemyAlive.loadFromFile("EnemyAlive.png");

	sf::Texture enemyDead;
	enemyDead.loadFromFile("EnemyDead.png");

	sf::Texture player;
	player.loadFromFile("Player.png");
	
	// Window size
	int windowx = 960;
	int windowy = 640;

	sf::RenderWindow window(sf::VideoMode(windowx, windowy), "Tile Thing");

	Tile tileArray[600];

	// Loop to create the tiles in 30x20 square
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 20; j++) {
			tileArray[(i * 20 + j)].CreateTile(32 * i, 32 * j);
		}
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Detection of mouse interaction (clicking)
			if (event.type == sf::Event::MouseButtonReleased)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
				
				// When mouse clicked the tile type changes ("ChangeTileType()")
				for (int i = 0; i < 600; i++)
				{
					if (tileArray[i].tile.getGlobalBounds().contains(mousePosF))
					{
						tileArray[i].ChangeTileType();
					}
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				// Print to console & save text of current level layout 
				if (event.key.code == sf::Keyboard::P)
				{
					ofstream myfile;
					myfile.open("levelEditor.txt");
					{
						for (int j = 0; j < 20; j++)
						{
							for (int i = 0; i < 30; i++)
							{
								myfile << tileArray[j + (i * 20)].tileType;
								cout << tileArray[j + (i * 20)].tileType;
							}
							cout << "\n";
							myfile << "\n";
						}
						myfile.close();
					}
				}

				// Loads "saved" level from text file
				if (event.key.code == sf::Keyboard::L)
				{
					string entireLevel[600];
					string level;
					ifstream myfile ("levelEditor.txt");

					if (myfile.is_open())
					{
						int levelCounter = 0;

						while (getline(myfile, level))
						{
							cout << level << '\n';

							if (levelCounter < 600) 
							{
								for (int i = 0; i < 30; i++)
								{
									entireLevel[levelCounter + i] = level.at(i);
								}

								levelCounter += 30;
							}
						}
						myfile.close();
					}

					for (int i = 0; i < 20; i++)
					{
						for (int j = 0; j < 30; j++)
						{
							tileArray[i + (j * 20)].tileType = stoi(entireLevel[j+(30*i)]);
						}
						cout << "\n";
					}
				}
			}

		 window.clear();

		// Switch with int tileType to display correct tiles
		for (int i = 0; i < 600; i++)
		{
			switch (tileArray[i].tileType)
			{
			case 0:
				tileArray[i].tile.setTexture(sky);
				break;
			case 1:
				tileArray[i].tile.setTexture(platform);
				break;
			case 2:
				tileArray[i].tile.setTexture(lava);
				break;
			}

		window.draw(tileArray[i].tile);
		}
		window.display();
		}
	}
return 0;
}


	//A mess of stuff I never got working or not using
		
		// Initial activity with rectangles rather than sprites
		//sf::RectangleShape tile;
		//tile.setSize(sf::Vector2f(100, 100));
		//tile.setFillColor(sf::Color::White);
		//tile.setOutlineColor(sf::Color::Red);
		//tile.setOutlineThickness(2.0f
		//bool clicked = false;

		//tileArray[i].clicked = !tileArray[i].clicked;

			/*if (tileArray[i].clicked)
			{
				tileArray[i].tile.setTexture(platform);
			}
			else
			{
				tileArray[i].tile.setTexture(sky);
			}*/

		// Tried to make a function that uses an int when click happens to change texture (didn't work)
		/*void ChangeTexture()
	{
		if (tileChoice = 1)
		{
			tile.setTexture(sf::Texture::sky)(sky.loadFromFile("BlockSky.png"));
		}
	}*/

		// This was another idea to switch the texture that will be used when a number is clicked before mouse click
		// ended up more complicated than I thought...
		/*switch (event.type)
{
case sf::Event::KeyPressed:
	if (sf::Keyboard::Num1)
	{

	}
	break;
}*/