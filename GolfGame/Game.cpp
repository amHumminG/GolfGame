#include "Game.h"

Game::Game()
{
	Initialize();
}

Game::Game(DirectX::XMINT3 courseBounds, DirectX::XMFLOAT3 startPos, float holeRadius, unsigned int maxSpeed, float updateFrequency)
{
	Initialize(courseBounds, startPos, holeRadius, maxSpeed, updateFrequency);
}

void Game::Initialize(DirectX::XMINT3 courseBounds, DirectX::XMFLOAT3 startPos, float holeRadius, unsigned int maxSpeed, float updateFrequency)
{
	this->input = InputHandler();
	this->output = OutputHandler();

	this->course = Course(courseBounds);

	// Change projectile creation so that we can set
	// gravity, updtate frequency, start position
	this->ball = Projectile();

	// Where do we set max ball speed?
}

void Game::endGame(unsigned int strokes, unsigned int par)
{
	GameEndMessage(strokes, par);
}

void Game::RepeatPlay(std::string Yes, std::string No)
{
	//Ask player if he want to repeat the game

	// if true
	//Start the game (start the beginning screen);

	//else;
	//thanks for playing (close the screen)
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
