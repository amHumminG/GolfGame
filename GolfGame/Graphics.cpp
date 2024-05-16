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

void Graphics::Initialize(unsigned int width, unsigned int height)
{
	this->window.create(sf::VideoMode(width, height), "Golf Game");
	window.setPosition(sf::Vector2i(960 - 10, 0));
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