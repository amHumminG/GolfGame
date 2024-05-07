#pragma once

#include <DirectXMath.h>

#include "Drag.h"
#include "Wind.h"

enum Gravity
{
	EARTH = 1,
	MOON = 2,
	MARS = 3,
	JUPITER = 4,
	VENUS = 5
};

class Projectile
{
private:
	Drag drag;
	Wind wind;

	DirectX::XMFLOAT3 pos0 = { 0.0f, 0.0f, 0.0f }; // Initial position of the ball
	DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f }; // Current position of the ball
	DirectX::XMFLOAT3 v0 = { 0.0f, 0.0f, 0.0f }; // Initial velocity of the ball
	DirectX::XMFLOAT3 v = { 0.0f, 0.0f, 0.0f }; // Current velocity of the ball
	float gravity = 9.81f;
	float t = 0.0f; // Current time of the projectile

	float iteration = 0.1f; // Update frequency
	bool airDrag = true;

	void ResetTime(); // Resets the time to 0.0f for every shot

public:
	Projectile() = default;
	Projectile(DirectX::XMFLOAT3 pos0, DirectX::XMFLOAT3 v0, float updateFrequency, Gravity g, bool airDrag,
		WindSpeed windSpeed);
	~Projectile() = default;

	void Initialize(DirectX::XMFLOAT3 pos0, DirectX::XMFLOAT3 v0, float updateFrequency, Gravity g, bool airDrag,
		WindSpeed windSpeed);

	void CalculateProjectile();

	void SetVelocity(DirectX::XMFLOAT3 v0);
	void SetPosition(DirectX::XMFLOAT3 pos0);
	void SetIteration(float iteration);
	void SetGravity(Gravity g);
	void SetUpdateFrequency(float updateFrequency);
	void SetAirDrag(bool airDrag);
	void SetWindSpeed(WindSpeed windSpeed);
	void SetWindManual(DirectX::XMFLOAT3 wind);

	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetVelocity();
	float GetTotalVelocity();
	float GetTime();
	float GetGravity();
	bool GetAirDrag();
	DirectX::XMFLOAT3 GetWindSpeed();

};
