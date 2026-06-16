#include "../stateList.h"


static Countdown countdown;


// Initialize // Runs only once at directly before game loop
void Init_CountdownState(void)
{
	CountdownStart(&countdown, 3.0f);
}


// Update // Control the program flow with the return value
StateIndex Update_CountdownState(float deltaTime)
{
	CountdownUpdate(&countdown);
	if (countdown.finished) return STATE_RACE;
	return STATE_CONTINUE;
}


// Draw // Generic draw function runs directly after update
void Draw_CountdownState(void)
{
	BeginMode2D(GetCamera());
		DrawMap();
		DrawPlayer();
	EndMode2D();
	DrawText
	(
		TextFormat("Ready in: %d", (int)countdown.remaining + 1), 10,
		GetScreenHeight() * .5f - 30, 30, BLACK
	);
}


// Escape // Return 1 to continue running, 0 to exit program entirely
int Escape_CountdownState(StateIndex toState)
{
	return 1;
}