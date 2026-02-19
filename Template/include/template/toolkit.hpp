#include "vex.h"
#include "template_api.hpp"

/**
 * @file toolkit.hpp
 * @brief Tookit is used to assist in tasks by creating simpler functions to complete them.
 */


//Tookit Marcos
#define TOOLKIT_SCOPE_LOCK(myMutex) \
    auto _toolkit_guard_##__LINE__ = myMutex.assign_scope_lock()

#define WAIT_UNTIL_TIMEOUT(condition, timeoutMs)                                         \
    {                                                                                    \
        int WAIT_UNTIL_TIMEOUT_IRERATIOR_COUNT_____ = 0;                                 \
        do {                                                                             \
            wait(5, vex::timeUnits::msec);                                               \
            WAIT_UNTIL_TIMEOUT_IRERATIOR_COUNT_____ += 5;                                \
        } while (!(condition) && (WAIT_UNTIL_TIMEOUT_IRERATIOR_COUNT_____ < timeoutMs)); \
    }


//Toolkit Class
namespace adt {
    /**
     * @brief TOOKKIT class that contains various utility functions and classes.
     */
    class TOOLKIT {
        public:
            TOOLKIT() {}
            
            /** 
             * @brief A helper function to create a chassis object with default parameters.
             * 
             * @return adt::chassis A chassis object with default parameters.
             */
            static adt::chassis createChassis(
                
            ) {
                return adt::chassis();
            }
            /**
             * @brief Allows you to run code and catch any exceptions that may occur so that it won't crash your program.
             * 
             * @param toRun Code to run that may cause an exception.
             * @param onError Optional Parameter that allows you to run code if an exception occurs. Defaults to an empty function.
             */
            static void errorHandler(std::function<void()> toRun, std::function<void()> onError = [](){}) {
                try {
                    toRun();
                } catch (const std::exception& e) {
                    onError();
                }
            }

            /**
             * @brief Allows you to run code and catch any exceptions that may occur so that it won't crash your program.
             * 
             * @param toRun Code to run that may cause an exception.
             * @param onError Code to run if an exception occurs. Must take in an exception as a parameter.
             */
            static void errorHandler(std::function<void()> toRun, std::function<void(std::exception e)> onError) {
                try {
                    toRun();
                } catch (const std::exception& e) {
                    onError(e);
                }
            }

        private:
    };
};