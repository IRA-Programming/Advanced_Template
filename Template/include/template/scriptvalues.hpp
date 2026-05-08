#pragma once
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    DO NOT TOUCH THIS FILE!                                                 */
/*    This file may be modified by scripts in order to run certain aspects    */
/*    of your project. It is strongly advised not to modify this file         */
/*    manually, unless you know what you are doing.                           */
/*    Additionally, do not move the location of this file. It must always be  */
/*    located in projectroot/include/template/                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "v5lvgl.h"
#include "template_api.hpp"

// Run Induvidual Aspects of the Competition Code
//Run only the autonomous code
#define AUTON_ONLY = 0 
//Run only the driver control code
#define DRIVER_ONLY = 0
//Run only the pre-autonomous code
#define PREAUTON_ONLY = 0
//Run only the disabled code
#define DISABLED_ONLY = 0
//Run only the competition initialize code
#define COMPETITIONINIT_ONLY = 0

// Modify how competion functions (NON VEX PROVIDED) are handled
//If set to 1, the competition_initialize() function will only run once when the robot is first connected to the field control or competition switch. 
//If set to 0, the competition_initialize() function will run every time the robot connected to field control or competition switch.
#define RUN_COMPETITION_INIT_ONCE = 1
//Disables all non-vex additional functions
#define DISABLE_ADDITIONAL_FUNCTIONS = 0

// Mini-Field Control
// Allow to run all aspects of the competition code without being connected to a field control or competition switch.
#define MINI_FIELD_CONTROL = 0
#define PREAUTON_PERIOD = 60 //Time in seconds for the pre-autonomous period
#define COMPETITION_INIT_PERIOD = 30 //Time in seconds for the competition initialize period
#define AUTON_PERIOD = 15 //Time in seconds for the autonomous period
#define DRIVER_PERIOD = 105 //Time in seconds for the driver control period
#define DISABLED_PERIOD = 45 //Time in seconds for the disabled period

// Value Management
//Allow for the use of script values. 
#define SCRIPT_VALUES = 1
//Reset all script values to default when the program is built without the flag.
#define RESET_ON_BUILD = 1