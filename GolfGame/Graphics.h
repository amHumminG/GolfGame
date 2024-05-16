#pragma once

#include <DirectXMath.h>
#include <SFML/Graphics.hpp>

class Graphics
{
private:
	sf::RenderWindow window;
	sf::Event event; // An event to check if the window closes

	unsigned int wWidth = 960;
	unsigned int wHeight = 960;
	void DrawTextAndImage(const sf::String imagePath, const sf::String fontPath, const sf::String mainText, const sf::String subText);


public:
	Graphics() = default;
	//Graphics();

	void Initialize();
	void Run();
	void DrawTrajectory(DirectX::XMFLOAT3 position);

	void DrawTitleScreen();
	void DrawOutOfBoundsScreen();
	void DrawVictoryScreen();

	void CloseWindow();
};