#include "template_api.hpp"
#include "v5lvgl.h"
#include "vex.h"

namespace adt {
    Autons::AutonReturnType AutonSelector::AutonSelector1(){

        bool autonSelected = false;
        bool noAuton = false;

        //Create each page (per auton) stored as a vector of functions to run when that page is selected
        std::vector<std::function<void()>> pages;
        for (const adt::Autons &auton : autons){
            std::function<void()> page = [&](){
                controller.Screen.clearScreen();
                controller.Screen.setCursor(1,1);
                controller.Screen.print("Auton %s", auton.getAutonStructure().asIdentifier.c_str());
                controller.Screen.setCursor(3,1);
                controller.Screen.print("%s", auton.getAutonStructure().asName.c_str());
            };
            pages.push_back(page);
        }
        
        bool leftPressed = false;
        bool rightPressed = false;
        bool selectPressed = false;
        bool noAutonPressed = false;
        int i = 0;
        while(!autonSelected){
            if(controller.ButtonLeft.pressing() && !leftPressed){
                leftPressed = true;
                i--;
                if(i < 0){
                    i = pages.size() - 1;
                }
                pages[i]();
            }

            if(!controller.ButtonLeft.pressing() && leftPressed){
                leftPressed = false;
            }

            if(controller.ButtonRight.pressing() && !rightPressed){
                rightPressed = true;
                i++;
                if(i >= pages.size()){
                    i = 0;
                }
                pages[i]();
            }

            if(!controller.ButtonRight.pressing() && rightPressed){
                rightPressed = false;
            }

            if(selectButton.pressing() && !selectPressed){
                selectPressed = true;
                autonSelected = true;
                noAuton = false;
                break;
            }

            if(!selectButton.pressing() && selectPressed){
                selectPressed = false;
            }

            if(noAutonButton.pressing() && !noAutonPressed){
                noAutonPressed = true;
                autonSelected = true;
                noAuton = true;
                break;
            }

            if(!noAutonButton.pressing() && noAutonPressed){
                noAutonPressed = false;
            }
            
        }

        return autons[i].getAutonStructure();
    }
};

lv_obj_t * myButton;
lv_obj_t * myButtonLabel;
lv_obj_t * myLabel;

static void btn_click_action(lv_obj_t * btn, lv_event_t event)
{
    uint8_t id = (int)lv_obj_get_user_data(btn); //id usefull when there are multiple buttons

    if(id == 0 && event == LV_EVENT_CLICKED)
    {
  		lv_label_set_text(myLabel, "clicked");
    }

    return ;
}


int demo() {
   static lv_style_t style1;
   lv_style_set_bg_color(&style1, LV_STATE_DEFAULT, LV_COLOR_WHITE);
   lv_style_set_bg_color(&style1, LV_STATE_PRESSED, LV_COLOR_GRAY);
   lv_style_set_bg_color(&style1, LV_STATE_FOCUSED, LV_COLOR_RED);
   lv_style_set_bg_color(&style1, LV_STATE_FOCUSED | LV_STATE_PRESSED, lv_color_hex(0xf88));

   myButton = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
   lv_obj_set_user_data(myButton, (lv_font_user_data_t)0); //set button is to 0
   lv_obj_set_event_cb(myButton, btn_click_action); //set function to be called on button click
   lv_obj_add_style(myButton, LV_OBJ_PART_MAIN, &style1);
   lv_obj_set_size(myButton, 200, 50); //set the button size
   lv_obj_align(myButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10); //set the position to top mid

    myButtonLabel = lv_label_create(myButton, NULL); //create label and puts it inside of the button
    lv_label_set_text(myButtonLabel, "Click the Button"); //sets label text

    myLabel = lv_label_create(lv_scr_act(), NULL); //create label and puts it on the screen
    lv_label_set_text(myLabel, "Button has not been clicked yet"); //sets label text
    lv_obj_align(myLabel, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0); //set the position to center

    return(0);
}