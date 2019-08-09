#pragma once

int main()
{
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

	int windowx = 160;
	int windowy = 160;

	sf::RenderWindow window(sf::VideoMode(windowx, windowy), "Tile Thing");

	Tile tileArray[25];

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++) {
			tileArray[(i * 5 + j)].CreateTile(32 * j, 32 * i);
		}
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonReleased)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

				for (int i = 0; i < 25; i++)
				{
					if (tileArray[i].tile.getGlobalBounds().contains(mousePosF))
					{
						tileArray[i].clicked = !tileArray[i].clicked;
					}
				}
			}

			/*if (event.type == sf::Event::KeyPressed)
			{
			if (event.key.code == sf::Keyboard::P)
			{
			for (int i = 0; i < 5; i++)
			{
			for (int j = 0; j < 5; j++) {
			if (tileArray[(i * 5) + j].clicked)
			{
			cout << "1 ";
			}
			else
			{
			cout << "0 ";
			}
			}
			cout << "\n";
			}
			}
			}*/

			enum Textures { Sky, Platform, Lava, Coin, Door, EnemyAlive, EnemyDead, Player };
			Textures currentTexture;

			switch (currentTexture)
			{
			case Textures.Sky:

			}
			window.clear();

			for (int i = 0; i < 25; i++)
			{
				if (tileArray[i].clicked)
				{
					tileArray[i].tile.setTexture(platform);
					//tileArray[i].tile.setFillColor(sf::Color::Black);
				}
				else
				{
					tileArray[i].tile.setTexture(sky);
					//tileArray[i].tile.setFillColor(sf::Color::White);
				}
				window.draw(tileArray[i].tile);
			}
			window.display();
		}
	}
	return 0;
}
