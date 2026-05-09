#pragma once
#include "template_api.hpp"

/********************
 * @file units.hpp
 * @brief This file contains various unit conversion functions and constants.
 * @note Concept, probably not going to be used
 * @note From LemLib
 * @warning Work in progress, not fully implemented, and may contain errors. Use with caution.
 ********************/

namespace adt {
    template <typename Scale = std::ratio<1>, typename Mass = std::ratio<0>, typename Length = std::ratio<0>, typename Time = std::ratio<0>,
          typename Current = std::ratio<0>, typename Angle = std::ratio<0>, typename Temperature = std::ratio<0>,
          typename Luminosity = std::ratio<0>, typename Moles = std::ratio<0>>
    class Unit {
        double baseValue = 1; //Base value of unit (e.g. for length, this would be in meters). Default as base value
        double value; //The pure numeric value of the unit
        public:
            typedef Mass mass;
            typedef Length length;
            typedef Time time;
            typedef Current current;
            typedef Angle angle;
            typedef Temperature temperature;
            typedef Luminosity luminosity;
            typedef Moles moles;
            /**
             * @brief Definition of Self
             * @details This is the base unit the class is representing
             */
            using Self = Unit<Scale, Mass, Length, Time, Current, Angle, Temperature, Luminosity, Moles>;

            /**
             * @brief Definition of Dimensionless
             */
            using Dimensionless = Unit<>;

            /**
             * @brief construct a new Quantity object
             *
             * This constructor initializes the value to 0
             */
            explicit constexpr Unit()
                : value(0) {}

            /**
             * @brief construct a new Quantity object
             *
             * @param value the value to initialize the quantity with
             */
            explicit constexpr Unit(double value)
                requires (!std::is_same_v<Self, Dimensionless>)
                : value(value) {}

            constexpr Unit(double value) 
                requires (std::is_same_v<Self, Dimensionless>) 
                : value(value) {}
            
            /**
             * @brief Return Raw Value
             * 
             * @return double 
             */
            double raw() const {
                return value;
            }

            /**
             * @brief Double value
             * @return the value as double
             * @warning Drops the units
             */
            operator double() const {
                return value;
            }

            operator std::string() const {
                std::string unit = "";
                return std::to_string(value);
            }

            template<typename OtherScale>

            Self operator+(
                const Unit<
                    OtherScale,
                    Mass,
                    Length,
                    Time,
                    Current,
                    Angle,
                    Temperature,
                    Luminosity,
                    Moles
                >& other
            ) const {
                using Conversion =
                    std::ratio_divide<
                        OtherScale,
                        Scale
                    >;

                double converted =
                    other.raw() *
                    static_cast<double>(Conversion::num) /
                    static_cast<double>(Conversion::den);

                return Self(value + converted);
            }

            template<typename OtherScale>
            Self operator+(
                const Unit<
                    OtherScale,
                    Mass,
                    Length,
                    Time,
                    Current,
                    Angle,
                    Temperature,
                    Luminosity,
                    Moles
                >& other
            ) const {
                using Conversion =
                    std::ratio_divide<
                        OtherScale,
                        Scale
                    >;

                double converted =
                    other.raw() *
                    static_cast<double>(Conversion::num) /
                    static_cast<double>(Conversion::den);

                return Self(value - converted);
            }

    };
}

// Define base units
using Meter = adt::Unit<std::ratio<1>, std::ratio<0>, std::ratio<1>>;
using Second = adt::Unit<std::ratio<1>, std::ratio<0>, std::ratio<0>, std::ratio<1>>;
using Ampere = adt::Unit<std::ratio<1>, std::ratio<0>, std::ratio<0>, std::ratio<1>>;
using Radian = adt::Unit<std::ratio<1>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>;
using Kelvin = adt::Unit<std::ratio<1>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>;
using Candela = adt::Unit<std::ratio<1>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>;
using Mole = adt::Unit<std::ratio<1>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>;
using Kilogram = adt::Unit<std::ratio<1>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>>;
using Dimensionless = adt::Unit<>;

