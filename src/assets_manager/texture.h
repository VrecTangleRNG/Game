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
} TextureData;

typedef struct
{
	Texture2D sheet;
	uint4 tileCount;
} SheetData;


void LoadTextureSheet(char *filename);													// load png (filename) from assets/ into memory
uint1 SimpleDrawSheet(char *file, Vector2 pos, float rotation, float scale, Color tint);// Draw texture section with origin set to middle
uint1 DrawSheetSection(char *file, Vector2 pos, Vector2 origin, float rot, float scale, Color tint);	// Draw one section (file) from a loaded sheet
void FreeTexture(char *filename);														// Free the (filename) position texture loaded into memory
void ClearTextures(void);																// Clear all textures and tiles information
TextureData *GetTileData(char *file);													// Returns texture rectangle and index of (file) texture
SheetData *GetSheetData(char *cutFilename);												// Returns sheet data of position (filename) with no "_sheet" prefix

#endif
