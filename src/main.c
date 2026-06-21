/* MAKE AN ACTUAL INTRODUCTORY LINES */

/*
	NOTES: before reading source files any further...
	- char *params in function that accepts filename follows this rule:
		[absPath->originate from root, xFile->have .ext, xFilename->doesn't have .ext]
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
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Racing Game");
	SetupGameTime(FPS, 1.0f);
	while (RunStateStack());
	CloseWindow();
	return 0;
}
