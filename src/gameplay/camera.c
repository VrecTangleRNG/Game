/* --- User-defined header files --- */

#include "../HEADERS/camera.h"
/* --- ------------------------- --- */


/* --- Global static variables --- */

Camera2D camera = { 0 };
/* --- ----------------------- --- */


/* --- Methods --- */

void SetupCamera(void)
{
	camera.offset = (Vector2)
	{
		GetScreenWidth() * 0.5f,
		GetScreenHeight() * 0.5f
	};
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
}

inline void SetCameraPos(Vector2 *v)
{
	camera.target = *v;
}

Camera2D GetCamera(void)
{
	return camera;
}
/* --- ------- --- */
