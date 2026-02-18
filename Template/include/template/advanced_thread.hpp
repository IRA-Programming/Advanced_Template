#include <vex.h>
#include <functional>
#include <atomic>

namespace adt {
    class ThreadGuard;

    class Thread : public vex::thread {
        public:
        Thread() : thread() {};

        /**
         * @brief Creates a thread object.
         * @param callback A reference to a function.
         * @param arg A void pointer that is passed to the callback.
         */
        Thread( int  (* callback)(void *), void *arg ) : _thread(new thread(callback, arg)) {};

        /**
         * @brief Creates a thread object.
         * @param callback A reference to a function.
         * @param arg A void pointer that is passed to the callback.
         */
        Thread( void (* callback)(void *), void *arg ) : _thread(new thread((int (*)(void *)) callback, arg)) {}

        /**
         * @brief Construct a new Thread object
         * 
         * @param func Function to input. This allows for lambda functions and more advanced capabilities.
         */
        Thread(std::function<void()> func) {
            _thread = new thread(lambda_trampoline, new std::function<void()>(func));
        }

        /**
         * @brief Destroy the Thread object
         * 
         */
        ~Thread(){
            delete _thread;
        }
        

        private:
        vex::thread* _thread;

        static int lambda_trampoline(void* arg) {
            auto* fn = static_cast<std::function<void()>*>(arg);
            (*fn)();      // invoke lambda / function
            delete fn;    // clean up if one-shot
            return 0;
        }

        friend class ThreadGuard;
    };

    class AdvancedMutex{
        public:
            AdvancedMutex() : _mutex(new vex::mutex){
                madeMutex = true;
                isLocked.store(false);
            }

            AdvancedMutex(vex::mutex& mutex_){
                _mutex = &mutex_;
                isLocked.store(false);
            }

            ~AdvancedMutex(){
                if(madeMutex){
                    delete _mutex;
                }
            }
            
        private:

            bool madeMutex = false;
            vex::mutex* _mutex;
            std::atomic<bool> isLocked;
        
        public:

            class ThreadGuard{
                public:
                    explicit ThreadGuard(std::atomic<bool>& running, vex::mutex* mtx = nullptr): _running(running), _mtx(mtx) {
                        _running.store(true, std::memory_order_release);
                        if (_mtx) _mtx->lock();
                    }
 
                    ~ThreadGuard(){
                        if (_mtx) _mtx->unlock();
                        _running.store(false, std::memory_order_release);
                    }

                    /**
                     * @brief Locks the mutex and blocks if the mutex is not available. 
                     */
                    void  wait_until_free(){
                        while(!_mtx->try_lock()){
                            vex::task::sleep(5);
                        }
                    };

                    /**
                     * @brief Try to lock the mutex and returns if the mutex is not available.
                     * @return Returns true if successful and false if the mutex is owned by another thread.
                     */
                    bool  check_if_free(){
                        if(_mtx) return _mtx->try_lock();
                        return false;
                    };

                private:
                    vex::mutex* _mtx;
                    std::atomic<bool>& _running;
            };

            ThreadGuard assign_scope_lock(){
                return ThreadGuard(isLocked, _mutex);
            }

            void lock(){
                _mutex->lock();
            }

            bool try_lock(){
                return _mutex->try_lock();
            }

            void unlock(){
                _mutex->unlock();
            }
    };
};