#pragma once
#include "template_api.hpp"

using namespace adt;

namespace adt {
    class Omniwheel {
        static constexpr float NEW_2 = 2.125;
        static constexpr float NEW_275 = 2.75;
        static constexpr float OLD_275 = 2.75;
        static constexpr float NEW_275_HALF = 2.744;
        static constexpr float OLD_275_HALF = 2.74;
        static constexpr float NEW_325 = 3.25;
        static constexpr float OLD_325 = 3.25;
        static constexpr float NEW_325_HALF = 3.246;
        static constexpr float OLD_325_HALF = 3.246;
        static constexpr float NEW_4 = 4;
        static constexpr float OLD_4 = 4.18;
        static constexpr float NEW_4_HALF = 3.995;
        static constexpr float OLD_4_HALF = 4.175;
    }; // namespace Omniwheel

    //==============================================================================
    
    /** 
     * @brief A struct to represent gear ratios
     * 
     */
    struct gearRatio{
        int output;
        int input;

        /** 
         * @brief Construct a new gear Ratio object
         * 
         * @param output The output gear teeth count
         * @param input The input gear teeth count
         */
        gearRatio(int outputGear, int inputGear) : output(outputGear), input(inputGear) {}

        operator double() const {
            return static_cast<double>(output) / static_cast<double>(input);
        }
    };

    //==============================================================================

    /** 
     * @brief A template class to represent a drive curve
     * 
     */
    class drivecurve{
        public:

            /** 
             * @brief Destroy the drivecurve object
             * 
             */
            ~drivecurve(){}

            /** 
             * @brief A function to apply a curve to an input value
             * @note This is a placeholder function and should be overridden in derived classes
             * 
             * @param input The input value to be curved
             * @return double The curved output value
             */
            virtual double curve(double input) const = 0;

        private:
    };

    class linearDrivecurve : public drivecurve {
        public:
            /** 
             * @brief Construct a new linear Drivecurve object
             * 
             */
            linearDrivecurve() {}

            /** 
             * @brief Apply a linear curve to the input value
             * 
             * @param input The input value to be curved
             * @return double The curved output value
             */
            double curve(double input) const override {
                return input;
            }
    };

    struct TankDriveParams;
    struct ArcadeDriveParams;

    class drivetrain{
        public:
            /**
             * @brief Construct a new drivetrain object
             * 
             * @param leftMotors The motors on the left side of the drivetrain
             * @param rightMotors The motors on the right side of the drivetrain
             * @param wheelDiameter The diameter of the wheels in inches or the omniwheel used in the drivetrain
             * @param gearRatio The gear ratio of the drivetrain as a double or a gearRatio struct
            */
            drivetrain(vex::motor_group leftMotors, vex::motor_group rightMotors, double wheelDiameter, double gearRatio): 
                _leftMotors(leftMotors), 
                _rightMotors(rightMotors), 
                _wheelDiameter(wheelDiameter), 
                _gearRatio(gearRatio) {};



            void drive_tank(int leftPower, int rightPower, TankDriveParams params);

            void drive_arcade(int forwardPower, int turnPower, ArcadeDriveParams params);

            static linearDrivecurve _defaultCurve;

        private:
            vex::motor_group _leftMotors;
            vex::motor_group _rightMotors;
            double _wheelDiameter;
            double _gearRatio;

            friend class Chassis;
    };

    struct TankDriveParams{
        /** 
         * @brief The section of joystick input that is considered as zero input/stop
         * 
         */
        double deadband = 0.0;

        /**
         * @brief The brake type to use when stopping the drivetrain
         * 
         */
        vex::brakeType brakeType = vex::brakeType::coast;

        /** 
         * @brief The maximum output value for the drivetrain
         * @note Should be between 0 and 100 percent
         * @note Scales, not clamps, so the max output will be mapped to 100 percent input
         * 
         */
        double maxOutput = 100.0;

        /** 
         * @brief The minimum output value for the drivetrain when the joystick is moved beyond the deadband.
         * @note Only applies when using a deadband greater than 0
         * 
         */
        double minMovingOutput = 0.0;

        /** 
         * @brief A pointer to a drivecurve object to apply a curve to the joystick input
         * 
         */
        const drivecurve* curve = &adt::drivetrain::_defaultCurve;
    };

    struct ArcadeDriveParams {
        /** 
         * @brief The section of joystick input that is considered as zero input/stop
         * 
         */
        double deadband = 0.0;

        /**
         * @brief The brake type to use when stopping the drivetrain
         * 
         */
        vex::brakeType brakeType = vex::brakeType::coast;

        /** 
         * @brief The maximum output value for the drivetrain
         * @note Should be between 0 and 100 percent
         * @note Scales, not clamps, so the max output will be mapped to 100 percent input
         * 
         */
        double maxOutput = 100.0;

        /** 
         * @brief The minimum output value for the drivetrain when the joystick is moved beyond the deadband.
         * @note Only applies when using a deadband greater than 0
         * 
         */
        double minMovingOutput = 0.0;

        /** 
         * @brief A pointer to a drivecurve object to apply a curve to the forward joystick input
         * 
         */
        const drivecurve* forwardCurve = &adt::drivetrain::_defaultCurve;

        /** 
         * @brief A pointer to a drivecurve object to apply a curve to the turn joystick input
         * 
         */
        const drivecurve* turnCurve = &adt::drivetrain::_defaultCurve;
    };
    
    
}; // namespace adt