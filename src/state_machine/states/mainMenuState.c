#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false };

typedef enum
{
	PLAY = 0,
	CAR_SELECT,
	QUIT,
	MENU_COUNT
} Menus;

static smalluint selection = 0;


// Initialize // Runs only once at directly before game loop
INIT_STATE(MainMenu)
{
	return;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(MainMenu)
{
	smalluint input = IsKeyPressed(KEY_DOWN) - IsKeyPressed(KEY_UP);
	selection += input;
	selection = abs(selection) % MENU_COUNT;
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
	DrawText(TextFormat("%sPlay", (selection == PLAY) ? ">> " : ""), 20, 30, 30, BLACK);
	DrawText(TextFormat("%sCar Select", (selection == CAR_SELECT) ? ">> " : ""), 20, 70, 30, BLACK);
	DrawText(TextFormat("%sQuit", (selection == QUIT) ? ">> " : ""), 20, 110, 30, BLACK);
}

// Exit // Do clean ups before continue to the next state
EXIT_STATE(MainMenu)
{
	return;
}
