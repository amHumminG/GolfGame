#include "Course.h"
#include <random>
Course::Course(DirectX::XMINT3 bounds)
{
	initialize(bounds);
}

void Course::initialize(DirectX::XMINT3 bounds)
{
	Bounds = bounds;
	hole.radius = 1;
	randomizeHoleLocation();
	SetPar(7); // change to dynamically change based on distance to hole
}

void Course::randomizeHoleLocation()
{
	//Random position in x 
	int locationX = RandomSize();
	hole.location.x = locationX;

	//Random position in y 
	hole.location.y = 0;

	//Random position in z 
	int locationZ = RandomSize();
	hole.location.z = locationZ;
}

int Course::RandomSize()
{
	std::random_device RandomDevice;
	std::uniform_int_distribution<> RandomNum(100, 300);
	int randomNumber = RandomNum(RandomDevice);
	return randomNumber;
}


DirectX::XMINT3 Course::GetlocationHole()
{
	return hole.location;
}


DirectX::XMINT3 Course::SetlocationHole(DirectX::XMINT3 NewLocationHole)
{
	return hole.location = NewLocationHole;
}


float Course::GetradiusHole()
{
	return hole.radius;
}

float Course::SetradiusHole(float NewRadius)
{
	return hole.radius = NewRadius;
}


DirectX::XMINT3 Course::GetBounds()
{
	return this->Bounds;
}

void Course::SetBounds(DirectX::XMINT3 NewBounds)
{
	this->Bounds = NewBounds;
}

unsigned int Course::GetPar()
{
	return this->par;
}

void Course::SetPar(unsigned int NewPar)
{
	this->par = NewPar;
}


