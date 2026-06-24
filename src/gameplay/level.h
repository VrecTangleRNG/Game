#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <string.h>
#include <stdlib.h>

#include "raylib.h"
#include "cJSON/cJSON.h"

#include "../systems/utils.h"

typedef enum
{
    CIRCUIT = 0,
    FREE_ROAM,
    DRIVE_MODE_COUNT
} RaceGameMode;

typedef struct
{
    RaceGameMode mode;
    float angle;
    char name[20];
    uint2 spawnpointId;
    uint2 *checkpointIds; // TODO: fix this member allocation type later
    uint2 cpIdCount;
} Level;

typedef struct
{
    uint1 currentLap;
    uint1 currentCp;
} LapTracker;

// Global gamemode module
void LoadCurrentLevel(char *tilemapFile, char *levelFile);
void SetRunningLevelIndex(int levelIndex);
Level *GetRunningLevel(void);

// Circuit gamemode exclusive module
void InitLapTracker(LapTracker *lap, Level *level);

#endif
