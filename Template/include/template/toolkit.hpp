#pragma once
#include "vex.h"
#include "template_api.hpp"
#include <functional>

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


#define COMPETITION_ADDITIONALS \
while (true) { \
    static bool competitionInitRan = false; \
    if(Competition.DISABLED) disabled(); \
    bool isCompetitionControlled = Competition.isCompetitionSwitch() || Competition.isFieldControl(); \
    if(!competitionInitRan && isCompetitionControlled){ \
      competition_initialize(); \
      competitionInitRan = true; \
    } \
    wait(100, msec); \
  } \

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
            // static void errorHandler(std::function<void()> toRun, std::function<void()> onError = [](){}) {
            //     try {
            //         toRun();
            //     } catch (const std::exception& e) {
            //         onError();
            //     }
            // }

            /**
             * @brief Allows you to run code and catch any exceptions that may occur so that it won't crash your program.
             * 
             * @param toRun Code to run that may cause an exception.
             * @param onError Code to run if an exception occurs. Must take in an exception as a parameter.
             */
            // static void errorHandler(std::function<void()> toRun, std::function<void(std::exception e)> onError) {
            //     try {
            //         toRun();
            //     } catch (const std::exception& e) {
            //         onError(e);
            //     }
            // }

            /**
             * @brief Allows the user to run code once if a button is pressed. Switches between 2 callbacks.
             * 
             * @param button The button to check if it is pressed
             * @param callback1 The function to run when button is pressed an odd number of times [1, inf).
             * @param callback2 The function to run when button is pressed an even number of times [2, inf).
             */
            static void toggleButtonScheme(vex::controller::button &button, std::function<void()> callback1, std::function<void()> callback2){
                toggleButtonScheme(button, [&](){
                    static bool status = false;
                    status = !status;
                    if(status){
                        callback1();
                    }else{
                        callback2();
                    }
                });
                
            }

            /**
             * @brief Allows the user to run code once if a button is pressed
             * 
             * @param button The button to check if it is pressed
             * @param callback The function to run when the button is pressed
             * @note Could use mevent instead of current logic for simplification
             */
            static void toggleButtonScheme(vex::controller::button &button, std::function<void()> callback) {
                static bool buttonPressed = false; //Use static to retain the value of buttonPressed between function calls
                if(button.pressing() && !buttonPressed){
                    callback();
                }
                if(!button.pressing() && buttonPressed){
                    buttonPressed = false;
                }
            }

            static void waitUntilOneComplete(std::function<void()> callback1, std::function<void()> callback2, bool forceStop = false){
                std::atomic<bool> complete;
                complete.store(false);
                std::function<void()> c1 = [&](){
                    callback1();
                    complete.store(true);
                };

                std::function<void()> c2 = [&](){
                    callback2();
                    complete.store(true);
                };

                adt::Thread thread1(c1);

                adt::Thread thread2(c2);

                do{
                    wait(5, vex::msec);
                }while(complete.load() == false);

            }
    };
};