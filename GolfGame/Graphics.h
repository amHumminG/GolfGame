#pragma once

#include <SFML/Graphics.hpp>

class Graphics
{
private:
	sf::RenderWindow window;
	sf::Event event; // An event to check if the window closes

	void CloseWindow();

public:
	Graphics() = default;
	//Graphics();

	void Initialize();
	void Run();
};