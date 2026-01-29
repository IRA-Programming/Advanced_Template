#include "template_api.hpp"
#include "drivetrain.hpp"
#include <cmath>
#include <algorithm>

namespace adt {

    void drivetrain::drive_tank(int leftPower, int rightPower, TankDriveParams params){
        double leftSpeed = 0.0;
        double rightSpeed = 0.0;
        // Ensure curve pointer is valid, just in case
        if(params.curve == nullptr){
            params.curve = &drivetrain::_defaultCurve;
        }

        if(params.deadband > 0.0){
            // Apply deadband and min moving output to left power
            if(fabs(leftPower) <= params.deadband){
                _leftMotors.stop(params.brakeType);
            } else {
                double sign = leftPower > 0 ? 1.0 : -1.0;
                double mag = (std::abs(leftPower) - params.deadband) / (100.0 - params.deadband) * 100.0;

                double curved = params.curve->curve(mag); // curve expects 0..100

                //clamp
                curved = (curved < 0.0) ? 0.0 : (curved > 100.0) ? 100.0 : curved;

                double scaled = params.minMovingOutput + (curved / 100.0) * (params.maxOutput - params.minMovingOutput);

                leftSpeed = sign * scaled;
            }

            if(fabs(rightPower) <= params.deadband){
                _rightMotors.stop(params.brakeType);
            } else {
                double sign = rightPower > 0 ? 1.0 : -1.0;
                double mag = (std::abs(rightPower) - params.deadband) / (100.0 - params.deadband) * 100.0;
                double curved = params.curve->curve(mag); // curve expects 0..100

                //clamp
                curved = (curved < 0.0) ? 0.0 : (curved > 100.0) ? 100.0 : curved;

                double scaled = params.minMovingOutput + (curved / 100.0) * (params.maxOutput - params.minMovingOutput);

                rightSpeed = sign * scaled;
            }

            _leftMotors.spin(vex::directionType::fwd, leftSpeed, vex::velocityUnits::pct);
            _rightMotors.spin(vex::directionType::fwd, rightSpeed, vex::velocityUnits::pct);

        } else {
            double rightSpeed = 0;
            double leftSpeed = 0;

            double sign = leftPower > 0 ? 1.0 : -1.0;
            double mag = (std::abs(leftPower) - params.deadband) / (100.0 - params.deadband) * 100.0;

            double curved = params.curve->curve(mag); // curve expects 0..100

            //clamp
            curved = (curved < 0.0) ? 0.0 : (curved > 100.0) ? 100.0 : curved;

            double scaled = 0 + (curved / 100.0) * (params.maxOutput - 0);

            leftSpeed = sign * scaled;

            sign = rightPower > 0 ? 1.0 : -1.0;
            mag = (std::abs(rightPower) - params.deadband) / (100.0 - params.deadband) * 100.0;

            curved = params.curve->curve(mag); // curve expects 0..100

            //clamp
            curved = (curved < 0.0) ? 0.0 : (curved > 100.0) ? 100.0 : curved;

            scaled = 0 + (curved / 100.0) * (params.maxOutput - 0);

            rightSpeed = sign * scaled;

            _leftMotors.spin(vex::directionType::fwd, leftSpeed, vex::velocityUnits::pct);
            _rightMotors.spin(vex::directionType::fwd, rightSpeed, vex::velocityUnits::pct);

        }
    }

    void drivetrain::drive_arcade(int forwardPower, int turnPower, ArcadeDriveParams params){
        double forwardSpeed = 0.0;
        double turnSpeed = 0.0;

        // Ensure curve pointer is valid, just in case
        if(params.forwardCurve == nullptr){
            params.forwardCurve = &drivetrain::_defaultCurve;
        }

        if(params.turnCurve == nullptr){
            params.turnCurve = &drivetrain::_defaultCurve;
        }

        if(params.deadband > 0.0){
            // Apply deadband and min moving output to left power
            if(fabs(forwardPower) <= params.deadband){
                forwardSpeed = 0.0;
            } else {
                double sign = forwardPower > 0 ? 1.0 : -1.0;
                double mag = (std::abs(forwardPower) - params.deadband) / (100.0 - params.deadband) * 100.0;

                double curved = params.forwardCurve->curve(mag); // curve expects 0..100

                //clamp
                curved = (curved < 0.0) ? 0.0 : (curved > 100.0) ? 100.0 : curved;

                double scaled = params.minMovingOutput + (curved / 100.0) * (params.maxOutput - params.minMovingOutput);

                forwardSpeed = sign * scaled;
            }

            if(fabs(turnPower) <= params.deadband){
                turnSpeed = 0.0;
            } else {
                double sign = turnPower > 0 ? 1.0 : -1.0;
                double mag = (std::abs(turnPower) - params.deadband) / (100.0 - params.deadband) * 100.0;
                double curved = params.turnCurve->curve(mag); // curve expects 0..100

                //clamp
                curved = (curved < 0.0) ? 0.0 : (curved > 100.0) ? 100.0 : curved;

                double scaled = params.minMovingOutput + (curved / 100.0) * (params.maxOutput - params.minMovingOutput);

                turnSpeed = sign * scaled;
            }

            if(forwardSpeed == 0 && turnSpeed == 0){
                _leftMotors.stop(params.brakeType);
                _rightMotors.stop(params.brakeType);
                return;
            }

            _leftMotors.spin(vex::directionType::fwd, forwardSpeed + turnSpeed, vex::velocityUnits::pct);
            _rightMotors.spin(vex::directionType::fwd, forwardSpeed - turnSpeed, vex::velocityUnits::pct);

        } else {
            double forwardSpeed = 0;
            double turnSpeed = 0;

            double sign = forwardPower > 0 ? 1.0 : -1.0;
            double mag = (std::abs(forwardPower) - params.deadband) / (100.0 - params.deadband) * 100.0;

            double curved = params.forwardCurve->curve(mag); // curve expects 0..100

            //clamp
            curved = (curved < 0.0) ? 0.0 : (curved > 100.0) ? 100.0 : curved;

            double scaled = 0 + (curved / 100.0) * (params.maxOutput - 0);

            forwardSpeed = sign * scaled;

            sign = turnPower > 0 ? 1.0 : -1.0;
            mag = (std::abs(turnPower) - params.deadband) / (100.0 - params.deadband) * 100.0;

            curved = params.turnCurve->curve(mag); // curve expects 0..100

            //clamp
            curved = (curved < 0.0) ? 0.0 : (curved > 100.0) ? 100.0 : curved;

            scaled = 0 + (curved / 100.0) * (params.maxOutput - 0);

            turnSpeed = sign * scaled;

            _leftMotors.spin(vex::directionType::fwd, forwardSpeed + turnSpeed, vex::velocityUnits::pct);
            _rightMotors.spin(vex::directionType::fwd, forwardSpeed - turnSpeed, vex::velocityUnits::pct);

        }
    }

}