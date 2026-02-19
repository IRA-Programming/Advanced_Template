#include "template_api.hpp"

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

            if(selectButton.isPressed() && !selectPressed){
                selectPressed = true;
                autonSelected = true;
                noAuton = false;
                break;
            }

            if(!selectButton.isPressed() && selectPressed){
                selectPressed = false;
            }

            if(noAutonButton.isPressed() && !noAutonPressed){
                noAutonPressed = true;
                autonSelected = true;
                noAuton = true;
                break;
            }

            if(!noAutonButton.isPressed() && noAutonPressed){
                noAutonPressed = false;
            }
            
        }

        return autons[i].getAutonStructure();
    }
};