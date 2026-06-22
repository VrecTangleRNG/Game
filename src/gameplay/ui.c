/* --- User-defined header files --- */

#include "../HEADERS/ui.h"
/* --- ------------------------- --- */


/* --- Main methods --- */

void DrawDriveModeUi(void)
{
	DrawText(TextFormat("FPS: %.2f", (float)GetFPS()), 10, 10, 20, WHITE);
}
/* --- ------------ --- */
