#include "Game.h"

Game::Game()
{
	Initialize();
}

Game::Game(DirectX::XMINT3 courseBounds, DirectX::XMFLOAT3 startPos, float holeRadius, unsigned int maxSpeed, float updateFrequency, float gravity)
{
	Initialize(courseBounds, startPos, holeRadius, maxSpeed, updateFrequency, gravity);
}

void Game::Initialize(DirectX::XMINT3 courseBounds, DirectX::XMFLOAT3 startPos, float holeRadius, unsigned int maxSpeed, float updateFrequency, float gravity)
{
	this->input = InputHandler();
	this->output = OutputHandler();

	this->course = Course(courseBounds);

	// Change projectile creation so that we can set
	// gravity, updtate frequency, start position
	this->ball = Projectile();

	// Where do we set max ball speed?
}

void Game::Run()
{
	startGame();

	while (/* ball is not in hole */)
	{
		swing();
		update();
	}

	endGame();

	// maybe add a play again option?
}
