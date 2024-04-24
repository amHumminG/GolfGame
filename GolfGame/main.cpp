#include <iostream>

#include "Projectile.h"
using namespace std;

int main()
{
	Projectile ball;

	DirectX::XMFLOAT3 v0;

	cout << "Set vx: ";
	cin >> v0.x;
	cout << "Set vy: ";
	cin >> v0.y;
	cout << "Set vz: ";
	cin >> v0.z;
	ball.SetVelocity(v0);

	DirectX::XMFLOAT3 ballPos = ball.GetPosition();
	DirectX::XMFLOAT3 ballV = ball.GetVelocity();

	cout << "Pos: (" << ballPos.x << ", " << ballPos.y << ", " << ballPos.z << ") -- ";
	cout << "v: (" << ballV.x << ", " << ballV.y << ", " << ballV.z << ") -- ";
	cout << "Time: " << ball.GetTime() << endl;

	ball.CalculateProjectile();
	ballPos = ball.GetPosition();
	ballV = ball.GetVelocity();

	while (ball.GetPosition().y > 0.0f)
	{
		cout << "Pos: (" << ballPos.x << ", " << ballPos.y << ", " << ballPos.z << ") -- ";
		cout << "v: (" << ballV.x << ", " << ballV.y << ", " << ballV.z << ") -- ";
		cout << "Time: " << ball.GetTime() << endl;

		ball.CalculateProjectile();
		ballPos = ball.GetPosition();
		ballV = ball.GetVelocity();
	}
	cout << "Pos: (" << ballPos.x << ", " << ballPos.y << ", " << ballPos.z << ") -- ";
	cout << "v: (" << ballV.x << ", " << ballV.y << ", " << ballV.z << ") -- ";
	cout << "Time: " << ball.GetTime() << endl;


	return 0;
}