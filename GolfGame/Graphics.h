#pragma once

#include <DirectXMath.h>
#include <SFML/Graphics.hpp>

class Graphics
{
private:
	sf::RenderWindow window;
	sf::Event event; // An event to check if the window closes

	unsigned int wWidth;
	unsigned int wHeight;

public:
	Graphics() = default;
	//Graphics();

	void Initialize(unsigned int width, unsigned int height);
	void Run();
	void DrawTitleScreen();
	void DrawGameOver();
	void DrawTrajectory(DirectX::XMFLOAT3 position);

	void CloseWindow();
};