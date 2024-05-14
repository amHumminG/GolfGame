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
	while (this->window.isOpen())
	{
		this->CloseWindow();
	}
}