#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"
#include "box2d/box2d.h"
#include "cJSON/cJSON.h"

#include "checkpoint.h"
#include "../assets_manager/texture.h"
#include "../systems/physics.h"
#include "../systems/utils.h"
//--------------------------//

//		Tileset structs		//
typedef struct
{
	Rectangle rect;
	bool isCircle;
} Hitbox;

typedef struct
{
	int lid;
	int gid;
	int hitboxCount;
	char *tileType;		// It literally store texture's file
	Hitbox *hitboxes;
} Tile;
//--------------------------//

//		Tilemap structs		//
typedef struct
{	// -1 means an object doesn't have one/all of these properties
	int checkpoint;
	int spawnpoint;
} ObjectProperty;

typedef struct
{
	int gid;
	bool hasgid;
	Rectangle rect;
	ObjectProperty properties;
} Object;

typedef struct
{
	char *layerName;
	Object *objects;
	int objectCount;
} TilemapLayer;

typedef struct
{
	int *firstgids;
	int tsCount;
	TilemapLayer *layers;
	int layerCount;
} Tilemap;
//--------------------------//

typedef struct
{
	int id;
	b2Vec2 pos;
} Spawnpoint;

// Main functions
/* NOTE: can only load one tilemap as the program running */
void LoadMap(char *tilemapFile);
void PlaceObjects(void);
void DrawMap(void);
void FreeMapDatas(void);
void DestroyMapBodies(void);

// Utility functions
int GetTilesetIndex(int gid);
Spawnpoint GetSpawnpoint(int spawnId);

#endif
