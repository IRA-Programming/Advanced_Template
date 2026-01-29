#include "template_api.hpp"
#include "chassis.hpp"

namespace adt {

    Pose sensors::trackingLogic(){
        double previousVertical = 0.0;
        double previousHorizontal = 0.0;
        double previousHeading = 0.0;

        double currentVertical = 0;
        double currentHorizontal = 0;
        double currentHeading = 0;

        double deltaVertical = 0.0;
        double deltaHorizontal = 0.0;
        double deltaHeading = 0.0;

        double v_corr = 0;
        double h_corr = 0;

        double verticalPodOffset = 0; //Distance from robot center to vertical tracking wheel along the robot Y axis
        double horizontalPodOffset = 0; //Distance from robot center to horizontal tracking wheel along

        double local_x;
        double local_y;

        double theta_m;

        double global_dx;

        double global_dy;

        Pose previousPose(0.0, 0.0, 0.0);

        //Step 1: Get Current Sensor Readings
        currentVertical = getOdomPosition(odom::vertical);
        currentHorizontal = getOdomPosition(odom::horizontal);
        currentHeading = _inertialSensor.rotation();

        //Step 2: Get Deltas
        deltaVertical = currentVertical - previousVertical;
        deltaHorizontal = currentHorizontal - previousHorizontal;
        deltaHeading = currentHeading - previousHeading;

        //Step 3: Set current as previous for next iteration
        previousVertical = currentVertical;
        previousHorizontal = currentHorizontal;
        previousHeading = currentHeading;

        v_corr = deltaVertical - (verticalPodOffset * (deltaHeading));
        h_corr = deltaHorizontal - (horizontalPodOffset * (deltaHeading));

        local_x = h_corr;  // right
        local_y = v_corr;  // forward

        /*
        V1:
        theta_m = previousHeading + deltaHeading / 2.0;

        global_dx = local_x * cos(theta_m) - local_y * sin(theta_m);

        global_dy = local_x * sin(theta_m) + local_y * cos(theta_m);
        */
    }

}