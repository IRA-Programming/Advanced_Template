#include "template_api.hpp"

namespace adt::lvgl {
    class Button{
        public:

        Button() = default;
        /**
         * Create a button object
         * @param par pointer to an object, it will be the parent of the new button
         * @param copy pointer to a button object, if not NULL then the new object will be copied from it
         * @return pointer to the created button
         */
        Button(lv_obj_t *parent, lv_obj_t *copy){
            _parent = parent;
            _copy = copy;
            _button = lv_btn_create(parent, copy);
        }

        void align(lv_obj_t *base, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs){
            lv_obj_align(_button, base, align, x_ofs, y_ofs);
        }

        void addStyle(uint8_t part, lv_style_t *style){
            lv_obj_add_style(_button, part, style);
        }

        void setSize(lv_coord_t w, lv_coord_t h){
            lv_obj_set_size(_button, w, h);
        }

        void align(lv_align_t align = LV_ALIGN_CENTER, lv_coord_t x_ofs = 0, lv_coord_t y_ofs = 0, const lv_obj_t *base = NULL){
            lv_obj_align(_button, base, align, x_ofs, y_ofs);
        }

        operator lv_obj_t* () {
            return _button;
        }

        struct setActionStruct{
            Button* STRUCT_BUTTON___ = nullptr;
            
            int32_t setEvent(std::function<void()> action, lv_event_t when = LV_EVENT_CLICKED){
                STRUCT_BUTTON___->buttonCb = action;
                std::function<void(lv_obj_t*, lv_event_t)> func = [action, when](lv_obj_t * btn, lv_event_t event){
                    if(event == when){
                        action();
                    }
                };

                if(func.target<lv_event_cb_t>() == nullptr){
                    STRUCT_BUTTON___->buttonCbWLVGLFormatted = NULL;
                    return ADT_ERR;
                }

                lv_event_cb_t funcPtr = *func.target<lv_event_cb_t>();
                STRUCT_BUTTON___->buttonCbWLVGLFormatted = funcPtr;

                lv_obj_set_event_cb(*STRUCT_BUTTON___, funcPtr);
            }

            struct getEventMethods{
                Button* STRUCT_BUTTON___ = nullptr;
                std::function<void()> asFunc(){
                    return this->STRUCT_BUTTON___->buttonCb;
                }

                lv_event_cb_t asLVGLFormat(){
                    if(this->STRUCT_BUTTON___->buttonCbWLVGLFormatted == NULL || this->STRUCT_BUTTON___->buttonCbWLVGLFormatted == nullptr){
                        return NULL;
                    }
                    return this->STRUCT_BUTTON___->buttonCbWLVGLFormatted;
                }

                getEventMethods(Button* button) : STRUCT_BUTTON___(button) {}

            };

            getEventMethods getEventMethods__{STRUCT_BUTTON___};

            getEventMethods getEvent(){
                return getEventMethods__;
            }
            
            setActionStruct(Button* button) : STRUCT_BUTTON___(button) {}
            
        };

        setActionStruct action(){
            return s_actionStruct;
        }

        private:
        lv_obj_t *_parent = nullptr;
        lv_obj_t *_copy = nullptr;
        lv_obj_t *_button = nullptr;
        setActionStruct s_actionStruct{this};
        std::function<void()> buttonCb = nullptr;
        lv_event_cb_t buttonCbWLVGLFormatted = NULL;
    };
}