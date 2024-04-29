#pragma once

#include <DirectXMath.h>
#include <random>


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
	DirectX::XMINT3 bounds;

	int RandomInRange(int min, int max);
	void RandomizeHoleLocation(int min, int max);
	unsigned int CalculatePar(unsigned int increment);

public:

	Course() = default;
	Course(DirectX::XMINT3 bounds);

	void initialize(DirectX::XMINT3 bounds);
	void GenerateHole(int minDistanceToHole, int maxDistanceToHole, float holeRadius, unsigned int parIncrement);

	DirectX::XMINT3 GetBounds();
	DirectX::XMINT3 GetHoleLocation();
	float GetHoleRadius();
	unsigned int GetPar();

	void SetBounds(DirectX::XMINT3 newBounds);
	void SetHoleLocation(DirectX::XMINT3 newLocation);
	void SetHoleRadius(float newRadius);
	void SetPar(unsigned int newPar);
};
