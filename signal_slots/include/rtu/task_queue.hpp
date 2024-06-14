#ifndef TASK_QUEUE_HPP
#define TASK_QUEUE_HPP
#include "int_traits.hpp"
#include "delegate.hpp"
#include <cstring>
#include "default_guard.hpp"
#ifndef CHECK_QUEUE_OVF
#define NOT_CHECK_QUEUE_OVF
#endif
namespace rtu{
    /*task queue concept:
        1) inline void pot(FuncType && F);
        2) bool empty() const;
        3) void pop();
    */
    /*
        implementation details:
        [ttttttt*****ttttttt---]
          |    |     |       |
          |   end   start    |
          |                  |
      [task bytes]  [not used bytes for linearity]
    */
    template <bool __check_ovf>
    struct overflow_action_t{
        typedef void (*OverflowFunction_t) (void);
        OverflowFunction_t overflow_function;
        void set_ovf_func(OverflowFunction_t __overflow_function){
            overflow_function = __overflow_function;
        }
        inline void operator()(){overflow_function();}
    };
    template <>
    struct overflow_action_t<false>{};

    template <size_t _size,typename guard_t = no_guard_t,bool check_overflow = false,boool align_compress = false>
    struct task_queue{

        static inline void * operator new (size_t N,void * p) {return p;}

        constexpr size_t max_align = align_compress ? 1 : alignof(max_align_t);   
        
        typedef typename min_type_for_size<_size>::type pos_t;
        
        constexpr static bool merge_size_data = (sizer_algmnt+delegate_algmnt <= max_align);

        struct alignas(max_align) al_pos_t
        {
            pos_t x;
            inline al_pos_t (pos_t x): x(x){}
            inline operator pos_t & (){return x;}
            inline operator pos_t const& ()const{return x;}  
        }

        /// @brief type of function in task_qeue
        typedef void (*DelegateFunction_t) (void *);


        struct alignas(max_align) al_size_and_functor_t
        {
            pos_t size;
            DelegateFunction_t Functor;
        };

        static constexpr pos_t aligned_size(pos_t __size){
            return  (__size+(max_align-1))& ~((max_align-1));
        } 
        struct alignas(alignof(max_align_t)) data_array{
            static constexpr pos_t size = aligned_size(_size);
            char data[size];
            inline har * operator ()(pos_t pos){return data + pos;}
            inline const char * operator  ()(pos_t pos) const{return data + pos;}
        };
        constexpr static pos_t pointer_size = sizeof(al_ex_size_t); 
        constexpr static pos_t func_size = sizeof(al_lambda_caller_t); 
        constexpr static pos_t size = data_array::size;
        
        data_array data;
        pos_t start;
        pos_t end;

        guard_t __guard;
        overflow_action_t<check_overflow> ovf_action;
        

        task_queue():start(0),end(0){}
        
        

        template <typename...Args,typename LambdaType>
        inline void put_bind(LambdaType Lambda, Args...args){
            typedef MakeTask<typename std::decay<LambdaType>::type,Args...> Task_t;
            __guard.lock();
            

            if(data_array::size - end < sizeof(al_size_and_functor_t)){
                end = 0;    
            }
            
            if constexpr (check_overflow){
                while ( (end < start && sizeof(al_size_and_functor_t) >= start - end) ||
                        ()){
                    ovf_action();
                    __guard.unlock();
                    pop();
                    __guard.lock();
                }
            }
 
            new ( (void *) data(end)) al_size_and_functor_t({aligned_size(Task_t::size),&Task_t::process_task});
            end +=  sizeof(al_pos_t);

            if(data_array::size - end < aligned_size(sizeof(Task_t))){
                end = 0;
            }

            if constexpr (check_overflow){
                while ( end < start && sizeof(al_size_and_functor_t) >= start - end){
                    ovf_action();
                }
            }

            new (data(end)) Task_t::create_task(std::move(Lambda),args...);
            end +=  aligned_size(Task_t::size);
            __guard.unlock();
        }
        template <typename T>
        inline void put(T * Object,void (T::*Function)(void)){
            typedef ClassTask<T> Task_t;
            __guard.lock();
            

            if(data_array::size - end < sizeof(al_pos_t)){
                end = 0;    
            }
            
            #ifndef NOT_CHECK_QUEUE_OVF
            if( end < start && end + sizeof(al_pos_t) >= start){
                OverflowFunction();
            }
            #endif
 
            new ( (void *) data(end)) al_pos_t(aligned_size(sizeof(Task_t)));
            end +=  sizeof(al_pos_t);

            if(data_array::size - end < aligned_size(sizeof(Task_t))){
                end = 0;
            }

            #ifndef NOT_CHECK_QUEUE_OVF
            if( end < start && end + sizeof(al_pos_t) >= start){
                OverflowFunction();
            }
            #endif

            new (data(end)) Task_t(Object,Function);
            end +=  aligned_size(sizeof(Task_t));
            
            __guard.unlock();
        }
        
        inline void put(Task * m_task,size_t m_size){
            __guard.lock();
            size_t real_size = aligned_size(m_size);
            if(data_array::size - end < sizeof(al_pos_t)){
                end = 0;    
            }
            
            #ifndef NOT_CHECK_QUEUE_OVF
            if( end < start && end + sizeof(al_pos_t) >= start){
                OverflowFunction();
            }
            #endif
 
            new ( (void *) data(end)) al_pos_t(real_size);
            end +=  sizeof(al_pos_t);

            if(data_array::size - end < sizeof(Task_t)){
                end = 0;
            }

            #ifndef NOT_CHECK_QUEUE_OVF
            if( end < start && end + sizeof(al_pos_t) >= start){
                OverflowFunction();
            }
            #endif

           memcpy(data(end), m_task);
            end +=  real_size;
            
            __guard.unlock();
        }

        inline bool is_empty(){
            return (start == end);
        }
        inline void pop(){
            /* task = [sizeof task] [body of type Task] */
            al_pos_t & curr_task_size = *(al_pos_t *)data(start);
            pos_t tmp = start + sizeof(al_pos_t);
            if(curr_task_size > data_array::size - tmp ){
                tmp = 0;
            }
            reinterpret_cast<Task *>( data(tmp ) )->call();
            start = (tmp + curr_task_size)%data_array::size;
        }

    };
};


#endif//TASK_QUEUE_HPP