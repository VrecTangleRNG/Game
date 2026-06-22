#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"

void SetupCamera(void);         // Runs only once to initialize camera
void SetCameraPos(Vector2 *v);  // Set where the camera should be focused in fixed coordinates
Camera2D GetCamera(void);       // Get camera informations

#endif
