#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false };

typedef enum
{
	PLAY = 0,
	CAR_SELECT,
	QUIT,
	MENU_COUNT
} Menus;

static uint1 selection = 0;


// Initialize // Runs only once at directly before game loop
INIT_STATE(MainMenu)
{
	return;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(MainMenu)
{
	// Get player input
	uint1 input = IsKeyPressed(KEY_DOWN) - IsKeyPressed(KEY_UP);

	// Cycle through menu
	selection += input;
	selection = (selection == 255) ? MENU_COUNT - 1 : selection % MENU_COUNT;

	// Send signal to machine on player pressed enter key
	if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
	{
		switch (selection)
		{
			case PLAY:
				status.state = STATE_CIRCUIT;
				status.replace = true;
				break;

			case CAR_SELECT:
				break;

			case QUIT:
				break;
		}
	}
	return &status;
}


// Pause // Do something in background
PAUSE_STATE(MainMenu)
{
	return;
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(MainMenu)
{
	ClearBackground(GRAY);
	DrawText(TextFormat("%sPlay", (selection == PLAY) ? ">> " : ""), 20, 30, 30, BLACK);
	DrawText(TextFormat("%sCar Select", (selection == CAR_SELECT) ? ">> " : ""), 20, 70, 30, BLACK);
	DrawText(TextFormat("%sQuit", (selection == QUIT) ? ">> " : ""), 20, 110, 30, BLACK);
}

// Exit // Do clean ups before continue to the next state
EXIT_STATE(MainMenu)
{
	return;
}
