#pragma once

#include <DirectXMath.h>

#define PI DirectX::XM_PI
#define RADIUS 0.02135f // Ball radius
#define AREA PI * pow(RADIUS, 2) // Ball area pi*r^2
#define DENSITY 1.22f // Air density
#define MASS 0.0459f // Ball mass
#define yAxis DirectX::XMVECTOR({0.0f, 1.0f, 0.0f})

class Spin
{
private:
	float MagnusLiftCoefficient(float omega, float velocityLength);

public:
	Spin() = default;

	DirectX::XMFLOAT3 GetMagnusForce(DirectX::XMFLOAT3 velocity, float omega);
};

