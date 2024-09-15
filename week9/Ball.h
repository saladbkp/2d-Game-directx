#pragma once
#include "Graphics.h"
#include "Polygon.h"

class Ball
{
public:
	Ball(int _x, int _y);
	Ball(int _x, int _y, int _dia);
	Ball();
	void drawBall(Graphics& gr, float x, float y, int dia, bool filled);
	void drawCircle(Graphics& gr, int ox, int oy, int rad, int r, int g, int b);
	void resetBall(int _x, int _y, int _dia);
	void resetBall(int _x, int _y);
	void update(float deltaTime);
	bool checkCollision(const D3DXVECTOR3& playerPos, float playerWidth, float playerHeight);
	
	void applyForce(float forceX, float forceY);
	float x;
	float y;
	float vx;
	float vy;
	int diameter;
	int radius;
	float speed;
	bool inMotion;
	float velocityX, velocityY;
	float gravity;
	float windForce;
	float mass;
private:
	// Function to apply physics (gravity, wind, inertia)
	void applyPhysics(float deltaTime, float gravity, float windForce);
};
