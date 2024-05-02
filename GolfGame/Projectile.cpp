#include "Projectile.h"

void Projectile::ResetTime()
{
	this->t = 0.0f;
}

Projectile::Projectile(DirectX::XMFLOAT3 pos0, DirectX::XMFLOAT3 v0, float updateFrequency, Gravity g, bool airDrag)
{
	this->Initialize(pos0, v0, updateFrequency, g, airDrag);
}

void Projectile::Initialize(DirectX::XMFLOAT3 pos0, DirectX::XMFLOAT3 v0, float updateFrequency, Gravity g, bool airDrag)
{
	this->iteration = updateFrequency;
	this->SetPosition(pos0);
	this->SetVelocity(v0);
	this->SetGravity(g);
	this->airDrag = airDrag;
}

void Projectile::CalculateProjectile()
{
	t += iteration;

	// If air drag should be calculated
	if (this->airDrag)
	{
		this->drag.CalculateDrag(this->v0, this->v, this->GetTotalVelocity(), this->pos, this->gravity, 
			this->iteration, this->t);
	}
	else
	{
		// Position
		pos.x = v0.x * t + pos0.x;
		pos.y = v0.y * t - ((gravity * pow(t, 2)) / 2) + pos0.y;
		pos.z = v0.z * t + pos0.z;

		// Velocity
		v.x = v0.x;
		v.y = v0.y - gravity * t; // Calculate the new vy after the time t
		v.z = v0.z;

		if (pos.y <= 0) // If pos.y <= 0, calculate velocity and position when the ball is exactly at y = 0
		{
			t = v0.y / (gravity / 2);

			pos.x = v0.x * t + pos0.x;
			pos.y = 0.0f;
			pos.z = v0.z * t + pos0.z;

			v.y = v0.y - gravity * t;
		}
	}
}

void Projectile::SetVelocity(DirectX::XMFLOAT3 v0)
{
	this->ResetTime();
	this->v0 = v0;
	this->v = v0;
}

void Projectile::SetPosition(DirectX::XMFLOAT3 pos0)
{
	this->pos0 = pos0;
}

void Projectile::SetGravity(Gravity g)
{
	switch (g)
	{
	case Gravity::EARTH:
		this->gravity = 9.81f;
		break;

	case Gravity::MOON:
		this->gravity = 1.62f;
		break;

	case Gravity::MARS:
		this->gravity = 3.71f;
		break;

	case Gravity::JUPITER:
		this->gravity = 24.79f;
		break;

	case Gravity::VENUS:
		this->gravity = 8.87f;
		break;
	}
}

void Projectile::SetUpdateFrequency(float iteration)
{
	this->iteration = iteration;
}

DirectX::XMFLOAT3 Projectile::GetPosition()
{
	return this->pos;
}

DirectX::XMFLOAT3 Projectile::GetVelocity()
{
	return this->v;
}

float Projectile::GetTotalVelocity()
{
	return pow(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2), 0.5f); // Length of the total velocity vector
}

float Projectile::GetTime()
{
	return this->t;
}

float Projectile::GetGravity()
{
	return this->gravity;
}
