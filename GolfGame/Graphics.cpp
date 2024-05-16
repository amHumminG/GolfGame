#include "Graphics.h"

void Graphics::CloseWindow()
{
	while (this->window.pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window.close();
	}
}

void Graphics::Run()
{

	// do this is game class
	while (this->window.isOpen())
	{
		this->CloseWindow();
	}
}

void Graphics::Initialize()
{
	this->window.create(sf::VideoMode(this->wWidth, this->wHeight), "Golf Game");
	window.setPosition(sf::Vector2i(1920/2 - 10, 0));
}

void Graphics::DrawTrajectory(DirectX::XMFLOAT3 position)
{
	float circleRadius = 3.0f;
	sf::CircleShape circle1(circleRadius);
	sf::CircleShape circle2(circleRadius);
	circle1.setFillColor(sf::Color::Red);
	circle2.setFillColor(sf::Color::Green);

	sf::RectangleShape line(sf::Vector2f(wWidth, 1));
	line.setFillColor(sf::Color::White);
	line.setPosition(sf::Vector2f(0, wHeight / 2));
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



