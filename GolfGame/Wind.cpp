#include "Wind.h"

void Wind::RandomizeDirection()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

	DirectX::XMFLOAT3 dir = { dis(gen), dis(gen), dis(gen) };
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&dir);
	v = DirectX::XMVector3Normalize(v);
	DirectX::XMStoreFloat3(&this->direction, v);
}

void Wind::RandomizeMagnitude(WindSpeed speedInterval)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis;

	switch (speedInterval)
	{
	case NO_WIND:
		this->magnitude = 0.0f;
		break;
	case LIGHT_WIND:
		dis = std::uniform_real_distribution<float>(0.1f, 3.3f);
		this->magnitude = dis(gen);
		break;
	case MODERATE_WIND:
		dis = std::uniform_real_distribution<float>(3.4f, 7.9f);
		this->magnitude = dis(gen);
		break;
	case STRONG_WIND:
		dis = std::uniform_real_distribution<float>(8.0f, 13.8f);
		this->magnitude = dis(gen);
		break;
	case VERY_STRONG_WIND:
		dis = std::uniform_real_distribution<float>(13.9f, 24.4f);
		this->magnitude = dis(gen);
		break;
	case STORM_WIND:
		dis = std::uniform_real_distribution<float>(24.5f, 32.6f);
		this->magnitude = dis(gen);
		break;
	case HURRICANE_WIND:
		dis = std::uniform_real_distribution<float>(32.7f, 40.0f);
		this->magnitude = dis(gen);
		break;
	case RANDOM_WIND:
		dis = std::uniform_real_distribution<float>(0.0f, 40.0f);
		this->magnitude = dis(gen);
		break;
	}
}


Wind::Wind(WindSpeed speed)
{
	Initialize(speed);
}

// Initializes the wind speed and direction
void Wind::Initialize(WindSpeed speed)
{
	RandomizeMagnitude(speed);
	RandomizeDirection();
}

// Sets the wind magnitude
void Wind::SetMagnitude(float magnitude)
{
	this->magnitude = magnitude;
}

// Sets the wind direction
void Wind::SetDirection(DirectX::XMFLOAT3 direction)
{
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&direction);
	v = DirectX::XMVector3Normalize(v);
	DirectX::XMStoreFloat3(&this->direction, v);
}

// Returns the magnitude of the wind (total speed)
float Wind::GetMagnitude()
{
	return this->magnitude;
}

// Returns a normalized 3D vector of the wind direction
DirectX::XMFLOAT3 Wind::GetDirection()
{
	return this->direction;
}

// Returns the wind speed in a 3D vector
DirectX::XMFLOAT3 Wind::GetSpeed()
{
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&this->direction);
	v = DirectX::XMVectorScale(v, this->magnitude);

	DirectX::XMFLOAT3 windSpeed;
	DirectX::XMStoreFloat3(&windSpeed, v);
	return windSpeed;
}

// Applies the wind speed to a velocity v and returns the new velocity u
DirectX::XMFLOAT3 Wind::ApplyWind(DirectX::XMFLOAT3 v)
{
	DirectX::XMVECTOR V = DirectX::XMLoadFloat3(&v);
	DirectX::XMVECTOR Vs = DirectX::XMLoadFloat3(&this->direction);
	Vs = DirectX::XMVectorScale(Vs, this->magnitude);

	V = DirectX::XMVectorAdd(V, Vs);

	DirectX::XMFLOAT3 u;
	DirectX::XMStoreFloat3(&u, V);
	return u;
}


