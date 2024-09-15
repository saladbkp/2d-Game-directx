#include "Ball.h"
#include <corecrt_math.h>
#include "Graphics.h"

Ball::Ball(int _x, int _y)
{
	x = _x;
	y = _y;
	vx = 0;
	vy = 0;
	diameter = 20;
	radius = diameter / 2;
	inMotion = false;
}

Ball::Ball(int _x, int _y, int _dia)
{
	x = _x;
	y = _y;
	vx = 0;
	vy = 0;
	diameter = _dia;
	radius = diameter / 2;
	inMotion = false;
}

Ball::Ball()   //Default Constructor
{
	mass = diameter / 2;  // Mass scales with size (arbitrary scaling factor)
	gravity = 9.8f;           // Default gravity value
	windForce = 3.0f;         // No wind by default
}


void Ball::drawBall(Graphics& gr, float x, float y, int dia, bool filled)
{
	for (int a = (int)x - (dia / 2); a < (int)x + (dia / 2); a++)
	{
		for (int b = (int)y - (dia / 2); b < (int)y + (dia / 2); b++)
		{
			gr.PutPixel(a, b, 139, 188, 255);
		}
	}
}

void Ball::drawCircle(Graphics& gr, int ox, int oy, int rad, int r, int g, int b)
{
	for (int x = -rad; x < rad; x++)
	{
		int height = (int)sqrt(rad * rad - x * x);


		for (int y = -height; y < height; y++)
			gr.PutPixel(x + ox, y + oy, r, g, b);
	}
}

void Ball::resetBall(int _x, int _y, int _dia)
{
	x = _x;
	y = _y;
	vx = 0;
	vy = 0;
	diameter = _dia;
	radius = diameter / 2;
	inMotion = false;
}

void Ball::resetBall(int _x, int _y)
{
	x = _x;
	y = _y;
	vx = 0;
	vy = 0;
	inMotion = false;
}

bool Ball::checkCollision(const D3DXVECTOR3& playerPos, float playerWidth, float playerHeight)
{
	if (!inMotion) return false;

	float cactusLeft = x - radius - 200;
	float cactusRight = x + radius - 200;
	float cactusTop = y - radius;
	float cactusBottom = y + radius;

	float playerLeft = playerPos.x - playerWidth / 2;
	float playerRight = playerPos.x + playerWidth / 2;
	float playerTop = playerPos.y - playerHeight / 2;
	float playerBottom = playerPos.y + playerHeight / 2;

	if (cactusRight < playerLeft || cactusLeft > playerRight ||
		cactusBottom < playerTop || cactusTop > playerBottom) {
		return false; // No collision
	}

	return true; // Collision detected
}

void Ball::update(float deltaTime) {
	if (!inMotion) return;  // If the ball is not in motion, skip update

	// Apply gravity, wind force, and inertia to the ball
	applyPhysics(deltaTime, gravity, windForce);
}

void Ball::applyPhysics(float deltaTime, float gravity, float windForce) 
{
	Graphics gfx;
	mass = diameter;
	// Apply gravity
    vy += gravity;
    
	// Air resistance slows down lighter balls more
	float dragCoefficient = 0.5f / mass;  // Lighter balls have higher drag
	vy -= dragCoefficient * vy * vy; // Apply drag to vertical velocity

	// Apply wind force (affects horizontal velocity)
	vx += windForce;

	// Air resistance affects horizontal velocity as well
	vx -= dragCoefficient * vx * vx;
    //
    // Update position based on velocity and time delta
    x += vx;
    y += vy * 0.1f;
    
    //// Bounce off screen edges
    if (y > gfx.ScreenHeight - radius)
    {
        y = gfx.ScreenHeight - radius;
        vy = -vy; // Reflect y-velocity
    }
    if (y < radius) 
    {
        y = radius;
        vy = -vy; // Reflect y-velocity
    }
    if (x > gfx.ScreenWidth - radius) 
    {
        x = gfx.ScreenWidth - radius;
        vx = -vx; // Reflect x-velocity
    }
    if (x < radius) 
    {
        x = radius;
        vx = -vx; // Reflect x-velocity
    }
}

void Ball::applyForce(float forceX, float forceY)
{
	vx += forceX / mass;  // The heavier the ball, the less it accelerates
	vy += forceY / mass;
}