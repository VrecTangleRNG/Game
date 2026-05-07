#ifndef PLAYER_H
#define PLAYER_H

#include "dependencies.h"

void InitPlayer();
void UpdatePlayer();
void DrawPlayer();
float GetPlayerX();				// Return the center x position of car
float GetPlayerY();				// Return the center y position of car using sine

#endif