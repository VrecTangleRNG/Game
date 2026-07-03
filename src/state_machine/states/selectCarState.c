#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false, 1 };

#define IDENTIFIER "car%d.png"
#define H_MARGIN 200
static uint2 carCount = 0;
static uint1 selection = 0;
static uint1 selected = 0;
/*
	NOTE:
	buffer[0] = represents position index in the self array that points to curently selected car
	buffer[1] = represents how many cars does the player owns (N)
	buffer[2 ~ N] = list of car ids of owned cars
*/
// TODO: make buffer dynamic
static uint4 totalBytes = 0;
static uint1 *carData = NULL;
static uint1 *buffer;


// Initialize // Runs only once at directly before game loop
INIT_STATE(SelectCar)
{
	status.pop = false;
	carCount = GetSheetData("car")->tileCount;

	// Load player data on cars
	carData = LoadFileData("app/car.dat", &totalBytes);
	selected = carData[0] - 2;
	buffer = carData;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(SelectCar)
{
	// Car selection control
	int1 nav = IsKeyPressed(KEY_D) - IsKeyPressed(KEY_A);
	selection = abs((selection + nav) % carData[1]);

	// Selected car
	if (EnterInput())
	{
		selected = selection;
		buffer[0] = 2 + selection;
	}

	// Control state flow
	if (EscapeInput())
	{
		status.pop = true;
	}
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
	for (int i = 0 +1; i < carData[1] +1; i++)
	{
		strcpy(targetFile, TextFormat(IDENTIFIER, carData[2 + i -1] +1));
		// printf("%d\n", buffer[2 + i -1]);
		if (selection == i -1)
		{
			carSize = 1.5f;
			if (selected == i -1) DrawText
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
	SaveFileData("app/car.dat", buffer, sizeof(buffer));
	UnloadFileData(carData);
}
