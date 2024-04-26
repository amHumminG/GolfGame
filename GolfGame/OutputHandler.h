#pragma once

#include <iostream>
#include <DirectXMath.h>
#include <string>

class OutputHandler
{
private:

	void print(std::string message);
	void printNL(std::string message);
	void newLine();

	std::string float3ToString(DirectX::XMFLOAT3 float3);
	std::string int3ToString(DirectX::XMINT3 int3);

public:

	OutputHandler() = default;
	~OutputHandler() = default;

	void SelectGravity();
	void InvalidGravity();

	void GameStartMessage();
	void GameInfoMessage(DirectX::XMFLOAT3 ballLocation, DirectX::XMINT3 holeLocation, unsigned int par, unsigned int maxStartVelocity, float gravity);
	void GameEndMessage(unsigned int strokes, unsigned int par);
	void BallOutOfBounds();
	void AskForReplay();
	void ExitGameMessage();

	void PreStrokeInfo(unsigned int strokes, DirectX::XMFLOAT3 ballLocation, DirectX::XMINT3 holeLocation);

	void InvalidInputVelocity();
	void InvalidBallSpeed(float ballSpeed);

	void BallInfo(float t, DirectX::XMFLOAT3 ballLocation, DirectX::XMFLOAT3 ballSpeed);
};