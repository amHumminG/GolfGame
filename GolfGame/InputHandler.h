#pragma once

#include <iostream>
#include <string>
#include "DirectXMath.h"

class InputHandler
{
private:

	std::string ReadInput();
	bool validateCharInput(std::string input);
	bool validateFloatInput(std::string input);
	bool validateIntInput(std::string input);

	char convertToChar(std::string input);
	float convertToFloat(std::string input);
	int convertToInt(std::string input);

public:

	InputHandler() = default;
	~InputHandler() = default;

	bool GetStartVelocity(DirectX::XMFLOAT3& startVelocity);
	bool GetIntInRange(int& input, int min, int max);
	bool GetYesOrNo(bool& question);
};
