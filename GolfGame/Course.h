#pragma once


#include <DirectXMath.h>
#include <iostream>
#include <stdlib.h>


struct Hole
{
	DirectX::XMINT3 location;
	float radius;
};


class Course
{
private:
	Hole hole;
	unsigned int par;
	DirectX::XMINT3 Bounds;
	void randomizeHoleLocation();
	int RandomSize();

public:

	Course() = default;
	Course(DirectX::XMINT3 Bounds);

	void initialize(DirectX::XMINT3 Bounds);


	DirectX::XMINT3 GetlocationHole();

	DirectX::XMINT3 SetlocationHole(DirectX::XMINT3 NewLocationHole);

	float GetradiusHole();

	float SetradiusHole(float NewRadius);


	DirectX::XMINT3 GetBounds();
	void SetBounds(DirectX::XMINT3 newBounds);

	unsigned int GetPar();
	void SetPar(unsigned int newPar);


};
