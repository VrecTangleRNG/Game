#include "../stateList.h"


// Initialize //
void Init_BaseState(void)
{
	return;
}


// Update //
StateIndex Update_BaseState(float deltaTime)
{
	return STATE_HIGHLIGHT;
}


// Draw //
void Draw_BaseState(void)
{
	return;
}


// Escape //
int Escape_BaseState(StateIndex toState)
{
	return 1;
}
