#pragma once
#include "vex.h"

// Similar to PROS, error logic for easy error handling.

#define ADT_ERR (INT32_MAX)
#define ADT_SUCCESS (1)

#include "chassis.hpp"
#include "drivetrain.hpp"
#include "advanced_controller.hpp"
#include "advanced_thread.hpp"
#include "toolkit.hpp"
#include "auton_selector.hpp"