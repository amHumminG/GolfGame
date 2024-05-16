#pragma once

#include <DirectXMath.h>
#include <SFML/Graphics.hpp>

class Graphics
{
private:
	sf::Event event; // An event to check if the window closes
	sf::Color ballColors[7] = { sf::Color::Red, sf::Color(255, 128, 0), sf::Color::Yellow, sf::Color::Green,
		sf::Color(0, 255, 255), sf::Color::Blue, sf::Color(255, 0, 255) };

	unsigned int wWidth = 960;
	unsigned int wHeight = 960;

	sf::Color textColor = sf::Color::White;
	sf::Color backgroundColor = sf::Color::Black;

	sf::RenderTexture renderTexture;
	sf::RenderTexture renderTextureTrajectory;
	sf::Sprite windowSprite;

	void DrawTextAndImage(const sf::String imagePath, const sf::String fontPath, const sf::String mainText, const sf::String subText);

public:
	sf::RenderWindow window;

	Graphics() = default;
	~Graphics() = default;

	void Initialize();
	void Reset(); // clears trajectory RenderTexture for a new game

	void DrawTrajectory(DirectX::XMFLOAT3 position, unsigned int colorIndex, DirectX::XMINT3 holePos);
	void DrawFlag(DirectX::XMINT3 position);
	void DrawTitleScreen();
	void DrawOutOfBoundsScreen();
	void DrawVictoryScreen();

	void CloseWindow();
};