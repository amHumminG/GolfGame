#pragma once

#include "InputHandler.h"
#include "OutputHandler.h"

#include "Course.h"
#include "Projectile.h"

class Game
{
private:
	
	InputHandler input;
	OutputHandler output;

	Course course;
	Projectile ball;

	float maxBallSpeed;

	void SetupGame();
	void GetSettings();
	void StartGame();
	void Swing(unsigned int strokes);
	void EndGame(unsigned int strokes, unsigned int par);

	bool BallInHole();
	bool BallInBounds();

public:

	Game();
	Game
	(
		DirectX::XMINT2 courseBounds = { 1000, 1000 },
		DirectX::XMFLOAT3 startPos = { 0.0f, 0.0f, 0.0f },
		float holeRadius = 1.0f,
		unsigned int maxSpeed = 50,
		float updateFrequency = 0.1f
	);
	~Game() = default;

	void Initialize
	(
		DirectX::XMINT2 courseBounds = { 1000, 1000 }, 
		DirectX::XMFLOAT3 startPos = { 0.0f, 0.0f, 0.0f },
		float holeRadius = 1.0f,
		unsigned int maxSpeed = 50, 
		float updateFrequency = 0.1f
	);

	void Run();
	void RepeatPlay();

	void RunDebug(Gravity gravity, bool airDrag, DirectX::XMFLOAT3 wind);
};