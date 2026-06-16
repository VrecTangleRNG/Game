#ifndef PHYSICS_H
#define PHYSICS_H

#include <string.h>

#include "raylib.h"
#include "box2d/box2d.h"

#include "timer.h"

#define PX_PER_METER 32.0f


// Main functions
// NOTE: Call CheckSensorCollision after calling UpdatePhysics in a loop
void InitPhysics(void);
void UpdatePhysics(float timeStep, float deltaTime);
b2ShapeId CheckSensorCollision(b2ShapeId *targetShape, b2ShapeId *sensorShape, int check);

// Utility functions
b2WorldId GetWorldId(void);

#endif
