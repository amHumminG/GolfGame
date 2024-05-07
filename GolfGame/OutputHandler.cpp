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

void OutputHandler::InputIntegerInRange(int min, int max)
{
	print("Please enter a valid number");
	print(" (" + std::to_string(min) + "-" + std::to_string(max) + "): ");
}


// PUBLIC FUNCTIONS

void OutputHandler::AskForAirDrag()
{
	print("Would you like to enable air drag? (y/n): ");
}

void OutputHandler::InvalidInputYesOrNo()
{
	print("Invalid input. Please enter 'y' or 'n': ");
}

void OutputHandler::SelectGravity()
{
	printNL("Please select gravity: ");
	printNL("1. Earth (9.81 m/s^2)");
	printNL("2. Moon (1.62 m/s^2)");
	printNL("3. Mars (3.71 m/s^2)");
	printNL("4. Jupiter (24.79 m/s^2)");
	printNL("5. Venus (8.87 m/s^2)");

	print("Enter a number (1-5): ");
}

void OutputHandler::InvalidInputGravity()
{
	print("Invalid gravity. ");
	InputIntegerInRange(1, 5);
}

void OutputHandler::SelectWindSpeed()
{
	newLine();
	printNL("Please select wind speed: ");
	printNL("1. Calm (0.0) m/s");
	printNL("2. Light (0.1 - 3.3) m/s");
	printNL("3. Moderate (3.4 - 7.9) m/s");
	printNL("4. Strong (8.0 - 13.8) m/s");
	printNL("5. Very strong (13.9 - 24.4) m/s");
	printNL("6. Storm (24.5 - 32.6) m/s");
	printNL("7. Tornado (32.7 - 40.0) m/s");
	printNL("8. Random (0.0 - 40.0) m/s");
	
	print("Enter a number (1-8): ");
}

void OutputHandler::InvalidInputWindSpeed()
{
	print("Invalid wind speed. ");
	InputIntegerInRange(1, 8);
}


void OutputHandler::GameStartMessage()
{
	newLine();
	printNL("------------- Welcome to Golf Game -------------");
}

void OutputHandler::GameInfoMessage(DirectX::XMFLOAT3 ballLocation, DirectX::XMINT3 holeLocation, unsigned int par, unsigned int maxStartVelocity, float gravity, bool airDrag, DirectX::XMFLOAT3 WindSpeed)
{
	printNL("---------------------- GENERAL INFORMATION ----------------------");
	printNL("Gravity is set to: " + std::to_string(gravity) + "m/s^2");
	if (airDrag)
	{
		printNL("Air drag is enabled");
		printNL("WindSpeed (m/s) is set to: " + float3ToString(WindSpeed));
	}
	else
	{
		printNL("Air drag is disabled");
	}
	printNL("Hole is located at: " + int3ToString(holeLocation));
	printNL("Ball is located at: " + float3ToString(ballLocation));	
	printNL("Par for this hole is: " + std::to_string(par));
	printNL("Total allowed starting velocity for each shot is " + std::to_string(maxStartVelocity) + "m/s or less");
	newLine();
	printNL("Good luck!");
	newLine();
}

void OutputHandler::GameEndMessage(unsigned int strokes, unsigned int par)
{
	newLine();
	if (strokes == 1)
	{
		printNL("------------------------------------------------");
		printNL("Hole in one!");
		printNL("Par for this hole was: " + std::to_string(par));
		printNL("------------------------------------------------");
	}
	else if (strokes == par)
	{
		printNL("------------------------------------------------");
		printNL("Par! Nicely done.");
		printNL("Par for this hole was: " + std::to_string(par));
		printNL("------------------------------------------------");
	}
	else if (strokes < par)
	{
		printNL("------------------------------------------------");
		printNL("You have completed the hole in " + std::to_string(strokes) + " strokes.");
		printNL("Par for this hole was: " + std::to_string(par));
		printNL("Impressive.");
		printNL("------------------------------------------------");
	}
	else if (strokes < par + 5)
	{
		printNL("------------------------------------------------");
		printNL("You have completed the hole in " + std::to_string(strokes) + " strokes.");
		printNL("Par for this hole was: " + std::to_string(par));
		printNL("Not even close buddy.");
		printNL("------------------------------------------------");
	}
	else if (strokes < par + 10)
	{
		printNL("------------------------------------------------");
		printNL("You have completed the hole in " + std::to_string(strokes) + " strokes.");
		printNL("Par for this hole was: " + std::to_string(par));
		printNL("Next time, aim for the hole.");
		printNL("------------------------------------------------");
	}
	else
	{
		printNL("------------------------------------------------");
		printNL("You have completed the hole in " + std::to_string(strokes) + " strokes.");
		printNL("Par for this hole was: " + std::to_string(par));
		printNL("You should probably consider another hobby.");
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

void OutputHandler::InvalidInputVelocity()
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
	print(" | ");
	print("Pos: " + float3ToString(ballPosition));
	print(" | ");
	printNL("Speed: " + float3ToString(ballSpeed));
}

void OutputHandler::AskForReplay()
{
	print("Would you like to play again? (y/n): ");
}

void OutputHandler::ExitGameMessage()
{
	printNL("Exiting game. Thanks for playing!");
}