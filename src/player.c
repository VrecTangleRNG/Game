#include "dependencies.h"
#include <stdio.h>
/* TODO:
	- fix the rotation bug where if the car is lined 0 degree, the tire do full rotation
	- understand and give comment to everything so you won't forget
	- do fina; code clean up
*/	


// Global variables
// Visuals
Texture2D car;
Texture2D tire;
Rectangle carSource;
Rectangle tireSource;
Rectangle carDest;
Rectangle tireDest;
Vector2 origin;				// Used for center of bodyRotation, scaling, and main coordinate
Vector2 tireOrigin;
float bodyRotation;
float tireRotation;
int lastRotation = 0;
float scale = 2.0f;

// Dynamics
float acceleration = 15;
float speed;


// Main game loop
//-----------------------------------------------------------------------------------------
void InitPlayer()
{
	
	// Texture loading
	car = LoadTexture("assets/body.png");
	tire = LoadTexture("assets/tire.png"); 					// tire dimension: 5*7
	
	carSource = (Rectangle){ 0, 0, car.width, car.height};
	carDest = (Rectangle)
	{
		GetScreenWidth()/2, GetScreenHeight()/2,
		car.width*scale, car.height*scale
	};
	
	tireSource = (Rectangle){ 0, 0, tire.width, tire.height };
	tireDest = (Rectangle){ 0, 0, tire.width*scale, tire.height*scale };
	
	origin = (Vector2){ car.width*scale/2, car.height*scale*4/5 };
	tireOrigin = (Vector2){ tire.width*scale/2, tire.height*scale/2 };
	bodyRotation = 90.0f;
	tireRotation = bodyRotation;
}


void UpdatePlayer()
{
	
	// Listen for user input for movement
	int speedFactor = IsKeyDown(KEY_UP) -IsKeyDown(KEY_DOWN);
	speed += acceleration*GetFrameTime()*speedFactor;
	speed = Clamp(speed, -10, 10);
	
	// When player isn't register any input, decelerate until it is stoped
	if (speedFactor == 0)
	{
		if (speed > 0)
		{
			speed -= acceleration*GetFrameTime();
			speed = Clamp(speed, 0, 10);
		}
		else if (speed < 0)
		{
			speed += acceleration*GetFrameTime();
			speed = Clamp(speed, -10, 0);
		}
	}
	
	// Listen for user input for any rotation
	int rotation = IsKeyDown(KEY_A) - IsKeyDown(KEY_D);
	bodyRotation -= 120.0f*speed/5*rotation*GetFrameTime();
	if (bodyRotation > 360) bodyRotation -= 360;
	if (bodyRotation < 0) bodyRotation += 360;
	tireRotation -= 800.0f*GetFrameTime()*rotation;
	if (rotation != 0)
	{
		lastRotation = rotation;
	}
	
	// If no rotation input is delivered, then return to normal position
	else
	{
		float returnSpeed = 200.0f;
    
		if (tireRotation > bodyRotation)
		{
			tireRotation -= returnSpeed * GetFrameTime();
		}
			
		else if (tireRotation < bodyRotation)
		{
			tireRotation += returnSpeed * GetFrameTime();
		}
	}
	
	// Move and rotate, both it's body and tires
	carDest.x -= cos(DEG2RAD*bodyRotation)*speed;
	carDest.y -= sin(DEG2RAD*bodyRotation)*speed;
	
	Vector2 localOffset = {
    car.width*scale/2 -tire.width*scale/2 +2,
    car.height*scale*3/5
	};

	Vector2 rotatedOffset = Vector2Rotate(localOffset, DEG2RAD * (bodyRotation + 90.0f));

	tireDest.x = carDest.x + rotatedOffset.x;
	tireDest.y = carDest.y + rotatedOffset.y;
	tireRotation = Clamp(tireRotation, bodyRotation -60.0f, bodyRotation +60.0f);
	
	
	// DEBUG
	static float timer = 0;
	timer += GetFrameTime();

	if (timer > 0.2f)
	{
		printf("%.2f %.2f %.2f\n", 1);
		timer = 0;
	}
}


void DrawPlayer()
{
	DrawTexturePro(tire, tireSource, tireDest, tireOrigin, tireRotation -90.0f, WHITE);
	DrawTexturePro(car, carSource, carDest, origin, bodyRotation -90.0f, WHITE);
}
//-----------------------------------------------------------------------------------------


// Methods
//-----------------------------------------------------------------------------------------
float GetPlayerX()
{
	return carDest.x;
}

float GetPlayerY()
{
	return carDest.y -sin(DEG2RAD*bodyRotation)*car.height*scale/5;
}
//-----------------------------------------------------------------------------------------


