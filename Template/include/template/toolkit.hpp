#include "vex.h"
#include "template_api.hpp"

/**
 * @file toolkit.hpp
 * @brief Tookit is used to assist in tasks by creating simpler functions to complete them.
 */


//Tookit Marcos
#define TOOLKIT_SCOPE_LOCK(myMutex) \
    auto _toolkit_guard_##__LINE__ = myMutex.assign_scope_lock()

//Toolkit Class
namespace adt {
    /**
     * @brief TOOKKIT class that contains various utility functions and classes.
     */
    class TOOLKIT {
        public:
            TOOLKIT() {}

            static adt::chassis createChassis(
                
            ) {
                return adt::chassis();
            }

        private:
    };
};