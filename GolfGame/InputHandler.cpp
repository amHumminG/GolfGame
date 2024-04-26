#include "InputHandler.h"

// PRIVATE FUNCTIONS

std::string InputHandler::ReadInput()
{
    std::string input;
    std::getline(std::cin, input);

    return input;
}

bool InputHandler::validateCharInput(std::string input)
{
	// length of 0 is invalid
	if (input.length() == 0)
		return false;

	// Check each character to ensure it is a character from a-z
	for (int i = 0; i < input.length(); i++)
	{
		if (!isalpha(input[i]))
			return false;
	}

	return true;
}

// Validates the input to ensure that it only contains numberic characters in the form of a float
bool InputHandler::validateFloatInput(std::string input)
{
    // length of 0 is invalid
    if (input.length() == 0)
		return false;

    // Only one decimal point is allowed
    if (input.find_first_of('.') != input.find_last_of('.'))
        return false;

    // Check each character to ensure it is a digit or a decimal point
    for (int i = 0; i < input.length(); i++)
    {
		if (!isdigit(input[i]) && input[i] != '.' && input[i] != '-')
			return false;
	}

    return true;
}

// Validates the input to ensure that it only contains numberic characters in the form of an integer
bool InputHandler::validateIntInput(std::string input)
{
	// length of 0 is invalid
	if (input.length() == 0)
		return false;

	// Check each character to ensure it is a digit
	for (int i = 0; i < input.length(); i++)
	{
		if (!isdigit(input[i]) && input[i] != '-')
			return false;
	}

	return true;
}

// Converts a string with length 1 to a char
char InputHandler::convertToChar(std::string input)
{
	return input[0];
}

// Converts a string to a float
float InputHandler::convertToFloat(std::string input)
{
    if (input.back() == '.')
		input.pop_back();

	return std::stof(input);
}

int InputHandler::convertToInt(std::string input)
{
	return std::stoi(input);
}



// PUBLIC FUNCTIONS

// Obtains the start velocity vector from the input stream
bool InputHandler::GetStartVelocity(DirectX::XMFLOAT3& startVelocity)
{
    float arr[3] = { 0.0f, 0.0f, 0.0f };
    unsigned int arrSize = 0;

    std::string input = ReadInput();

    // Validate and convert the input to float values
    std::string num;
    for (int i = 0; i < input.length()+1; i++)
    {
        if (arrSize == 3)
			break;

        if (input[i] != ' ' && i != input.length())
        {
            num += input[i];
		}
        else
        {
			if (!validateFloatInput(num))
				return false;
            
			arr[arrSize] = convertToFloat(num);
			arrSize++;
			num.clear();
		}
	}

    // Check if the xyz values are filled
    if (arrSize < 3)
        return false;

    startVelocity = DirectX::XMFLOAT3(arr[0], arr[1], arr[2]);
    return true;
}

bool InputHandler::GetGravity(unsigned int& gravityIndex)
{
	std::string input = ReadInput();

	if (!validateIntInput(input))
		return false;

	int value = convertToInt(input);

	// Check if the value is within the valid range 1-5
	if (value < 0 || value > 5)
		return false;

	gravityIndex = value;
	return true;
}

// Obtains a yes or no answer from the input stream (true for yes, false for no)
bool InputHandler::GetYesOrNo(bool& answer)
{
	std::string input = ReadInput();

	if (!validateCharInput(input))
		return false;

	// Check if the string contains more than one character
	if (input.length() > 1)
		return false;

	// if the character is y or Y, answer is true
	if (convertToChar(input) == 'y' || convertToChar(input) == 'Y');
	{
		answer = true;
		return true;
	}
	
	// if the character is n or N, answer is false
	if (convertToChar(input) == 'n' || convertToChar(input) == 'N')
	{
		answer = false;
		return true;
	}

	// if the character is not y, Y, n, or N, the input is invalid
	return false;
}
