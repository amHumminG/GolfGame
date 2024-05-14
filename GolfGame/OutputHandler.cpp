#include "OutputHandler.h"

// PRIVATE FUNCTIONS

void OutputHandler::print(std::string message)
{
	std::cout <<  message;
}

void OutputHandler::print(int value)
{
	std::cout << value;
}

void OutputHandler::print(unsigned int value)
{
	std::cout << value;
}

void OutputHandler::print(float value)
{
	std::cout << std::fixed << std::setprecision(2) << value;
}

void OutputHandler::printNL(std::string message)
{
	std::cout << message << std::endl;
}

void OutputHandler::newLine()
{
	std::cout << std::endl;
}

void OutputHandler::printFloat3(DirectX::XMFLOAT3 float3)
{
	print(float3.x); print(", ");
	print(float3.y); print(", ");
	print(float3.z);
}

void OutputHandler::printInt3(DirectX::XMINT3 int3)
{
	print(int3.x); print(", ");
	print(int3.y); print(", ");
	print(int3.z);
}

void OutputHandler::InputIntegerInRange(int min, int max)
{
	print("Please enter a valid number");
	print(" ("); print(min); print("-"); print(max); print("): ");
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

void OutputHandler::AskForSpinRate()
{
	newLine();
	print("Please select spin rate (backspin 0 - 6000 rpm): ");
}

void OutputHandler::InvalidInputSpinRate()
{
	print("Invalid spin rate. Please enter a valid spin rate (0 - 6000 rpm): ");
}

void OutputHandler::GameStartMessage()
{
	newLine();
	printNL("------------- Welcome to Golf Game -------------");
}

void OutputHandler::GameInfoMessage(DirectX::XMFLOAT3 ballLocation, DirectX::XMINT3 holeLocation, unsigned int par, unsigned int maxStartVelocity, float gravity, bool airDrag, DirectX::XMFLOAT3 WindSpeed)
{
	printNL("---------------------- GENERAL INFORMATION ----------------------");
	print("Gravity is set to: "); print(gravity); print("m/s^2"); newLine();
	if (airDrag)
	{
		printNL("Air drag is enabled");
		print("WindSpeed (m/s) is set to: "); printFloat3(WindSpeed); newLine();
	}
	else
	{
		printNL("Air drag is disabled");
	}
	print("Hole is located at: "); printInt3(holeLocation); newLine();
	print("Ball is located at: "); printFloat3(ballLocation); newLine();
	print("Par for this hole is: "); print(par); newLine();
	print("Total allowed starting velocity for each shot is "); print(maxStartVelocity); print(" m/s or less");
	newLine();
	printNL("Good luck!");
}

void OutputHandler::GameEndMessage(unsigned int strokes, unsigned int par)
{
	newLine();
	if (strokes == 1)
	{
		printNL("------------------------------------------------");
		printNL("Hole in one!");
		print("Par for this hole was: "); print(par); newLine();
		printNL("------------------------------------------------");
	}
	else if (strokes == par)
	{
		printNL("------------------------------------------------");
		printNL("Par! Nicely done.");
		printNL("Par for this hole was: "); print(par); newLine();
		printNL("------------------------------------------------");
	}
	else if (strokes < par)
	{
		printNL("------------------------------------------------");
		print("You have completed the hole in "); print(strokes); print(" strokes."); newLine();
		print("Par for this hole was: "); print(par); newLine();
		printNL("Impressive.");
		printNL("------------------------------------------------");
	}
	else if (strokes < par + 5)
	{
		printNL("------------------------------------------------");
		print("You have completed the hole in "); print(strokes); print(" strokes."); newLine();
		print("Par for this hole was: "); print(par); newLine();
		printNL("Not even close buddy.");
		printNL("------------------------------------------------");
	}
	else if (strokes < par + 10)
	{
		printNL("------------------------------------------------");
		print("You have completed the hole in "); print(strokes); print(" strokes."); newLine();
		print("Par for this hole was: "); print(par); newLine();
		printNL("Next time, aim for the hole.");
		printNL("------------------------------------------------");
	}
	else
	{
		printNL("------------------------------------------------");
		print("You have completed the hole in "); print(strokes); print(" strokes."); newLine();
		print("Par for this hole was: "); print(par); newLine();
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

void OutputHandler::PreStrokeInfo(unsigned int stroke, unsigned int par, DirectX::XMFLOAT3 ballLocation, DirectX::XMINT3 holeLocation, DirectX::XMFLOAT3 windSpeed)
{
	newLine();
	print("-------------- Stroke: "); print(stroke); print(" (Par: "); print(par); print(") --------------"); newLine();
	print("Ball location: "); printFloat3(ballLocation); newLine();
	print("Hole location: "); printInt3(holeLocation); newLine();
	print("Wind speed: "); printFloat3(windSpeed); newLine();
	printNL("------------------------------------------------");
	print("Please enter starting velocity for your next stroke <x y z>: ");
}

void OutputHandler::InvalidInputVelocity()
{
	print("Invalid input. Please enter a valid starting velocity <x y z>: ");
}

void OutputHandler::InvalidBallSpeed(float ballSpeed, float maxBallSpeed)
{
	print("Invalid ball speed: "); print(ballSpeed); print(" m/s (max: "); print(maxBallSpeed); print(" m/s) .Please enter a valid starting velocity <x y z> : ");
}

void OutputHandler::BallInfo(float t, DirectX::XMFLOAT3 ballPosition, DirectX::XMFLOAT3 ballSpeed)
{
	print("t = "); print(t);
	print(" | ");
	print("Pos: "); printFloat3(ballPosition);
	print(" | ");
	print("Speed: "); printFloat3(ballSpeed);
	newLine();
}

void OutputHandler::AskForReplay()
{
	print("Would you like to play again? (y/n): ");
}

void OutputHandler::ExitGameMessage()
{
	printNL("Exiting game. Thanks for playing!");
}