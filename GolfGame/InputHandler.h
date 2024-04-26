#pragma once

#include <iostream>
#include <string>
#include "DirectXMath.h"

class UserInput
{
private:

	std::string RecieveInput();
	bool validateFloatInput(std::string input);
	bool validateIntInput(std::string input);
	float convertToFloat(std::string input);
	int convertToInt(std::string input);

public:

	UserInput() = default;
	~UserInput() = default;

	bool GetStartVelocity(DirectX::XMFLOAT3& startVelocity);
	bool GetGravity(unsigned int& gravityIndex);
};
