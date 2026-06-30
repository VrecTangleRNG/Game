#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false };

#define IDENTIFIER "car%d.png"
static uint2 carCount = 0;
static int2 margin = 256;
static int2 selection = 0;


// Initialize // Runs only once at directly before game loop
INIT_STATE(SelectCar)
{
	status.pop = false;
	carCount = GetSheetData("car")->tileCount;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(SelectCar)
{
	// Car selection
	int1 nav = IsKeyPressed(KEY_D) - IsKeyPressed(KEY_A);
	selection = (selection + nav);

	// Control state flow
	if (EscapeInput()) status.pop = true;
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
	int4 offset = 0;
	// TODO: modify this code to match the filename indexing after fixing it
	for (int i = 1; i < carCount + 1; i++)
	{
		char file[32];
		strcpy(file, TextFormat(IDENTIFIER, i));
		SimpleDrawSheet
		(
			file, (Vector2){ GetScreenWidth() * .5f + offset + margin * selection, GetScreenHeight() * .5f},
			.0f, 1.0f, WHITE
		);
		offset += margin;
	}
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(SelectCar)
{
	return;
}
