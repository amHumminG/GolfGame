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
