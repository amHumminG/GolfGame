#include "Spin.h"

float Spin::MagnusLiftCoefficient(float omega, float velocityLength)
{
	return (RADIUS * omega) / velocityLength;
}

DirectX::XMFLOAT3 Spin::GetMagnusForce(DirectX::XMFLOAT3 velocity, float omega)
{
	float velocityLength = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2) + pow(velocity.z, 2));
	float magnusLiftCoefficient = MagnusLiftCoefficient(omega, velocityLength);
	float magnusForce = (magnusLiftCoefficient * DENSITY * pow(velocityLength, 2) * AREA) / 2;
	
	DirectX::XMVECTOR normalizeVelocity = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&velocity));
	DirectX::XMVECTOR ew = DirectX::XMVector3Cross(yAxis, DirectX::XMLoadFloat3(&velocity)); // (e_omega) Local x-axis 
	DirectX::XMVECTOR normalizeEw = DirectX::XMVector3Normalize(ew);

	DirectX::XMVECTOR em = DirectX::XMVector3Cross(normalizeVelocity, normalizeEw);

	DirectX::XMVECTOR magnusForceVector = DirectX::XMVectorScale(em, magnusForce);
	DirectX::XMFLOAT3 magnusForceFloat3;
	DirectX::XMStoreFloat3(&magnusForceFloat3, magnusForceVector);
	return magnusForceFloat3;
}
