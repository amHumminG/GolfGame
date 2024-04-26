#pragma once

#include <DirectXMath.h>

class Projectile
{
private:
	DirectX::XMFLOAT3 pos0 = { 0.0f, 0.0f, 0.0f }; // Initial position of the ball
	DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f }; // Current position of the ball
	DirectX::XMFLOAT3 v0 = { 0.0f, 0.0f, 0.0f }; // Initial velocity of the ball
	DirectX::XMFLOAT3 v = { 0.0f, 0.0f, 0.0f }; // Current velocity of the ball
	float gravity = 9.81f;
	float t = 0.0f; // Current time of the projectile

	float iteration = 0.1f; // Update frequency

	void ResetTime();

public:
	Projectile() = default;
	~Projectile() = default;

	void CalculateProjectile();

	void SetVelocity(DirectX::XMFLOAT3 v0);
	void SetPosition(DirectX::XMFLOAT3 pos0);
	void SetGravity(float gravity);
	void SetUpdateFrequency(float iteration);

	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetVelocity();
	float GetTotalVelocity();
	float GetTime();
};

// SetVelocity() and SetPosition() needs to be called on every new shot