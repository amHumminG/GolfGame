#include "Game.h"

void Game::StartGame()
{

}

void Game::Swing()
{
	DirectX::XMFLOAT3 v0;
	bool validShot = false;
	while (!validShot)
	{
		validShot = this->input.GetStartVelocity(v0);
		if (!validShot);
		{
			std::cout << "Invalid velocity!\n";
		}
	}

	while (this->ball.GetPosition().y >= 0.0f)
	{
		// Set ball velocity and calculate its projectile
		this->ball.SetVelocity(v0);
		this->ball.CalculateProjectile();
		
		// Print ball information
		this->output.BallInfo(this->ball.GetTime(), this->ball.GetPosition(), this->ball.GetVelocity());
	}
	
	// Updates the ball start position
	this->ball.SetPosition(this->ball.GetPosition());
}

bool Game::BallInHole()
{
	DirectX::XMFLOAT3 ballPos = ball.GetPosition();
	DirectX::XMFLOAT3 holePos = course.GetlocationHole();

	DirectX::XMFLOAT3 ballToHole = { ballPos.x - holePos.x, ballPos.y - holePos.y, ballPos.z - holePos.z };

	float length = pow(pow(ballToHole.x, 2) + pow(ballToHole.y, 2) + pow(ballToHole.z, 2), 0.5f);
	float holeRadius = this->course.GetradiusHole();

	return length <= holeRadius;
}

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
	this->ball.SetPosition(startPos);
	this->ball.SetUpdateFrequency(updateFrequency);

	this->maxBallSpeed = maxSpeed;
}

void Game::EndGame(unsigned int strokes, unsigned int par)
{
	this->output.GameEndMessage(strokes, par);
}

void Game::RepeatPlay()
{
	//Ask player if he want to repeat the game

	// if true
	//Start the game (start the beginning screen);

	//else;
	//thanks for playing (close the screen)
}

void Game::Run()
{
	StartGame();
	unsigned int strokes = 0;
	unsigned int par = 7; // this->course.GetPar();

	while (!this->BallInHole())
	{
		Swing();
		strokes++;
	}

	EndGame(strokes, par);
}
