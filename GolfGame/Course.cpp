#include "Course.h"

Course::Course(DirectX::XMINT3 bounds)
{
	initialize(bounds);
}

void Course::initialize(DirectX::XMINT3 bounds)
{
	Bounds = bounds;
	hole.radius = 1;
	//Location of the hole
	randomizeHoleLocation();
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
	int Result = rand() % 300 + 100;
	return Result;
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


