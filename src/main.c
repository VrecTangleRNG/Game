/* MAKE AN ACTUAL INTRODUCTORY LINES */

/*
	NOTE: before reading source files any further...
	- char *params in function arguments that accepts filename follows this rule:
		[absPath->originate from root, xFile->have .ext, xFilename->doesn't have .ext]
	- TODO: fix car numbering (should start at 0) and in selectCarState.c
*/


/* Core library */
#include "raylib.h"


/* Complementary library */
#include "state_machine/stateMachine.h"
#include "systems/timer.h"


/* Preprocessors */
#define FPS 60.0f
#define SCREEN_WIDTH 1680
#define SCREEN_HEIGHT 1050


// Start of the program
int main(void)
{
	ChangeDirectory(GetApplicationDirectory());
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Racing Game");
	SetExitKey(KEY_NULL);
	TimerInit(FPS, 1.0f);
	while (RunStateStack());	// CRITICAL POINT IMMINENT
	CloseWindow();
	return 0;
}
