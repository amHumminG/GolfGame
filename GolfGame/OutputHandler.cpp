#include "OutputHandler.h"

// PRIVATE FUNCTIONS

void OutputHandler::print(std::string message)
{
	std::cout << message;
}

void OutputHandler::printNL(std::string message)
{
	std::cout << message << std::endl;
}

void OutputHandler::newLine()
{
	std::cout << std::endl;
}

std::string OutputHandler::float3ToString(DirectX::XMFLOAT3 float3)
{
	return std::to_string(float3.x) + ", " + std::to_string(float3.y) + ", " + std::to_string(float3.z);
}

std::string OutputHandler::int3ToString(DirectX::XMINT3 int3)
{
	return std::to_string(int3.x) + ", " + std::to_string(int3.y) + ", " + std::to_string(int3.z);
}


// PUBLIC FUNCTIONS

void OutputHandler::GameStartMessage(DirectX::XMINT3 holeLocation, unsigned int par, unsigned int maxStartVelocity)
{
	newLine();
	printNL("------------- Welcome to Golf Game -------------");
	printNL("Hole is located at: " + int3ToString(holeLocation));
	printNL("Total allowed starting velocity is " + std::to_string(maxStartVelocity) + "m/s or less");
	printNL("Par for this hole is: " + std::to_string(par));
	printNL("Good luck!");
	newLine();
}

void OutputHandler::GameEndMessage(unsigned int strokes, unsigned int par)
{
	newLine();
	if (strokes > 1)
	{
		printNL("------------------------------------------------");
		printNL("Congratulations! You have completed the hole in " + std::to_string(strokes) + " strokes.");
		printNL("Par for this hole was: " + std::to_string(par));
		printNL("------------------------------------------------");
	}
	else
	{
		printNL("------------------------------------------------");
		printNL("Hole in one! Impressive.");
		printNL("Par for this hole was: " + std::to_string(par));
		printNL("------------------------------------------------");
	}
}

void OutputHandler::BallOutOfBounds()
{
	printNL("-----------------------------------------------");
	printNL("Game over! Ball is out of bounds");
	printNL("Are you even trying?");
	printNL("-----------------------------------------------");
}

void OutputHandler::PreStrokeInfo(unsigned int stroke, DirectX::XMFLOAT3 ballLocation, DirectX::XMINT3 holeLocation)
{
	printNL("-------------- Stroke: " + std::to_string(stroke) + "--------------");
	printNL("Ball location: " + float3ToString(ballLocation));
	printNL("Hole location: " + int3ToString(holeLocation));
	printNL("------------------------------------------------");
	print("Please enter starting velocity for your next stroke <x y z>: ");
}

void OutputHandler::InvalidInput()
{
	print("Invalid input. Please enter a valid starting velocity <x y z>: ");
}

void OutputHandler::InvalidBallSpeed(float ballSpeed)
{
	print("Invalid ball speed: " + std::to_string(ballSpeed) + ". Please enter a valid starting velocity <x y z>: ");
}

void OutputHandler::BallInfo(float t, DirectX::XMFLOAT3 ballPosition, DirectX::XMFLOAT3 ballSpeed)
{
	print("t = " + std::to_string(t));
	print("Pos: " + float3ToString(ballPosition));
	print("  ");
	printNL("Speed: " + float3ToString(ballSpeed));
}