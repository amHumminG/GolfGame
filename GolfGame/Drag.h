#pragma once

#include <DirectXMath.h>

#define PI DirectX::XM_PI
#define RADIUS 0.02135f
#define AREA PI * pow(RADIUS, 2) // Ball area pi*r^2
#define DENSITY 1.22f // Air density
#define MASS 0.0459f // Ball mass

/*
* v = v + a * iteration
* pos = pos + v * iteration
*/

class Drag
{
private:
	float Cd = 0.21f; // Drag coefficient (Different value for different balls)

	float GetTotalVelocity(DirectX::XMFLOAT3 velocity);

public:
	Drag() = default;
	~Drag() = default;

	void CalculateDrag(DirectX::XMFLOAT3& v, DirectX::XMFLOAT3 u, DirectX::XMFLOAT3& pos,
		float gravity, float iteration, float& t);

	DirectX::XMFLOAT3 GetDragForce(DirectX::XMFLOAT3 u, float gravity);

	void SetDragCoefficient(float Cd);

	float GetDragCoefficient();
};

