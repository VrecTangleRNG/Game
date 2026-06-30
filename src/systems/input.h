#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#include "raylib.h"


// Function declaration //
// universal input
bool EnterInput(void);
bool EscapeInput(void);

// Car player control
bool AccelerateInput(void);
bool BrakeInput(void);
float SteeringInput(void);

#endif
