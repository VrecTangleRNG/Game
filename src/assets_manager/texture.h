#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"
#include "cJSON/cJSON.h"

#include "../systems/utils.h"

typedef struct
{
	Rectangle rect;
	uint4 textureIndex;
	uint2 neighborCount;
} TextureData;


void LoadTextureSheet(const char *filename);											// load png (filename) from assets/ into memory
uint1 DrawSheetSection(char *file, Vector2 pos, Vector2 origin, float rot, Color tint);	// Draw one section (file) from a loaded sheet
void FreeAllTextures(void);																// Free all textures loaded into memory
TextureData *GetSheetData(char *file);													// Returns texture rectangle and index of (file) texture

#endif
