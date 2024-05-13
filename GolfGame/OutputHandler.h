#pragma once

#include <iostream>
#include <iomanip>
#include <DirectXMath.h>
#include <string>

class OutputHandler
{
private:

	void print(std::string message);
	void print(int value);
	void print(unsigned int value);
	void print(float value);
	void printNL(std::string message);
	void newLine();

	void printFloat3(DirectX::XMFLOAT3 float3);
	void printInt3(DirectX::XMINT3 int3);

	void InputIntegerInRange(int min, int max);


public:

	OutputHandler() = default;
	~OutputHandler() = default;

	// Yes or No
	void AskForAirDrag();
	void AskForReplay();

	void InvalidInputYesOrNo();

	// Settings
	void SelectGravity();
	void InvalidInputGravity();
	void SelectWindSpeed();
	void InvalidInputWindSpeed();
	void SelectSpinRate();
	void InvalidInputSpinRate();

	void GameStartMessage();
	void GameInfoMessage
	(
		DirectX::XMFLOAT3 ballLocation, 
		DirectX::XMINT3 holeLocation, 
		unsigned int par, 
		unsigned int maxStartVelocity, 
		float gravity,
		bool airDrag,
		DirectX::XMFLOAT3 windSpeed
	);
	void GameEndMessage(unsigned int strokes, unsigned int par);
	void BallOutOfBounds();

	void ExitGameMessage();

	void PreStrokeInfo(unsigned int strokes, unsigned int par, DirectX::XMFLOAT3 ballLocation, DirectX::XMINT3 holeLocation, DirectX::XMFLOAT3 windSpeed);

	void InvalidInputVelocity();
	void InvalidBallSpeed(float ballSpeed, float maxBallSpeed);

	void BallInfo(float t, DirectX::XMFLOAT3 ballLocation, DirectX::XMFLOAT3 ballSpeed);
};