#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "stateList.h"

#define REPLACE (1 << 0)
#define POP     (1 << 1)

int RunStateStack(void);

#endif
