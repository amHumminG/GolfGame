#pragma once

#include "InputHandler.h"
#include "OutputHandler.h"

#include "Course.h"
#include "Projectile.h"

enum Gravity
{
	EARTH = 1,
	MOON = 2,
	MARS = 3,
	JUPITER = 4,
	VENUS = 5
};

class Game
{
private:
	
	InputHandler input;
	OutputHandler output;

	Course course;
	Projectile ball;

	float maxBallSpeed;

	void StartGame();
	void Swing();
	void EndGame(unsigned int strokes, unsigned int par);

	bool BallInHole();

public:

	Game();
	Game
	(
		DirectX::XMINT3 courseBounds = { 1000, 0, 1000 },
		DirectX::XMFLOAT3 startPos = { 0.0f, 0.0f, 0.0f },
		float holeRadius = 1.0f,
		unsigned int maxSpeed = 50,
		float updateFrequency = 0.1f
	);
	~Game() = default;

	void Initialize
	(
		DirectX::XMINT3 courseBounds = { 1000, 0, 1000 }, 
		DirectX::XMFLOAT3 startPos = { 0.0f, 0.0f, 0.0f },
		float holeRadius = 1.0f,
		unsigned int maxSpeed = 50, 
		float updateFrequency = 0.1f
	);

	void Run();
	void RepeatPlay();
};