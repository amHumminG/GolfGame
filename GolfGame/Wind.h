#pragma once

#include <DirectXMath.h>
#include <random>

enum WindSpeed
{
	NO_WIND = 1,			// 0.0			m/s
	LIGHT_WIND = 2,			// 0.1 - 3.3	m/s
	MODERATE_WIND = 3,		// 3.4 - 7.9    m/s
	STRONG_WIND = 4,		// 8.0 - 13.8   m/s
	VERY_STRONG_WIND = 5,	// 13.9 - 24.4  m/s
	STORM_WIND = 6,			// 24.5 - 32.6  m/s
	HURRICANE_WIND = 7,		// 32.7 - 40.0  m/s
	RANDOM_WIND = 8			// 0.0 - 40.0   m/s
};

class Wind
{
private:
	float magnitude = 0.0f;
	DirectX::XMFLOAT3 direction = { 0.0f, 0.0f, 0.0f };

	void RandomizeMagnitude(WindSpeed speed);
	void RandomizeDirection();

public:
	Wind() = default;
	Wind(WindSpeed speed);
	~Wind() = default;

	void Initialize(WindSpeed speed);

	void SetMagnitude(float magnitude);
	void SetDirection(DirectX::XMFLOAT3 direction);
	void SetWindSpeed(DirectX::XMFLOAT3 wind);
	void GenerateWind(WindSpeed speed);

	float GetMagnitude();
	DirectX::XMFLOAT3 GetDirection();
	DirectX::XMFLOAT3 GetSpeed();

	DirectX::XMFLOAT3 GetDragVelocity(DirectX::XMFLOAT3 v);
};