#include "template_api.hpp"
#include "chassis.hpp"

#define TO_RAD(x) ((x) * (M_PI / 180.0))
#define TO_DEG(x) ((x) * (180.0 / M_PI))

namespace adt {

    void sensors::trackingLogic(){

        while (true) {
            double verticalPosition = _vertical->position() - previousVerticalPosition;
            double horizontalPosition = _horizontal->position() - previousHorizontalPosition;
            double heading = TO_RAD(_inertialSensor->heading()) - previousHeading;

            double x,y = 0;

            if(heading != 0){
                double radius = (verticalPosition / heading) + vTrackingOffset;

                y = radius * sin(heading);

                x = -radius * (cos(heading) - 1);
            }else{
                x = verticalPosition;
                y = horizontalPosition;
            }
        }

    }

    chassis::_driveOutputs chassis::movementLogic(Pose targetPose){

        if(targetPose.x == 0 && targetPose.y == 0){
            //return go forward
            return chassis::_driveOutputs();
        }

        double radius = fabs(-(sqrt(pow(targetPose.x, 2) + pow(targetPose.y, 2))/(2 * targetPose.x)));

        //if side is -, then robot is going to turn right, else left
        double side = (-(sqrt(pow(targetPose.x, 2) + pow(targetPose.y, 2))/(2 * targetPose.x))/(fabs(-(sqrt(pow(targetPose.x, 2) + pow(targetPose.y, 2)))/(2 * targetPose.x))));

        
        
        return chassis::_driveOutputs();
    }

}