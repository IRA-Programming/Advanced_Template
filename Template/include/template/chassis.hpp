#pragma once
#include "template_api.hpp"
#include <string>
#include <atomic>
#include <functional>

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

        double radians() const {
            return heading * (M_PI / 180.0);
        }

        Pose(double x = 0.0, double y = 0.0, double heading = 0.0, bool radians = false) : x(x), y(y){
            if(radians){
                this->heading = heading * (180.0 / M_PI);
            }else{
                this->heading = heading;
            }
        }

        Pose(const Pose& other) : x(other.x), y(other.y), heading(other.heading) {}
        

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
            sensors(trackingWheel* vertical, trackingWheel* horizontal, vex::inertial* inertialSensor, double verticalOffset, double horizontalOffset) : _vertical(vertical), _horizontal(horizontal), _inertialSensor(inertialSensor), vTrackingOffset(verticalOffset), hTrackingOffset(horizontalOffset) {};

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

            double previousVerticalPosition = 0.0;
            double previousHorizontalPosition = 0.0;
            double previousHeading = 0.0;

            double vTrackingOffset = 0.0;
            double hTrackingOffset = 0.0;

            Pose previousPose;
            Pose currentPose;

            friend class Chassis;
    };

    class chassis{
        public:
            chassis();
        private:
            struct _driveOutputs
            {
                double kLeftSpeed = NULL;
                double kRightSpeed = NULL;

                std::function<void()> fLeftSpeed = nullptr;
                std::function<void()> fRightSpeed = nullptr;
            };
            
            /**
             * @brief The movement logic for the chassis, used to calculate the necessary outputs to move the chassis to a target pose. Uses the current pose of the chassis and a target pose to calculate the necessary outputs to move the chassis to the target pose.
             * 
             * @param targetPose Target Pose (in local coordinates) for the chassis to move to
             * @return _driveOutputs 
             */
            _driveOutputs movementLogic(Pose targetPose);
    };
    
}; // namespace adt