#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>	// DEBUG
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"
#include "cJSON/cJSON.h"

#include "utils.h"

typedef struct
{
	Rectangle rect;
	int textureIndex;
} TextureData;

// Main functions
void LoadTextureSheet(const char *filename);
void DrawSheetSection(char *file, Vector2 pos, Vector2 origin, float rot, Color tint);
void FreeAllTextures(void);

// Utility functions
TextureData *GetTextureData(char *file);

#endif
