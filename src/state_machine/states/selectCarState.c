#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false };

#define IDENTIFIER "car%d.png"
#define H_MARGIN 200
static uint2 carCount = 0;
static int2 selection = 0;
static int2 selected = 0;


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
	if (EnterInput()) selected = selection;

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
	static char targetFile[16];
	int4 carOffset = 0;
	float carSize = 1.0f;
	// TODO: modify this code to match the filename indexing after fixing it (remove +1 and -1)
	for (int i = 1; i < carCount +1; i++)
	{
		strcpy(targetFile, TextFormat(IDENTIFIER, i));
		if (selection == i -1)
		{
			carSize = 1.5f;
			if (selection == selected) DrawText
			(
				"Selected", GetScreenWidth() * .25f,
				GetScreenHeight() * .5f - 100, 50, BLACK
			);
		}
		else carSize = 1.0f;
		SimpleDrawSheet
		(
			targetFile, (Vector2)
			{
				GetScreenWidth() * .5f + carOffset - H_MARGIN * selection,
				GetScreenHeight() * .5f
			},
			.0f, carSize, WHITE
		);
		carOffset += H_MARGIN;
	}
	DrawText("^", GetScreenWidth() * .5f, GetScreenHeight() * .5f + 40, 50, BLACK);
	DrawText("Select car using A KEY or D KEY", 40, GetScreenHeight() * .5f + H_MARGIN, 40, BLACK);
	DrawText("Press ESCAPE to exit", 40, GetScreenHeight() * .5f + H_MARGIN + 50, 40, BLACK);
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(SelectCar)
{
	return;
}
