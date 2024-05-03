#include "Game.h"

void Game::SetupGame()
{
	this->ball.SetPosition({ 0.0f, 0.0f, 0.0f });
	this->course.GenerateHole(100, 400, 1, 50);
}

void Game::GetSettings()
{
	// Gravity
	this->output.SelectGravity();
	int gravityChoice = 1; // Default to Earth gravity
	bool validInput = false;
	while (!validInput)
	{
		validInput = this->input.GetIntInRange(gravityChoice, 1, 5);
		if (!validInput)
			this->output.InvalidInputGravity();
	}
	this->ball.SetGravity(static_cast<Gravity>(gravityChoice));

	// Air Drag
	this->output.AskForAirDrag();
	bool airDrag = true;
	validInput = false;
	while (!validInput)
	{
		validInput = this->input.GetYesOrNo(airDrag);
		if (!validInput)
			this->output.InvalidInputYesOrNo();
	}
	this->ball.SetAirDrag(airDrag);

	if (airDrag)
	{
		this->output.SelectWindSpeed();
		int windSpeed = 1;	// Default to no wind
		validInput = false;
		while (!validInput)
		{
			validInput = this->input.GetIntInRange(windSpeed, 1, 8);
			if (!validInput)
				this->output.InvalidInputWindSpeed();
		}
		this->ball.SetWindSpeed(static_cast<WindSpeed>(windSpeed));
	}
}

void Game::StartGame()
{
	this->output.GameStartMessage();
	SetupGame();
	GetSettings();

	this->output.GameInfoMessage
	(
		this->ball.GetPosition(), 
		this->course.GetHoleLocation(), 
		this->course.GetPar(), 
		this->maxBallSpeed, 
		this->ball.GetGravity()
	);
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
		if (!validInput)
			this->output.InvalidInputYesOrNo();
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
	this->course.GetPar();

	while (!this->BallInHole())
	{
		Swing(strokes);
		strokes++;
	}

	EndGame(strokes, this->course.GetPar());
}
