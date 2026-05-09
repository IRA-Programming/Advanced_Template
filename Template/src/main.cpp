/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       ethanvarikkad                                             */
/*    Created:      1/24/2026, 5:41:10 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "v5lvgl.h" //Thanks to jpearman for the help with this!
using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                      Competition Initialize Functions                     */
/*                                                                           */
/*  You may want to perform some actions but only when plugged in to the     */
/*  field control or a competion switch before the competition starts.       */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once when plugged into a competition controller  */
/*  not every time that the robot is connected.                              */
/*---------------------------------------------------------------------------*/

void competition_initialize(void) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                              Disabled Functions                           */
/*                                                                           */
/*  This is not apart of the regular V5 Competition template. Here, you can  */
/*  add code to run when your robot is in the disabled state. This can be    */
/*  useful for doing things such as setting variables to certain values.     */
/*  Do not have your bot physically move during this time.                   */
/*---------------------------------------------------------------------------*/

void disabled(void) {
  // ..........................................................................
  // Insert code to be run when the robot is disabled here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


void BrainSelector(){
    // 1. Create an image object on the active screen
    lv_obj_t* img = lv_img_create(lv_scr_act(), NULL);

    // 2. Set its source to the generated image
    lv_img_set_src(img, &bluewave);

    // 3. Align it on the screen
    lv_obj_align(img, NULL, LV_ALIGN_CENTER, 0, 0);

    // Optional: resize
    // lv_obj_set_size(img, 480, 240);
    lv_obj_t * titleText = nullptr;
    titleText = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(titleText, "Auton A");
    lv_obj_set_style_local_text_font(titleText, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_14);
    lv_obj_align(titleText, NULL, LV_ALIGN_IN_LEFT_MID, 10 , 0);
}


void usercontrol(void) {
  
  while (1) {

    // ..........................................................................
    // Insert code to be run when the robot is in usercontrol
    // ..........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//

int main() {
  //DO NOT REMOVE - ESPECIALY IF YOU ARE USING LVGL
  v5_lv_init(); //Initialize lvgl, this is required to use the display and touch screen.

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // For additional competition-related functions
  COMPETITION_ADDITIONALS
}
