#pragma once
#ifndef HeaderGuaurdCourse
#define HeaderGuaurdCourse

#include <DirectXMath.h>
#include <iostream>
#include <stdlib.h>


struct Hole
{
	DirectX::XMFLOAT3 location;
	float radius;
};


class Course
{
private:
	Hole hole;
	DirectX::XMINT3 Bounds;
	void randomizeHoleLocation();
	int RandomSize();

public:

	Course() = default;
	Course(DirectX::XMINT3 Bounds);

	void initialize(DirectX::XMINT3 Bounds);
	

	DirectX::XMFLOAT3 GetlocationHole();

	DirectX::XMFLOAT3 SetlocationHole(DirectX::XMINT3 SizeOfHole);

	float GetradiusHole();

	float SetradiusHole(float NewRadius);
	
};

#endif
