#pragma once

#include <DirectXMath.h>

#define PI DirectX::XM_PI
#define AREA PI * pow(0.02135f, 2) // Ball area pi*r^2
#define DENSITY 1.22f // Air density
#define MASS 0.0459f // Ball mass

// Turbulent drag (flow) p.103

/*
* v = v + a * iteration
* pos = pos + v * iteration
*/

class Drag
{
private:
	float Cd = 0.21f; // Drag coefficient (Different value for different balls)

public:
	Drag() = default;
	~Drag() = default;

	void CalculateDrag(DirectX::XMFLOAT3& v0, DirectX::XMFLOAT3& v, float vTotal, DirectX::XMFLOAT3& pos,
		float gravity, float iteration, float& t);

	void SetDragCoefficient(float Cd);
};

