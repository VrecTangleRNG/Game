#ifndef PHYSICS_H
#define PHYSICS_H

#include <string.h>

#include "raylib.h"
#include "box2d/box2d.h"

#include "timer.h"

#define PX_PER_METER 32.0f


// Main functions
// NOTE: Call CheckSensorCollision after calling UpdatePhysics in a loop
void InitPhysics(void);                                             // Create a world for physics objects to live upon, runs only once
void UpdatePhysics(float timeStep, float deltaTime);                // Similar to generic update function in state machine
/*
    (check) = 1 will return ENTERED shape id, vice versa for -1.
    one of both shape can be NULL, return NULL if no collision event happen
*/
b2ShapeId *CheckSensorCollision(b2ShapeId *targetShape, b2ShapeId *sensorShape, int check);
b2WorldId GetWorldId(void);                                         // Get world id

#endif
