#pragma once
#include "template_api.hpp"
#include <string>
#include <atomic>

// Define pi if not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace adt {
    class trackingWheel{
        public:
            trackingWheel(vex::rotation* rotationSensor, double wheelDiameter) : _rotationSensor(rotationSensor), _wheelDiameter(wheelDiameter) {};

            int32_t resetPosition(){
                if(_rotationSensor == nullptr){
                    return ADT_ERR;
                }
                _rotationSensor->resetPosition();
                return ADT_SUCCESS;
            }

            double position(){
                if(_rotationSensor == nullptr){
                    return ADT_ERR;
                }
                return (_rotationSensor->position(vex::rotationUnits::deg) / 360.0) * (M_PI * _wheelDiameter);
            }
        private:
            vex::rotation* _rotationSensor;
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
            sensors(trackingWheel* vertical, trackingWheel* horizontal, vex::inertial* inertialSensor) : _vertical(vertical), _horizontal(horizontal), _inertialSensor(inertialSensor) {};

            enum class odom{
                vertical,
                horizontal
            };

            double getOdomPosition(odom wheel){
                switch(wheel){
                    case odom::vertical:
                        if(_vertical == nullptr){
                            return ADT_ERR;
                        }
                        return _vertical->position();
                    case odom::horizontal:
                        if(_horizontal == nullptr){
                            return ADT_ERR;
                        }
                        return _horizontal->position();
                    default:
                        return ADT_ERR;
                }
            }

            double getInertialHeading(){
                if(_inertialSensor == nullptr){
                    return ADT_ERR;
                }
                return _inertialSensor->heading();
            }

            int32_t reset(){
                if(_vertical == nullptr && _horizontal == nullptr && _inertialSensor == nullptr){
                    return ADT_ERR;
                }
                if(_vertical != nullptr){
                    _vertical->resetPosition();
                }

                if(_horizontal != nullptr){
                    _horizontal->resetPosition();
                }

                if(_inertialSensor != nullptr){
                    _inertialSensor->resetHeading();
                    _inertialSensor->resetRotation();
                }else{
                    return ADT_ERR;
                }
                return ADT_SUCCESS;
            }

            int32_t calibrate(){
                if(_vertical != nullptr) _vertical->resetPosition();
                if(_horizontal != nullptr) _horizontal->resetPosition();
                if(_inertialSensor == nullptr){
                    return ADT_ERR;
                }
                _inertialSensor->calibrate(0);
                waitUntil(!_inertialSensor->isCalibrating());
                return ADT_SUCCESS;
            }

            void trackingLogic();
        private:
            trackingWheel* _vertical = nullptr;
            trackingWheel* _horizontal = nullptr;
            vex::inertial* _inertialSensor = nullptr;

            Pose previousPose;
            Pose currentPose;

            friend class Chassis;
    };

    class chassis{
        public:
            chassis();
        private:

    };
    
}; // namespace adt