#ifndef DELEGATE_HPP
#define DELEGATE_HPP
#include <functional>
namespace rtu{
      

    struct Task{
        virtual void call() = 0;
    };
    

    template <typename Lambda_t>
    struct LambdaTask : public Task{
        Lambda_t __M_LMBD; 

        inline LambdaTask(Lambda_t lambda):__M_LMBD(lambda){}
        
        void call (){
            __M_LMBD();
        }
    };

    template <typename T>
    struct ClassTask : public Task{
        typedef void (T::*T_Member_Func_t)(void);
        T * __M_OBJ;
        T_Member_Func_t __M_FN; 

        inline ClassTask(T * Object,T_Member_Func_t MemberFunc):
        __M_OBJ(Object),__M_FN(MemberFunc){}
        
        void call (){
            (__M_OBJ->*__M_FN)();
        }
    };

    namespace __deltail{
        template <typename T>
        struct fwd_type{
            typedef T type;
        };

        template <typename T>
        struct fwd_type<T &>{
            typedef std::reference_wrapper<T> type;
        };
        template <typename T>
        struct fwd_type<T && >{
            typedef T type;
        };
        
        template <size_t i,typename...Args>
        struct get_arg_type{
            typedef typename get_arg_type<i-1,Args...>::type type;
        };
        template <typename Arg,typename...Args>
        struct get_arg_type<0,Arg,Args...>{
            typedef Arg type;
        };
        template <>
        struct get_arg_type<0>{
            struct __non_type__{};
            typedef __non_type__ type;
        };
        
        template <size_t index,typename...Args>
        struct get_arg;
        
        template <size_t index,typename Arg,typename...Args>
        struct get_arg<index,Arg,Args...> {
            inline constexpr static decltype(auto) get(Arg arg,Args...args){
                return get_arg<index-1,Args...>(args...);
            }
        };

        template <typename Arg,typename...Args>
        struct get_arg<0,Arg,Args...> {
            inline constexpr static decltype(auto) get(Arg arg,Args...args){
                return static_cast<typename fwd_type<Arg>::type>(arg);
            }
        };

    };
    template <typename...Args>
    struct Function{
        virtual void call(Args...) = 0;
    };


    template <typename Lambda_t,typename...Args>
    struct LambdaFunction: public Function<Args...>{

    };

    template <typename T,typename...Args>
    struct ClassFunction: public Function<Args...>{

    };

    template <typename Lambda_t>
    struct LambdaFunction<Lambda_t> : public LambdaTask<Lambda_t>{
        typedef LambdaTask<Lambda_t> Base;
        using Base::Base;
    };

    
    template <typename T>
    struct ClassFunction<T> : public ClassTask<T>{
        typedef ClassTask<T> Base;
        using Base::Base;
    };


    /// double ref => need destructor of FuncType
    template <typename FuncType,typename...Args>
    struct MakeTask{
        static auto create_task(FuncType F,Args...args){
            //static_assert(std::is_trivially_destructible<FuncType>::value,"Function Delegate should be trivially destructible");
            #if (__cplusplus  >= 202002L)
            return [F= std::move(F),...args = static_cast<typename __deltail::fwd_type<Args>::type>(args)](){F(static_cast<Args>(args)...);}; 
            #else
            if constexpr (sizeof...(Args) == 0){
                return [F = std::move(F)](){F();};
            } else if constexpr (sizeof...(Args) == 1) {
                 return [F= std::move(F), arg0 = __deltail::get_arg<0,Args...>(args...)](){
                    F(static_cast<typename get_arg_type<0,Args...>::type>(arg0));
                 };
            } else if constexpr (sizeof...(Args) == 2) {
                 return [F= std::move(F), 
                            arg0 = __deltail::get_arg<0,Args...>(args...),
                            arg1 = __deltail::get_arg<1,Args...>(args...)
                        ](){
                            F(
                                static_cast<typename get_arg_type<0,Args...>::type>(arg0),
                                static_cast<typename get_arg_type<1,Args...>::type>(arg1)
                            );
                        };
            } else if constexpr (sizeof...(Args) == 3) {
                 return [F= std::move(F), 
                            arg0 = __deltail::get_arg<0,Args...>(args...),
                            arg1 = __deltail::get_arg<1,Args...>(args...),
                            arg2 = __deltail::get_arg<2,Args...>(args...)
                        ](){
                            F(
                                static_cast<typename get_arg_type<0,Args...>::type>(arg0),
                                static_cast<typename get_arg_type<1,Args...>::type>(arg1),
                                static_cast<typename get_arg_type<2,Args...>::type>(arg2)
                            );
                        };
            } else if constexpr (sizeof...(Args) == 4) {
                 return [F= std::move(F), 
                            arg0 = __deltail::get_arg<0,Args...>(args...),
                            arg1 = __deltail::get_arg<1,Args...>(args...),
                            arg2 = __deltail::get_arg<2,Args...>(args...),
                            arg3 = __deltail::get_arg<3,Args...>(args...)
                        ](){
                            F(
                                static_cast<typename get_arg_type<0,Args...>::type>(arg0),
                                static_cast<typename get_arg_type<1,Args...>::type>(arg1),
                                static_cast<typename get_arg_type<2,Args...>::type>(arg2),
                                static_cast<typename get_arg_type<3,Args...>::type>(arg3)
                            );
                        };
            } else {
                static_assert(false,"not supported more than 4 arguments in slot function");
            }
            #endif
        }
        typedef decltype(create_task(std::declval<FuncType &&>(),std::declval<Args>()...)) task_t;
        static constexpr size_t size = sizeof(task_t);
        static void process_task(void * ptr){
            (*reinterpret_cast<task_t*>(ptr))();
            ~(*reinterpret_cast<task_t*>(ptr));
        }
    };


/*
    #define __IMPL__CONSTRUCT_TASK__(__capture__param__,__call__action__)\
            typedef __deltail::get_arg_type<0,Args...> Arg0;\
            typedef __deltail::get_arg_type<1,Args...> Arg1;\
            typedef __deltail::get_arg_type<2,Args...> Arg2;\
            typedef __deltail::get_arg_type<3,Args...> Arg3;\
            void construct_task(task_queue_t & tq) const{\
                tq.put([__capture__param__](){__call__action__();} );\
            }\
            void construct_task(task_queue_t & tq,Arg0 arg0) const{\
                tq.put([__capture__param__,\
                arg0 = static_cast<typename __deltail::fwd_type<Arg0>::type>(arg0)]()\
                {\
                    __call__action__(static_cast<Arg0>(arg0));\
                } );\
            }\
            void construct_task(task_queue_t & tq,Arg0 arg0,Arg1 arg1) const{\
                tq.put([__capture__param__,arg0 = static_cast<typename __deltail::fwd_type<Arg0>::type>(arg0),\
                            arg1 = static_cast<typename __deltail::fwd_type<Arg1>::type>(arg1)](){\
                                    __call__action__(static_cast<Arg0>(arg0),static_cast<Arg1>(arg1));\
                                } );\
            }\
            void construct_task(task_queue_t & tq,Arg0 arg0,Arg1 arg1,Arg2 arg2) const{\
                tq.put([__capture__param__,arg0 = static_cast<typename __deltail::fwd_type<Arg0>::type>(arg0),\
                               arg1 = static_cast<typename __deltail::fwd_type<Arg1>::type>(arg1),\
                               arg2 = static_cast<typename __deltail::fwd_type<Arg2>::type>(arg2)](){\
                                    __call__action__(static_cast<Arg0>(arg0),static_cast<Arg1>(arg1),static_cast<Arg2>(arg2));\
                                } );\
            }\
            void construct_task(task_queue_t & tq,Arg0 arg0,Arg1 arg1,Arg2 arg2,Arg3 arg3) const{\
                tq.put([__capture__param__,arg0 = static_cast<typename __deltail::fwd_type<Arg0>::type>(arg0),\
                               arg1 = static_cast<typename __deltail::fwd_type<Arg1>::type>(arg1),\
                               arg2 = static_cast<typename __deltail::fwd_type<Arg2>::type>(arg2),\
                               arg3 = static_cast<typename __deltail::fwd_type<Arg3>::type>(arg3)](){\
                                    __call__action__(static_cast<Arg0>(arg0),static_cast<Arg1>(arg1),static_cast<Arg2>(arg2),static_cast<Arg3>(arg3));\
                                } );\
            }
    #define __WRAP__VARIADIC_MACRO__(...) __VA_ARGS__

        
    template <typename task_queue_t,typename...Args>
    struct FuncDelegate : public Delegate<task_queue_t,Args...>{
        typedef void (*FuncPointer_t) (Args...);
        FuncPointer_t __M_FP;
        inline FuncDelegate(FuncPointer_t fp):__M_FP(fp){}

        #if (__cplusplus  >= 202002L)
        void construct_task(task_queue_t & tq,Args...args) const{
            tq.put([__M_FP,...args = static_cast<typename __deltail::fwd_type<Args>::type>(args)](){__M_FP(static_cast<Args>(args)...);} );
        }
        #else
        __IMPL__CONSTRUCT_TASK__(__M_FP,__M_FP)
        #endif
    };

    template <typename task_queue_t,typename T,typename...Args>
    struct ClassDelegate : public Delegate<task_queue_t,Args...> {
        typedef void (T::*T_Member_Func_t)(void);
        T * __M_OBJ;
        T_Member_Func_t __M_FN; 

        inline ClassDelegate(T * Object,T_Member_Func_t MemberFunc):
        __M_OBJ(Object),__M_FN(MemberFunc){}

        #if (__cplusplus  >= 202002L)
        void construct_task(task_queue_t & tq,Args...args) const{
            tq.put([__M_OBJ,__M_FN,...args = static_cast<typename __deltail::fwd_type<Args>::type>(args)](){(__M_OBJ->*__M_FN)(static_cast<Args>(args)...);} );
        }
        #else
        __IMPL__CONSTRUCT_TASK__(__WRAP__VARIADIC_MACRO__(__M_OBJ,__M_FN),(__M_OBJ->*__M_FN))
        #endif
    };
    
    template <typename task_queue_t,typename Lambda_t,typename...Args>
    struct LambdaDelegate : public Delegate<task_queue_t,Args...> {
        Lambda_t Lambda;

        inline ClassDelegate(Lambda_t Lambda):Lambda(Lambda){}

        #if (__cplusplus  >= 202002L)
        void construct_task(task_queue_t & tq,Args...args) const{
            tq.put([Lambda,...args = static_cast<typename __deltail::fwd_type<Args>::type>(args)](){Lambda(static_cast<Args>(args)...);} );
        }
        #else
        __IMPL__CONSTRUCT_TASK__(Lambda,Lambda)
        #endif
    };

    struct call_always{
        typedef void call_condition_t;

        inline bool call_ready(){return true;}
        inline bool destroy_ready(){return false;}
    };
    struct call_and_destroy{
        typedef void call_condition_t;
        typedef void destroy_condition_t;

        inline bool call_ready(){return true;}
        inline bool destroy_ready(){return true;}
    };

    template <typename Delegate_Policy_t>
    struct DelegateTraits{
        static void create_delegate_in_list(...);
        /*
            if Meta_Info_t::put_sorted;
               put in list sorted and execute untill first false statement
            else
              put at the end of list in connection
            

        
        static index_t * process_in_list(index_t  index,Delegate_Policy_t::call_condition_t _t,Args...args){
            Delegat = Load_Delegat(index);
            Policy = Load_Policy(index);

            if(Policy.call_ready(_t)){
                Delegat.call(args);
            }
            if(Policy.destroy_ready(_t)){
                index = next;
                return index;
            } else {
                return next;
            }
        }

        /*
            struct ProperDeletate: public DelegateType, Meta_Info_t{};

        

    };
    */
};

#endif//DELEGATE_HPP