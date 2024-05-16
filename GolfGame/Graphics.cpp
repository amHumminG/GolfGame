#include "Graphics.h"

void Graphics::CloseWindow()
{
	while (this->window.pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window.close();
	}
}

void Graphics::Initialize()
{
	this->window.create(sf::VideoMode(this->wWidth, this->wHeight), "Golf Game");
	this->window.setPosition(sf::Vector2i(this->wWidth - 10, 0));
}

void Graphics::DrawTrajectory(DirectX::XMFLOAT3 position, unsigned int colorIndex, DirectX::XMINT3 holePos)
{
	float circleRadius = 3.0f;
	sf::CircleShape circleX(circleRadius); // Ball in xy-axis
	sf::CircleShape circleZ(circleRadius); // Ball in zy-axis
	circleX.setFillColor(this->ballColors[colorIndex % 7]);
	circleZ.setFillColor(this->ballColors[colorIndex % 7]);

	unsigned int circleOffset = 200;
	sf::Vector2f circlePosX(circleOffset + position.x, this->wWidth / 2 - 2 * circleRadius - position.y);
	circleX.setPosition(circlePosX);
	sf::Vector2f circlePosZ(circleOffset + position.z, this->wHeight - 2 * circleRadius - position.y);
	circleZ.setPosition(circlePosZ);

	sf::RectangleShape line(sf::Vector2f(this->wHeight, 1)); // Horisontal line
	line.setFillColor(sf::Color::White);
	line.setPosition(sf::Vector2f(0, 960 / 2));

	this->window.clear(this->backgroundColor);
	this->window.draw(circleX);
	this->window.draw(circleZ);
	this->window.draw(line);
	
	this->DrawFlag(holePos);

	this->window.display();
}

void Graphics::DrawFlag(DirectX::XMINT3 holePos)
{
	unsigned int poleHeight = 50;
	unsigned int flagSize = 10;
	sf::RectangleShape flagPoleX(sf::Vector2f(1, poleHeight));
	sf::RectangleShape flagPoleZ(sf::Vector2f(1, poleHeight));
	sf::CircleShape flagX(flagSize);
	sf::CircleShape flagZ(flagSize);
	flagPoleX.setFillColor(sf::Color::White);
	flagPoleZ.setFillColor(sf::Color::White);
	flagX.setFillColor(sf::Color::Red);
	flagZ.setFillColor(sf::Color::Red);
	flagX.setPointCount(3);
	flagZ.setPointCount(3);

	unsigned int offset = 200;
	flagPoleX.setPosition(sf::Vector2f(offset + holePos.x, 960 / 2 - poleHeight));
	flagPoleZ.setPosition(sf::Vector2f(offset + holePos.z, this->wHeight - poleHeight));
	flagX.setPosition(sf::Vector2f(offset + holePos.x + 2 * flagSize, 960 / 2 - poleHeight));
	flagZ.setPosition(sf::Vector2f(offset + holePos.z + 2 * flagSize, this->wHeight - poleHeight));

	int rotate = 90;
	flagX.setRotation(rotate);
	flagZ.setRotation(rotate);

	this->window.draw(flagPoleX);
	this->window.draw(flagPoleZ);
	this->window.draw(flagX);
	this->window.draw(flagZ);
}

void Graphics::DrawTextAndImage(const sf::String imagePath, const sf::String fontPath, const sf::String mainText, const sf::String subText)
{
	// IMAGE
	sf::Texture texture;
	if (!texture.loadFromFile(imagePath))
		this->window.close();

	texture.setSmooth(true);

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(1.0f, 1.0f);
	int xPos = 960 / 2 - sprite.getLocalBounds().width / 2;
	int yPos = 960 / 2 - sprite.getLocalBounds().height / 2;
	sprite.setPosition(xPos, yPos + 200);
		

	// TEXT
	int textYOffset = -200;

	sf::Font font;
	if (!font.loadFromFile(fontPath))
		this->window.close();

	sf::Text titleText;
	titleText.setFont(font);
	titleText.setString(mainText);
	titleText.setFillColor(this->textColor);
	titleText.setStyle(sf::Text::Bold);
	titleText.setCharacterSize(80);
	xPos = 960 / 2 - titleText.getLocalBounds().width / 2;
	yPos = 960 / 2 - titleText.getLocalBounds().height / 2;
	titleText.setPosition(xPos, yPos + textYOffset);

	sf::Text infoText;
	infoText.setFont(font);
	infoText.setString(subText);
	infoText.setFillColor(this->textColor);
	infoText.setStyle(sf::Text::Italic);
	infoText.setCharacterSize(20);
	xPos = 960 / 2 - infoText.getLocalBounds().width / 2;
	yPos = 960 / 2 - infoText.getLocalBounds().height / 2;
	infoText.setPosition(xPos, yPos + textYOffset + 90);


	// DRAW
	this->window.clear(this->backgroundColor);
	this->window.draw(sprite);
	this->window.draw(titleText);
	this->window.draw(infoText);

	this->window.display();
}

void Graphics::DrawTitleScreen()
{
	this->DrawTextAndImage("Resources/title.png", "Resources/Akira.otf", "Golf Game", "Use console window to play");
}

void Graphics::DrawOutOfBoundsScreen()
{
	this->DrawTextAndImage("Resources/gameover.png", "Resources/Akira.otf", "Out of Bounds", "Ok. That was horrible.");
}

void Graphics::DrawVictoryScreen()
{
	this->DrawTextAndImage("Resources/victory.png", "Resources/Akira.otf", "Victory", "Good job!");
}
