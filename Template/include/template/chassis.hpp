#pragma once
#include "template_api.hpp"
#include <string>
#include <atomic>

namespace adt {
    class trackingWheel{
        public:
            trackingWheel(vex::rotation &rotationSensor, double wheelDiameter) : _rotationSensor(rotationSensor), _wheelDiameter(wheelDiameter) {};

            void resetPosition(){
                _rotationSensor.resetPosition();
            }

            double position(){
                return _rotationSensor.position(vex::rotationUnits::deg) * (_wheelDiameter * 3.14159265358979323846) / 360.0;
            }
        private:
            vex::rotation &_rotationSensor;
            double _wheelDiameter;

            friend class Chassis;
    };

    struct Pose{
        double x;
        double y;
        double heading; // in degrees

        Pose(double x = 0.0, double y = 0.0, double heading = 0.0) : x(x), y(y), heading(heading) {}

        Pose operator+ (const Pose &other) const {
            return Pose(x + other.x, y + other.y, heading + other.heading);
        }
        Pose operator- (const Pose &other) const {
            return Pose(x - other.x, y - other.y, heading - other.heading);
        }
        Pose operator* (double scalar) const {
            return Pose(x * scalar, y * scalar, heading * scalar);
        }
        Pose operator/ (double scalar) const {
            return Pose(x / scalar, y / scalar, heading / scalar);
        }
        Pose& operator+= (const Pose &other) {
            x += other.x;
            y += other.y;
            heading += other.heading;
            return *this;
        }
        Pose& operator-= (const Pose &other) {
            x -= other.x;
            y -= other.y;
            heading -= other.heading;
            return *this;
        }
        Pose& operator*= (double scalar) {
            x *= scalar;
            y *= scalar;
            heading *= scalar;
            return *this;
        }
        Pose& operator/= (double scalar) {
            x /= scalar;
            y /= scalar;
            heading /= scalar;
            return *this;
        }
    };

    class sensors {
        public:
            sensors(trackingWheel &vertical, trackingWheel &horizontal, vex::inertial &inertialSensor) : _vertical(vertical), _horizontal(horizontal), _inertialSensor(inertialSensor) {};

            enum class odom{
                vertical,
                horizontal
            };

            double getOdomPosition(odom wheel){
                switch(wheel){
                    case odom::vertical:
                        return _vertical.position();
                    case odom::horizontal:
                        return _horizontal.position();
                    default:
                        return 0.0;
                }
            }

            double getInertialHeading(){
                return _inertialSensor.heading();
            }

            void reset(){
                _vertical.resetPosition();
                _horizontal.resetPosition();
                _inertialSensor.resetHeading();
                _inertialSensor.resetRotation();
            }

            void calibrate(){
                _vertical.resetPosition();
                _horizontal.resetPosition();
                _inertialSensor.calibrate(0);
                waitUntil(!_inertialSensor.isCalibrating());
            }

            Pose trackingLogic();
        private:
            trackingWheel &_vertical;
            trackingWheel &_horizontal;
            vex::inertial &_inertialSensor;

            friend class Chassis;
    };

    class chassis{
        public:
            chassis();
        private:

    };
    
}; // namespace adt