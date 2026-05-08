#include "vex.h"
#include "robot_config.hpp"

using namespace vex;

brain Brain;
controller Controller;
motor chainMotor(PORT1, ratio18_1, false);
motor wheelMotor(PORT2, ratio18_1, true);

distance distanceSensor(PORT3);
bumper bumperSensor(Brain.ThreeWirePort.A);