#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false };

#define IDENTIFIER "car%d.png"
static uint2 carCount = 0;
static int2 margin = 200;
static int2 selection = 0;
static int2 selected = 0;
static char file[16];


// Initialize // Runs only once at directly before game loop
INIT_STATE(SelectCar)
{
	status.pop = false;
	carCount = GetSheetData("car")->tileCount;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(SelectCar)
{
	// Car selection control
	int1 nav = IsKeyPressed(KEY_D) - IsKeyPressed(KEY_A);
	selection = abs((selection + nav) % carCount);

	// Selected car
	strcpy(file, TextFormat(IDENTIFIER, selection + 1 /* TODO: remove 1 when texture numebering was fixed */));
	if (EnterInput()) selected = selection + 1;

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
	float size;
	// TODO: modify this code to match the filename indexing after fixing it
	for (int i = 1; i < carCount + 1; i++)
	{
		char currentFile[16];
		strcpy(currentFile, TextFormat(IDENTIFIER, i));
		if (strcmp(file, currentFile) == 0) size = 1.5f;
		else size = 1.0f;
		SimpleDrawSheet
		(
			currentFile, (Vector2){ GetScreenWidth() * .5f + offset - margin * selection, GetScreenHeight() * .5f},
			.0f, size, WHITE
		);
		offset += margin;
	}
	DrawText("^", GetScreenWidth() * .5f, GetScreenHeight() * .5f + 40, 50, BLACK);
	DrawText("Select car using A KEY or D KEY", 40, GetScreenHeight() * .5f + margin, 40, BLACK);
	DrawText("Press ESCAPE to exit", 40, GetScreenHeight() * .5f + margin + 50, 40, BLACK);
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(SelectCar)
{
	return;
}
