#include "InputHandler.h"

// PRIVATE FUNCTIONS

std::string InputHandler::ReadInput()
{
    std::string input;
    std::getline(std::cin, input);

    return input;
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
		if (!isdigit(input[i]) && input[i] != '.')
			return false;
	}

    return true;
}

// Converts a string to a float
float InputHandler::convertToFloat(std::string input)
{
    if (input.back() == '.')
		input.pop_back();

    std::cout << input << std::endl;

	return std::stof(input);
}



// PUBLIC FUNCTIONS

// Obtains the start velocity vector from the input stream
bool InputHandler::GetStartVelocity(DirectX::XMFLOAT3& startVelocity)
{
    float arr[3] = { 0.0f, 0.0f, 0.0f };
    unsigned int arrSize = 0;

    // Get the input from the user
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
