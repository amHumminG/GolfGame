#include "Game.h"

void Game::StartGame()
{
	this->output.GameStartMessage();
	this ->output.SelectGravity();

	// Set gravity
	float gravity = 0;
	unsigned int gravityChoice = 1; // Default to Earth gravity
	bool validInput = false;
	while (!validInput)
	{
		validInput = this->input.GetGravity(gravityChoice);
	}

	switch(gravityChoice)
	{
	case Gravity::EARTH:
		gravity = 9.81f;
		break;

	case Gravity::MOON:
		gravity = 1.62f;
		break;

	case Gravity::MARS:
		gravity = 3.71f;
		break;

	case Gravity::JUPITER:
		gravity = 24.79f;
		break;

	case Gravity::VENUS:
		gravity = 8.87f;
		break;
	}

	this->ball.SetGravity(gravity);

	this->output.GameInfoMessage(this->ball.GetPosition(), this->course.GetlocationHole(), this->course.GetPar(), this->maxBallSpeed, gravity);
}

void Game::Swing()
{
	this->output.PreStrokeInfo(0, this->ball.GetPosition(), this->course.GetlocationHole());

	DirectX::XMFLOAT3 v0;
	bool validInput = false;
	while (!validInput)
	{
		validInput = this->input.GetStartVelocity(v0);

		if (!validInput)
			this->output.InvalidInputVelocity();
		else
		{
			// determine if length of v0 is greater than maxBallSpeed
			float length = pow(pow(v0.x, 2) + pow(v0.y, 2) + pow(v0.z, 2), 0.5f);
			if (length > this->maxBallSpeed)
			{
				this->output.InvalidBallSpeed(length);
				validInput = false;
			}
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
	DirectX::XMINT3 holePos = course.GetlocationHole();

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
	this->output.AskForReplay();
	bool replay;
	bool validInput = false;
	while (!validInput)
	{
		validInput = this->input.GetYesOrNo(replay);
	}

	if (replay)
	{
		Run();
	}
	else
	{
		this->output.ExitGameMessage();
	}
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
