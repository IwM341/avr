#pragma once
#include <stdlib.h>

namespace asyncruino{
    struct task
    {
        struct promise_type
        {
            void * operator new(size_t size){
                return malloc(size);
            }
            void operator delete(void * ptr){
                free(ptr);
            }

            task get_return_object() { return {}; }
            std::suspend_never initial_suspend() { return {}; }
            std::suspend_never final_suspend() noexcept { return {}; }
            void return_void() {}
            void unhandled_exception() {}
        };
    };

};