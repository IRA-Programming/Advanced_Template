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
    template <typename Mass = std::ratio<0>, typename Length = std::ratio<0>, typename Time = std::ratio<0>,
          typename Current = std::ratio<0>, typename Angle = std::ratio<0>, typename Temperature = std::ratio<0>,
          typename Luminosity = std::ratio<0>, typename Moles = std::ratio<0>>
    class Unit {
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
            using Self = Unit<Mass, Length, Time, Current, Angle, Temperature, Luminosity, Moles>;

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
                requires(!std::is_same_v<Self, Dimensionless>)
                : value(value) {}

            constexpr Unit(double value)
                requires std::is_same_v<Self, Dimensionless>
                : value(value) {}

            

            /**
             * @brief Double value, must be dimentionless
             * @return the value as double
             */
            operator double() const requires std::is_same_v<Self, Dimensionless>{
                return value;
            }

            operator std::string() const {
                std::string unit = "";
                return std::to_string(value);
            }

            Self operator +( const Self& other ) const {
                return Self(value + other.value);
            }

            Self operator -( const Self& other ) const {
                return Self(value - other.value);
            }

            

    };
}