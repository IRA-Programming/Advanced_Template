#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

// Include Template Header Files
#include "template/template_api.hpp"

#include "robot_config.hpp"


#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, vex::timeUnits::msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)