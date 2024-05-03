#include "Drag.h"

void Drag::CalculateDrag(DirectX::XMFLOAT3& v, float uTotal, DirectX::XMFLOAT3& pos, 
	float gravity, float iteration, float& t)
{
	// Drag accelerations
	float ax = - (DENSITY * uTotal * AREA * Cd * v.x) / (2 * MASS);
	float ay = - gravity - (DENSITY * uTotal * AREA * Cd * v.y) / (2 * MASS);
	float az = - (DENSITY * uTotal * AREA * Cd * v.z) / (2 * MASS);

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
	float vTotal1 = pow((pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)), 0.5f);

	ax = -(DENSITY * uTotal * AREA * Cd * v.x) / (2 * MASS);
	ay = -gravity - (DENSITY * uTotal * AREA * Cd * v.y) / (2 * MASS);
	az = -(DENSITY * uTotal * AREA * Cd * v.z) / (2 * MASS);

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

void Drag::SetDragCoefficient(float Cd)
{
	this->Cd = Cd;
}
