#pragma once

#include <iostream>
#include <string>
#include "DirectXMath.h"

class InputHandler
{
private:

	std::string ReadInput();
	bool validateFloatInput(std::string input);
	bool validateIntInput(std::string input);
	float convertToFloat(std::string input);
	int convertToInt(std::string input);

public:

	InputHandler() = default;
	~InputHandler() = default;

	bool GetStartVelocity(DirectX::XMFLOAT3& startVelocity);
	bool GetGravity(unsigned int& gravityIndex);
};
