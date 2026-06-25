/* --- Header files ---*/

#include "input.h"
/* --- ------------ ---*/


/* --- Function definition --- */

bool EnterInput(void)
{
    return IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER);
}

bool PauseInput(void)
{
    return IsKeyPressed(KEY_ESCAPE);
}

bool AccelerateInput(void)
{
    return IsKeyDown(KEY_UP);
}

bool BrakeInput(void)
{
    return IsKeyDown(KEY_LEFT);
}

float SteeringInput(void)
{
    return IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
}
/* --- ------------------- --- */
