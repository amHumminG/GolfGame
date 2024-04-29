#include "Course.h"

// Returns a random integer between min and max
int Course::RandomInRange(int min, int max)
{
	std::random_device RandomDevice;
	std::uniform_int_distribution<> RandomNum(min, max);
	int randomNumber = RandomNum(RandomDevice);
	return randomNumber;
}

// Adds one to the par for every increment of distance between the ball and the hole
unsigned int Course::CalculatePar(unsigned int Increment)
{
	// Calculate the distance between 0,0,0 ball and the hole
	int distance = sqrt(pow((this->hole.location.x + this->hole.location.z), 2));
	return distance / Increment;
}

// Generates a hole with a random location and radius
void Course::GenerateHole(int minDistanceToHole, int maxDistanceToHole, float holeRadius, unsigned int parIncrement)
{
	RandomizeHoleLocation(minDistanceToHole, maxDistanceToHole);
	SetHoleRadius(1);
	SetPar(CalculatePar(parIncrement));
}

Course::Course(DirectX::XMINT3 bounds)
{
	initialize(bounds);
}

void Course::initialize(DirectX::XMINT3 initialBounds)
{
	SetBounds(initialBounds);
	GenerateHole(100, 400, 1, 50);
}

// Randomizes the location of the hole
void Course::RandomizeHoleLocation(int min, int max)
{
	int locationX = RandomInRange(min, max);
	int locationY = 0;
	int locationZ = RandomInRange(min, max);

	hole.location.x = locationX;
	hole.location.y = locationY;
	hole.location.z = locationZ;
}

DirectX::XMINT3 Course::GetBounds()
{
	return this->bounds;
}

DirectX::XMINT3 Course::GetHoleLocation()
{
	return this->hole.location;
}

float Course::GetHoleRadius()
{
	return this->hole.radius;
}

unsigned int Course::GetPar()
{
	return this->par;
}

void Course::SetBounds(DirectX::XMINT3 NewBounds)
{
	this->bounds = NewBounds;
}

void Course::SetHoleLocation(DirectX::XMINT3 NewLocation)
{
	this->hole.location = NewLocation;
}

void Course::SetHoleRadius(float NewRadius)
{
	this->hole.radius = NewRadius;
}

void Course::SetPar(unsigned int NewPar)
{
	this->par = NewPar;
}


