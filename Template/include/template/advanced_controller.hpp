#pragma once
#include "template_api.hpp"
#include <functional>
#include <unordered_map>

namespace adt {
    class Controller : public vex::controller {
        public:
            /** 
             * @brief Creates a new Controller object.
            */
            Controller() : vex::controller() {}

            /** 
             * @brief Creates a new Controller object.
             * @param type The type of controller that is being created. This can be set to primary or partner.
            */
            Controller(vex::controllerType type) : vex::controller(type) {}
            
            class Button {
                public:

                    struct ControllerButton {
                            static const int DIGITAL_L1 = 0;
                            static const int DIGITAL_L2 = 1;
                            static const int DIGITAL_R1 = 2;
                            static const int DIGITAL_R2 = 3;
                            static const int DIGITAL_UP = 4;
                            static const int DIGITAL_DOWN = 5;
                            static const int DIGITAL_LEFT = 6;
                            static const int DIGITAL_RIGHT = 7;
                            static const int DIGITAL_X = 8;
                            static const int DIGITAL_B = 9;
                            static const int DIGITAL_Y = 10;
                            static const int DIGITAL_A = 11;
                            static const int DIGITAL_UNDEFINDED = 12;
                    };

                    Button(vex::controller::button button, int mappedButton) : _button(button), mappedButton(mappedButton) {}
                    
                    void onPressed(std::function<void()> callback) {
                        switch (mappedButton) {
                            case static_cast<int>(Controller::Button::ControllerButton::DIGITAL_L1):
                                _button.pressed(trampolineForButtonL1);
                                break;
                            case static_cast<int>(Controller::Button::ControllerButton::DIGITAL_L2):
                                _button.pressed(trampolineForButtonL2);
                                break;
                            case static_cast<int>(Controller::Button::ControllerButton::DIGITAL_R1):
                                _button.pressed(trampolineForButtonR1);
                                break;
                            case static_cast<int>(Controller::Button::ControllerButton::DIGITAL_R2):
                                _button.pressed(trampolineForButtonR2);
                                break;
                            case static_cast<int>(Controller::Button::ControllerButton::DIGITAL_UP):
                                _button.pressed(trampolineForButtonUp);
                                break;
                            case static_cast<int>(Controller::Button::ControllerButton::DIGITAL_DOWN):
                                _button.pressed(trampolineForButtonDown);
                                break;
                            case static_cast<int>(Controller::Button::ControllerButton::DIGITAL_LEFT):
                                _button.pressed(trampolineForButtonLeft);
                                break;
                            case static_cast<int>(Controller::Button::ControllerButton::DIGITAL_RIGHT):
                                _button.pressed(trampolineForButtonRight);
                                break;
                            case static_cast<int>(Controller::Button::ControllerButton::DIGITAL_X):
                                _button.pressed(trampolineForButtonX);
                                break;
                            case static_cast<int>(Controller::Button::ControllerButton::DIGITAL_B):
                                _button.pressed(trampolineForButtonB);
                                break;
                            case static_cast<int>(Controller::Button::ControllerButton::DIGITAL_Y):
                                _button.pressed(trampolineForButtonY);
                                break;
                            case static_cast<int>(Controller::Button::ControllerButton::DIGITAL_A):
                                _button.pressed(trampolineForButtonA);
                                break;
                            case static_cast<int>(Controller::Button::ControllerButton::DIGITAL_UNDEFINDED):
                                _button.pressed(trampolineForButtonUndefined);
                                break;
                            default:
                                break;
                        }
                    }

                    void onReleased(std::function<void()> callback) {
                        switch (mappedButton) {
                            case Controller::Button::ControllerButton::DIGITAL_L1:
                                _button.released(trampolineForButtonL1);
                                break;
                            case Controller::Button::ControllerButton::DIGITAL_L2:
                                _button.released(trampolineForButtonL2);
                                break;
                            case Controller::Button::ControllerButton::DIGITAL_R1:
                                _button.released(trampolineForButtonR1);
                                break;
                            case Controller::Button::ControllerButton::DIGITAL_R2:
                                _button.released(trampolineForButtonR2);
                                break;
                            case Controller::Button::ControllerButton::DIGITAL_UP:
                                _button.released(trampolineForButtonUp);
                                break;
                            case Controller::Button::ControllerButton::DIGITAL_DOWN:
                                _button.released(trampolineForButtonDown);
                                break;
                            case Controller::Button::ControllerButton::DIGITAL_LEFT:
                                _button.released(trampolineForButtonLeft);
                                break;
                            case Controller::Button::ControllerButton::DIGITAL_RIGHT:
                                _button.released(trampolineForButtonRight);
                                break;
                            case Controller::Button::ControllerButton::DIGITAL_X:
                                _button.released(trampolineForButtonX);
                                break;
                            case Controller::Button::ControllerButton::DIGITAL_B:
                                _button.released(trampolineForButtonB);
                                break;
                            case Controller::Button::ControllerButton::DIGITAL_Y:
                                _button.released(trampolineForButtonY);
                                break;
                            case Controller::Button::ControllerButton::DIGITAL_A:
                                _button.released(trampolineForButtonA);
                                break;
                            case Controller::Button::ControllerButton::DIGITAL_UNDEFINDED:
                                _button.released(trampolineForButtonUndefined);
                                break;
                            default:
                                // optional: handle error or fallback
                                break;
                        }
                    }

                    bool isPressed() {
                        return _button.pressing(); 
                    }

                    void toggle(std::function<void()> callback) {
                        if(isPressed() && !_toggleButtonPressed) {
                            _toggleButtonPressed = true;
                            _toggleState = !_toggleState;
                            callback();
                        }

                        if(!isPressed() && _toggleButtonPressed) {
                            _toggleButtonPressed = false;
                        }
                    }
                    
                    void hold(std::function<void()> whenPressed, std::function<void()> whenReleased) {
                        if(isPressed() && !_holdButtonPressed) {
                            _holdButtonPressed = true;
                            whenPressed();
                        }

                        if(!isPressed() && _holdButtonPressed) {
                            _holdButtonPressed = false;
                            whenReleased();
                        }
                    }

                private:
                    vex::controller::button _button;
                    int mappedButton;
                    static std::unordered_map<int, std::function<void()>> callbacks;

                    static void trampolineForButtonL1() {
                        int id = static_cast<int>(Controller::Button::ControllerButton::DIGITAL_L1);
                        if (callbacks.count(id)) callbacks[id]();
                    }

                    static void trampolineForButtonL2() {
                        int id = static_cast<int>(Controller::Button::ControllerButton::DIGITAL_L2);
                        if (callbacks.count(id)) callbacks[id]();
                    }

                    static void trampolineForButtonR1() {
                        int id = static_cast<int>(Controller::Button::ControllerButton::DIGITAL_R1);
                        if (callbacks.count(id)) callbacks[id]();
                    }

                    static void trampolineForButtonR2() {
                        int id = static_cast<int>(Controller::Button::ControllerButton::DIGITAL_R2);
                        if (callbacks.count(id)) callbacks[id]();
                    }

                    static void trampolineForButtonUp() {
                        int id = static_cast<int>(Controller::Button::ControllerButton::DIGITAL_UP);
                        if (callbacks.count(id)) callbacks[id]();
                    }

                    static void trampolineForButtonDown() {
                        int id = static_cast<int>(Controller::Button::ControllerButton::DIGITAL_DOWN);
                        if (callbacks.count(id)) callbacks[id]();
                    }

                    static void trampolineForButtonLeft() {
                        int id = static_cast<int>(Controller::Button::ControllerButton::DIGITAL_LEFT);
                        if (callbacks.count(id)) callbacks[id]();
                    }

                    static void trampolineForButtonRight() {
                        int id = static_cast<int>(Controller::Button::ControllerButton::DIGITAL_RIGHT);
                        if (callbacks.count(id)) callbacks[id]();
                    }

                    static void trampolineForButtonX() {
                        int id = static_cast<int>(Controller::Button::ControllerButton::DIGITAL_X);
                        if (callbacks.count(id)) callbacks[id]();
                    }

                    static void trampolineForButtonB() {
                        int id = static_cast<int>(Controller::Button::ControllerButton::DIGITAL_B);
                        if (callbacks.count(id)) callbacks[id]();
                    }

                    static void trampolineForButtonY() {
                        int id = static_cast<int>(Controller::Button::ControllerButton::DIGITAL_Y);
                        if (callbacks.count(id)) callbacks[id]();
                    }

                    static void trampolineForButtonA() {
                        int id = static_cast<int>(Controller::Button::ControllerButton::DIGITAL_A);
                        if (callbacks.count(id)) callbacks[id]();
                    }

                    static void trampolineForButtonUndefined() {
                        int id = static_cast<int>(Controller::Button::ControllerButton::DIGITAL_UNDEFINDED);
                        if (callbacks.count(id)) callbacks[id]();
                    }


                    bool _toggleState = false;
                    bool _toggleButtonPressed = false;

                    bool _holdButtonPressed = false;
            };
            
            Button CONTROLLER_DIGIAL_L1 = Button(ButtonL1, static_cast<int>(Controller::Button::ControllerButton::DIGITAL_L1));
            Button CONTROLLER_DIGIAL_L2 = Button(ButtonL2, static_cast<int>(Controller::Button::ControllerButton::DIGITAL_L2));
            Button CONTROLLER_DIGIAL_R1 = Button(ButtonR1, static_cast<int>(Controller::Button::ControllerButton::DIGITAL_R1));
            Button CONTROLLER_DIGIAL_R2 = Button(ButtonR2, static_cast<int>(Controller::Button::ControllerButton::DIGITAL_R2));
            Button CONTROLLER_DIGIAL_UP = Button(ButtonUp, static_cast<int>(Controller::Button::ControllerButton::DIGITAL_UP));
            Button CONTROLLER_DIGIAL_DOWN = Button(ButtonDown, static_cast<int>(Controller::Button::ControllerButton::DIGITAL_DOWN));
            Button CONTROLLER_DIGIAL_LEFT = Button(ButtonLeft, static_cast<int>(Controller::Button::ControllerButton::DIGITAL_LEFT));
            Button CONTROLLER_DIGIAL_RIGHT = Button(ButtonRight, static_cast<int>(Controller::Button::ControllerButton::DIGITAL_RIGHT));
            Button CONTROLLER_DIGIAL_X = Button(ButtonX, static_cast<int>(Controller::Button::ControllerButton::DIGITAL_X));
            Button CONTROLLER_DIGIAL_B = Button(ButtonB, static_cast<int>(Controller::Button::ControllerButton::DIGITAL_B));
            Button CONTROLLER_DIGIAL_Y = Button(ButtonY, static_cast<int>(Controller::Button::ControllerButton::DIGITAL_Y));
            Button CONTROLLER_DIGIAL_A = Button(ButtonA, static_cast<int>(Controller::Button::ControllerButton::DIGITAL_A));

            /**
             * @brief Print on the controller at a certain location
             * 
             * @param row The row to print on
             * @param col The column to print on
             * @param format The text to print
             * @param ... Additional arguments for formatting
             */
            void printAt(int row, int col, const char* format, ...) {
                va_list args;
                va_start(args, format);
                this->Screen.setCursor(row, col);
                this->Screen.print(format, args);
                va_end(args);
            }

        };
    
}; // namespace adt