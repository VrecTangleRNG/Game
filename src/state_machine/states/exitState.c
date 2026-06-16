#include "../stateList.h"


// Initialize //
void Init_ExitState(void)
{
	return;
}


// Update //
StateIndex Update_ExitState(float deltaTime)
{
	return STATE_EXIT;
}


// Draw //
void Draw_ExitState(void)
{
	return;
}


// Escape //
int Escape_ExitState(StateIndex toState)
{
	return 0;
}
