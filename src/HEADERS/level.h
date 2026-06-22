#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <string.h>
#include <stdlib.h>

#include "raylib.h"
#include "cJSON/cJSON.h"

#include "utils.h"

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
    meduint spawnpointId;
    meduint *checkpointIds; // TODO: later fix this member allocation type
    meduint cpIdCount;
} Level;

// Game mode exclusive objects //
typedef struct
{
    smalluint currentLap;
    smalluint currentCp;
} LapTracker;

void LoadCurrentLevel(char *tilemapFile, char *levelFile);
void SetRunningLevelIndex(int levelIndex);
Level *GetRunningLevel(void);

// Game mode exclusive funstions
void InitLapTracker(LapTracker *lap, Level *level);

#endif
