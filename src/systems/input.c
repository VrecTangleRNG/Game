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
/* --- ------------------- --- */
