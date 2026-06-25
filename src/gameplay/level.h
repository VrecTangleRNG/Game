#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <string.h>
#include <stdlib.h>

#include "raylib.h"
#include "cJSON/cJSON.h"

#include "checkpoint.h"
#include "../systems/physics.h"
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
    uint2 *checkpointIds;
    uint2 cpIdCount;
} Level;

typedef struct
{
    uint1 currentLap;
    bool firstIteration;
    uint1 currentCpIndex;
    uint2 currentCp;
} LapTracker;

// Global gamemode module
void LoadCurrentLevel(char *tilemapFile, char *levelFile);
void SetRunningLevelIndex(int levelIndex);
Level *GetRunningLevel(void);
void UnloadCurrentLevel(void);

// Circuit gamemode exclusive module
void InitLapTracker(LapTracker *lap, Level *level);
void RunLapTracker(LapTracker * lap, Level *level, b2ShapeId *targetShape);

#endif
