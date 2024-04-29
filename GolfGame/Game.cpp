#include "Game.h"

void Game::SetupGame()
{
	this->ball.SetPosition({ 0.0f, 0.0f, 0.0f });
	this->course.GenerateHole(100, 400, 1, 50);
}

void Game::StartGame()
{
	SetupGame();

	this->output.GameStartMessage();
	this ->output.SelectGravity();

	// Set gravity
	float gravity = 0;
	unsigned int gravityChoice = 1; // Default to Earth gravity
	bool validInput = false;
	while (!validInput)
	{
		validInput = this->input.GetGravity(gravityChoice);
		if (!validInput)
			this->output.InvalidGravity();
	}
	// cast gravityChoice to enum
	this->ball.SetGravity(static_cast<Gravity>(gravityChoice));

	this->output.GameInfoMessage(this->ball.GetPosition(), this->course.GetHoleLocation(), this->course.GetPar(), this->maxBallSpeed, this->ball.GetGravity());
}

void Game::Swing(unsigned int strokes)
{
	this->output.PreStrokeInfo(strokes, this->ball.GetPosition(), this->course.GetHoleLocation());

	DirectX::XMFLOAT3 v0;
	bool validInput = false;
	while (!validInput)
	{
		validInput = this->input.GetStartVelocity(v0);

		if (!validInput)
			this->output.InvalidInputVelocity();
		else
		{
			// Determine if length of v0 is greater than maxBallSpeed
			float length = pow(pow(v0.x, 2) + pow(v0.y, 2) + pow(v0.z, 2), 0.5f);
			if (length > this->maxBallSpeed)
			{
				this->output.InvalidBallSpeed(length);
				validInput = false;
			}
		}
	}

	bool ballHit = false;
	this->ball.SetVelocity(v0);
	this->output.BallInfo(this->ball.GetTime(), this->ball.GetPosition(), this->ball.GetVelocity());
	while (this->ball.GetPosition().y > 0.0f || !ballHit)
	{
		// Set ball velocity and calculate its projectile
		this->ball.CalculateProjectile();
		
		// Print ball information
		this->output.BallInfo(this->ball.GetTime(), this->ball.GetPosition(), this->ball.GetVelocity());
		ballHit = true;
	}
	
	// Updates the ball start position
	this->ball.SetPosition(this->ball.GetPosition());
}

bool Game::BallInHole()
{
	DirectX::XMFLOAT3 ballPos = ball.GetPosition();
	DirectX::XMINT3 holePos = course.GetHoleLocation();

	DirectX::XMFLOAT3 ballToHole = { ballPos.x - holePos.x, ballPos.y - holePos.y, ballPos.z - holePos.z };

	float length = pow(pow(ballToHole.x, 2) + pow(ballToHole.y, 2) + pow(ballToHole.z, 2), 0.5f);
	float holeRadius = this->course.GetHoleRadius();

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
		Swing(strokes);
		strokes++;
	}

	EndGame(strokes, par);
}
