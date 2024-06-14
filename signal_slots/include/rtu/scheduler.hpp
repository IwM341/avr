#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <stdio.h>

namespace rtu{
    /*
    Define:
    template <FuncSignature,typename signal_manager_t>
    signal<>
    if signal_manager_t::unique_signal == true; => unique signal
    if signal_manager_t::specify_[fptr, mfptr, lmbd] == true; => signal type is specified and is handles more effisiently
    
    */
    template <size_t task_queue_size,bool task_is_aligned, 
    size_t delegate_size,delegate_align_t _delegate_align,
    typename sheduler_guard_t>
    struct scheduler{
        inline static scheduler & instance(){
            static scheduler __ret;
            return ret;
        }

        inline static void exec(){
            while(!instance().__terminate_ready){
                if(instance().__tasks.is_full()){
                    instance().__tasks.pop();
                } else {
                    instance().__power_manager.sleep();
                }
            }
        }
        inline static void terminate(){
            instance().__terminate_ready = true;
        }
        
        template <typename FuncType>
        inline static void add_task(FuncType && f){
             instance().__tasks.put(static_cast<FuncType && >(f));
        }

         
        template <typename Signature_t,typename signal_policy_t>
        struct signal : public __signal__impl<mem_array_getter_t,signal_policy_t,Signature_t>{
            
            template <typename FuncType>
            void connect(FuncType && f,signal_policy_t );
            
            template <typename T>
            void connect(T * Object,void (T::*Slot)(Args...),signal_policy_t );
        
        };


        private:
        
        struct mem_array_getter_t{
            inline static mem_array_t & get(){
                return instance().__alloc_buffer();
            } 
        };

        struct mem_allocator{
            struct ptr_type{
                mem_array_t::index_t _index;
                void * ptr(){return &mem_array_getter_t::get().get_node(_index);}
                ptr_type(mem_array_t::index_t _index):_index(_index){}
                
            };
            ptr_type allocate(){
                return 
            }
        };

        struct task_queue_getter_t{
            inline static task_queue_t & get(){
                return __tasks;
            }
        };

        scheduler():__terminate_ready(false){}

        task_queue_t __tasks;
        mem_array_t __alloc_buffer;
        power_manager_t __power_manager;
        bool __terminate_ready;
    };
};

#endif//SCHEDULER_HPP