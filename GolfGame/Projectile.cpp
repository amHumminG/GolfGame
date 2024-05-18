#include "Projectile.h"

void Projectile::ResetTime()
{
	this->t = 0.0f;
}

float Projectile::GetVectorLength(DirectX::XMFLOAT3 vector)
{
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

DirectX::XMFLOAT3 Projectile::GetTotalForce(DirectX::XMFLOAT3 u)
{
	DirectX::XMFLOAT3 Fd = this->drag.GetDragForce(u, this->gravity); // Drag force
	DirectX::XMFLOAT3 Fm = this->spin.GetMagnusForce(u, this->angularVelocity); // Magnus force

	DirectX::XMVECTOR FdVec = DirectX::XMLoadFloat3(&Fd);
	DirectX::XMVECTOR FmVec = DirectX::XMLoadFloat3(&Fm);
	DirectX::XMVECTOR FgVec = DirectX::XMVectorScale({ 0.0f, -1.0f, 0.0f }, MASS * this->gravity);

	DirectX::XMVECTOR totalForceVec = DirectX::XMVectorAdd(FdVec, FmVec); // Sum of all forces, Fd + Fm
	totalForceVec = DirectX::XMVectorAdd(totalForceVec, FgVec);
	
	DirectX::XMFLOAT3 totalForce;
	DirectX::XMStoreFloat3(&totalForce, totalForceVec);
	return totalForce;
}

void Projectile::ApplyForces(DirectX::XMFLOAT3 u, DirectX::XMFLOAT3 totalForce)
{
	// Accelerations
	float ax = totalForce.x / MASS;
	float ay = totalForce.y / MASS;
	float az = totalForce.z / MASS;

	// New velocities
	v.x = v.x + ax * iteration;
	v.y = v.y + ay * iteration;
	v.z = v.z + az * iteration;

	// New positions
	pos.x = pos.x + v.x * iteration;
	pos.y = pos.y + v.y * iteration;
	pos.z = pos.z + v.z * iteration;

	// Next iteration
	DirectX::XMFLOAT3 newV;
	DirectX::XMFLOAT3 newPos;
	DirectX::XMFLOAT3 newU = this->wind.GetDragVelocity(this->v);
	totalForce = this->GetTotalForce(newU);

	ax = totalForce.x / MASS;
	ay = totalForce.y / MASS;
	az = totalForce.z / MASS;

	newV.x = v.x + ax * iteration;
	newV.y = v.y + ay * iteration;
	newV.z = v.z + az * iteration;

	newPos.x = pos.x + v.x * iteration;
	newPos.y = pos.y + v.y * iteration;
	newPos.z = pos.z + v.z * iteration;

	// If pos.y <= 0, calculate velocity and position when the ball is exactly at y = 0
	if (newPos.y <= 0.0f)
	{
		// Vector from last iteration to new iteration
		DirectX::XMFLOAT3 vec = { pos.x - newPos.x, pos.y - newPos.y, pos.z - newPos.z };

		float yWhole = vec.y; // Length of the vector in y axis
		float yDiffUnder = -newPos.y; // From y = 0 to newPos.y, newPos.y will always be negative

		float underSlice = yDiffUnder / yWhole; // Percentage of the y part under 0 to newPos.y

		// New positions when y = 0
		pos.x = newPos.x + underSlice * vec.x;
		pos.y = 0.0f;
		pos.z = newPos.z + underSlice * vec.z;

		t = t + underSlice * iteration;
	}
}

Projectile::Projectile(DirectX::XMFLOAT3 pos0, DirectX::XMFLOAT3 v0, float updateFrequency, Gravity g, bool airDrag,
	WindSpeed windSpeed, float angularVelocity)
{
	this->Initialize(pos0, v0, updateFrequency, g, airDrag, windSpeed, angularVelocity);
}

void Projectile::Initialize(DirectX::XMFLOAT3 pos0, DirectX::XMFLOAT3 v0, float updateFrequency, Gravity g, bool airDrag,
	WindSpeed windSpeed, float angularVelocity)
{
	this->SetIteration(updateFrequency);
	this->SetPosition(pos0);
	this->SetVelocity(v0);
	this->SetGravity(g);
	this->SetAirDrag(airDrag);
	this->SetWindSpeed(windSpeed);
	this->SetAngularVelocity(angularVelocity);
}

void Projectile::CalculateProjectile()
{
	t += iteration;

	// If air drag should be calculated, else calculate only gravity
	if (this->airDrag)
	{
		DirectX::XMFLOAT3 u = this->wind.GetDragVelocity(this->v);
		this->drag.CalculateDrag(this->v, u, this->pos, this->gravity, 
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

void Projectile::CalculateProjectile1()
{
	t += iteration;

	// If air drag should be calculated, else calculate only gravity
	if (this->airDrag)
	{
		DirectX::XMFLOAT3 u = this->wind.GetDragVelocity(this->v);
		DirectX::XMFLOAT3 totalForce = this->GetTotalForce(u);
		this->ApplyForces(u, totalForce);
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
	this->pos = pos0;
}

void Projectile::SetIteration(float updateFrequency)
{
	this->iteration = updateFrequency;
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

void Projectile::SetAirDrag(bool airDrag)
{
	this->airDrag = airDrag;
}

void Projectile::SetWindSpeed(WindSpeed windSpeed)
{
	this->wind.Initialize(windSpeed);
}

void Projectile::SetWindManual(DirectX::XMFLOAT3 wind)
{
	this->wind.SetWindSpeed(wind);
}

void Projectile::SetAngularVelocity(float angularVelocity)
{
	this->angularVelocity = angularVelocity;
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
	return this->GetVectorLength(this->v); // Length of the total velocity vector
}

float Projectile::GetTime()
{
	return this->t;
}

float Projectile::GetGravity()
{
	return this->gravity;
}

bool Projectile::GetAirDrag()
{
	return this->airDrag;
}

DirectX::XMFLOAT3 Projectile::GetWindSpeed()
{
	return this->wind.GetSpeed();
}
