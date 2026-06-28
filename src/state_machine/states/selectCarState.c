#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false };

#define IDENTIFIER "car"
static uint2 carCount = 0;

// Initialize // Runs only once at directly before game loop
INIT_STATE(SelectCar)
{
	carCount = GetSheetData("car1.png")->neighborCount;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(SelectCar)
{
	return &status;
}


// Pause // Do something in background
PAUSE_STATE(SelectCar)
{
	return;
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(SelectCar)
{
	uint2 stash = carCount;
	int4 offset = 0;
	for (int i = 0; i < carCount; i++)
	{
		char file[32] = IDENTIFIER;
		strcat(strcat(file, TextFormat("%d", i)), ".png");
		if (!DrawSheetSection(file, (Vector2){ GetScreenWidth() * .5f + offset, GetScreenHeight() * .5f }, (Vector2){ 0, 0 }, .0f, WHITE))
		{
			carCount++;
		}
		offset += 128;
	}
	carCount = stash;
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(SelectCar)
{
	return;
}
