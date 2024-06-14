#ifndef SIGNAL_IMPL_HPP
#define SIGNAL_IMPL_HPP

#include <type_traits>
#include "int_traits.hpp"
#include "default_guard.hpp"
namespace rtu{

    /*
        signal_manager_t{
            typedef ... guard_t; // guard type, default --- default_guard_t in...
            typdef ... call_type; // type of argument in functions, default --- void
            constexpr static bool fptr = true; // mean, that it takes only slot, which are the function pointers
            constexpr static bool mfptr = true; // mean, that it takes only slot, which are the object pointer and member function pointer
            constexpr static size_t lmbd = [lambda_size] // mean, that slot is a lambda, which size could,t ne more than lambda_size bytes

            [constexpr static] bool call_ready(call_type); // if  true, corresponing slot is executes
            [constexpr static] bool destroy_ready(call_type); // if true, disconnects coresponding slot 
            [constexpr static] bool direct_call(call_type); // if true calls slot directly (ommiting task queue)
             
        };
    */

    namespace detail{
        // if these functions (call_ready,destroy_ready,direct_call) are static constexper and without params,
        // or if these functions are not exists
        // we define bool constexpr_call_ready;
        struct __constructed_from_any__{
            template <typename T>
            constexpr __constructed_from_any__(T x){}
            constexpr __constructed_from_any__(){}
        };

        template <typename __signal_manager_t,typename = typename __signal_manager_t::call_type>
        typename __signal_manager_t::call_type call_type_check(__signal_manager_t);

        template <typename __signal_manager_t>
        void call_type_check(__constructed_from_any__);


        template <typename T>
        struct __is_void{
            constexpr static bool value = false;
        };

        template <>
        struct __is_void<void>{
            constexpr static bool value = true;
        };

        template <typename __signal_manager_t> 
        struct signal_manager_call_t{
            typedef decltype(call_type_check(__signal_manager_t{})) call_type;
            constexpr static bool is_void =  __is_void<call_type>::value;
        };

        struct __default_signal_manager_t{
            typedef void call_type;

            constexpr static bool default_call_ready = true;
            constexpr static bool default_destroy_ready = false;
            constexpr static bool default_direct_call = false;
        };

        #define __SIGNAL_MANAGER_SFINAE__(funcname) \
            template <typename __signal_manager_t,bool = __signal_manager_t::funcname() >\
            constexpr bool constexpr_check_##funcname(__signal_manager_t){\
                return true;\
            }\
            constexpr bool constexpr_check_##funcname(__constructed_from_any__){\
                return false;\
            }\
            template <bool is_void_ct,typename __signal_manager_t>\
            struct __call_##funcname{ \
                typedef decltype(std::declval<__signal_manager_t>().funcname(std::declval<__signal_manager_t::call_type>())) type;\
            };\
            template <typename __signal_manager_t>\
            struct __call_##funcname<true,__signal_manager_t>{ \
                typedef decltype(std::declval<__signal_manager_t>().funcname()) type;\
            };\
            template <typename __signal_manager_t,typename = typename __call_##funcname<signal_manager_call_t<__signal_manager_t>::is_void,__signal_manager_t>::type>\
            constexpr bool has_check_##funcname(__signal_manager_t){\
                return true;\
            }\
            constexpr bool has_check_##funcname(__constructed_from_any__){\
                return false;\
            }\
            template <typename __signal_manager_t>\
            struct __info_##funcname{\
                constexpr statis bool is_constexpr_function = constexpr_check_##funcname(std::declval<__signal_manager_t>());\
                constexpr static bool has_function = has_check_##funcname(std::declval<__signal_manager_t>());\
            };\
            template <bool __has_function,typename __signal_manager_t>\
            struct constexpr_value_impl_##funcname{\
                constexpr static bool value = __signal_manager_t::funcname();\
            };\
            template <typename __signal_manager_t>\
            struct constexpr_value_impl_##funcname<false,__signal_manager_t>{\
                constexpr static bool value = __default_signal_manager_t::default_##funcname;\
            };\
            template <typename __signal_manager_t>\
            struct constexpr_of_##funcname : \
            constexpr_value_impl_##funcname<__info_##funcname<__signal_manager_t>::has_function,__signal_manager_t>{\
                constexpr static bool value = __default_signal_manager_t::default_##funcname;\
            };\
            template <typename __signal_manager_t>\
            struct __meta_##funcname : public __info_##funcname<__signal_manager_t>{\
                constexpr static bool constexp_value = constexpr_of_##funcname<__signal_manager_t>::value;\
            };
        
        __SIGNAL_MANAGER_SFINAE__(call_ready)
        __SIGNAL_MANAGER_SFINAE__(destroy_ready)
        __SIGNAL_MANAGER_SFINAE__(direct_call)

        #define __CHECK_PROPERTY__(type,property) \
            template <typename __signal_manager_t>\
            constexpr auto __get_value##property(__signal_manager_t) -> decltype(__signal_manager_t::property){\
                return __signal_manager_t::property;\
            }\
            constexpr auto __get_value##property(__constructed_from_any__){\
                return static_cast<type>(0);\
            }

        __CHECK_PROPERTY__(bool,fptr)
        __CHECK_PROPERTY__(bool,mfptr)
        __CHECK_PROPERTY__(size_t,lmbd)



        template <typename __default_guard_t,typename __signal_manager_t>
        constexpr auto __get_guard_t(__signal_manager_t) -> typename __signal_manager_t::guard_t;

        
        template <typename __default_guard_t,typename __signal_manager_t>
        constexpr __default_guard_t __get_guard_t(__constructed_from_any__);

        template <typename T>
        struct empty_struct_check : T{
            max_align_t x;
        };

        template <typename T>
        struct is_empty_struct{
            constexpr static bool value = (sizeof(empty_struct_check<T>) == sizeof(max_align_t));
        };

        /*META CLASS, DEFINIG ALL*/
        template <typename __default_guard_t,typename __signal_manager_t>
        struct meta_signal_manager_t : signal_manager_call_t<__signal_manager_t>{
            typedef __signal_manager_t signal_manager_t;
            typedef decltype(__get_guard_t<__default_guard_t>(std::declval<__signal_manager_t>())) guard_t;
            constexpr static bool fptr = __get_value_fptr(std::declval<__signal_manager_t>());
            constexpr static bool mfptr = __get_value_mfptr(std::declval<__signal_manager_t>());
            constexpr static bool lmbd = __get_value_lmbd(std::declval<__signal_manager_t>());
            constexpr static bool is_empty_manager = is_empty_struct<__signal_manager_t>::value;
            /*call_type and is_void inhereted*/

            // types have static values: has_function, is_constexpr_function, constexp_value
            typedef __meta_call_ready<__signal_manager_t> meta_call_ready_t;
            typedef __meta_destroy_ready<__signal_manager_t> meta_destroy_ready_t;
            typedef __meta_direct_call<__signal_manager_t> meta_direct_call_t;
        };

        template <typename size_type>
        struct mem_array_index_ret{
            size_type next_index;
            bool destroy;
            //typedef mem_array_index_ret (*SignalProcessorFunc_t)(size_type,signal_manager_t::call_type,Args...)
        };

        template <typename task_queue_getter_t,typename meta_signal_manager_t,typename...Args>
        struct __signal_impl_only_slot_fptr_helper{
            typedef void (*fptr_t)(Args...);

            struct delegate_t : public meta_signal_manager_t::signal_manager_t{
                typedef typename meta_signal_manager_t::signal_manager_t signal_manager_t;
                using signal_manager_t::signal_manager_t;
                fptr_t fptr;
                inline meta_signal_manager_t(fptr_t fptr,signal_manager_t sig_man):
                fptr(fptr),signal_manager_t(sig_man){}
            };
            struct alignas(alignof(delegate_t)) data_delegate_t{
                static constexpr size_t size = sizeof(delegate_t);
                char data[size];
                operator char *(){return data;}
            };
            struct delegate_data{
                data_delegate_t data;
                meta_signal_manager_t::guard_t m_guard;
                bool occupied;

                inline delegate_t & get_delegate(){
                    return *(delegate_t *)(data);
                }

                struct Connection{
                    delegate_data *m_d;
                    inline void disconnect(){
                        m_d->disconnect();
                    }
                };
                void disconnect(Connection){
                    m_guard.lock();
                    if(occupied){
                        ~this->get_delegate();
                        occupied = false;
                    }
                    m_guard.unlock();
                }
                template <bool B>
                friend class connect_functionality;

                private:
                bool connect_impl(fptr_t fptr,meta_signal_manager_t::signal_manager_t __sig_mngr){
                    using delegate_data::delegate_data;
                    
                    lock_guard(this->guard) my_lock;
                    if(occupied)
                        return false;
                    else{
                        occupied = true;
                        new (&this->get_delegate()) delegate_t(fptr,__sig_mngr);
                        return true;
                    }
                }
            };

            template <bool is_trivially_constructed_manager> // default --- false
            struct connect_functionality : public delegate_data{
                inline bool connect(fptr_t fptr,meta_signal_manager_t::signal_manager_t __sig_mngr){
                    this->connect_impl(fptr,std::move(__sig_mngr));
                }
            };
            template <> // default --- false
            struct connect_functionality<true> : public delegate_data{
                inline bool connect(fptr_t fptr,meta_signal_manager_t::signal_manager_t __sig_mngr = {}){
                    this->connect_impl(fptr,std::move(__sig_mngr));
                }
            };

            typedef connect_functionality <
                std::is_trivially_constructible <
                    typename meta_signal_manager_t::signal_manager_t
                >::value > connectable_signal;

            //default is_void_call_type false
            template <bool is_void_call_type,typename connectable_delegate_t>
            struct callable_delegate : public connectable_delegate_t{
                using connectable_delegate_t::connectable_delegate_t;
                void operator()(signal_manager_t::call_type call_info,Args...args){
                    this->guard->lock();
                    if(this->occupied){

                        if constexpr(meta_signal_manager_t::meta_direct_call_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_direct_call_t::constexp_value) {
                                goto DirectCall;
                            } else {
                                goto DelayedCall;
                            }
                        } else {
                            if(get_delegate().meta_direct_call(call_info)){
                                goto DirectCall;
                            } else {
                                goto DelayedCall;
                            }
                        }
                        
                        DirectCall:
                        if constexpr(meta_signal_manager_t::meta_call_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_call_ready_t::constexp_value) {
                                get_delegate().fptr(args...);
                            } 
                        } else {
                            if(get_delegate().call_ready(call_info)){
                                get_delegate().fptr(args...);
                            }
                        } 
                        goto Continue;
                        DelayedCall:
                        if constexpr(meta_signal_manager_t::meta_call_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_call_ready_t::constexp_value) {
                                task_queue_getter_t::get::put_bind<Args...>(get_delegate().fptr,args...);
                            } 
                        } else {
                            if(get_delegate().call_ready(call_info)){
                                task_queue_getter_t::get::put_bind<Args...>(get_delegate().fptr,args...);
                            }
                        }
                        goto Continue;
                        Continue:
                        if constexpr(meta_signal_manager_t::meta_destroy_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_destroy_ready_t::constexp_value) {
                                task_queue_getter_t::get::put_bind<Args...>(get_delegate().fptr,args...);
                            } 
                        } else {
                            if(get_delegate().meta_destroy_ready(call_info)){
                                task_queue_getter_t::get::put_bind<Args...>(get_delegate().fptr,args...);
                            }
                        }
                    }

                }
            };

            typedef callable_delegate<meta_signal_manager_t::is_void, connectable_signal> signal_type;

        };
        template <typename...Args>
        struct __EmptyHelperClass__{
            void __HelperFunction__(Args...){};
        };
        template <typename task_queue_getter_t,typename meta_signal_manager_t,typename...Args>
        struct __signal_impl_only_slot_mfptr_helper{
            
            typedef void (*fptr_t)(Args...);

            struct delegate_t : public meta_signal_manager_t::signal_manager_t{
                typedef typename meta_signal_manager_t::signal_manager_t signal_manager_t;
                using signal_manager_t::signal_manager_t;
                __EmptyHelperClass__ * ObjPtr;
                void (__EmptyHelperClass__::*MFunctor)(Args);

                template <typename T>
                inline meta_signal_manager_t(T* ObjPtr,void (T::*MFunctor)(Args...),signal_manager_t sig_man):
                ObjPtr(ObjPtr),MFunctor(MFunctor),signal_manager_t(sig_man){}
            };
            struct alignas(alignof(delegate_t)) data_delegate_t{
                static constexpr size_t size = sizeof(delegate_t);
                char data[size];
                operator char *(){return data;}
            };
            struct delegate_data{
                data_delegate_t data;
                meta_signal_manager_t::guard_t m_guard;
                bool occupied;

                inline delegate_t & get_delegate(){
                    return *(delegate_t *)(data);
                }

                struct Connection{
                    delegate_data *m_d;
                    inline void disconnect(){
                        m_d->disconnect();
                    }
                };
                void disconnect(Connection){
                    m_guard.lock();
                    if(occupied){
                        ~this->get_delegate();
                        occupied = false;
                    }
                    m_guard.unlock();
                }
                template <bool B>
                friend class connect_functionality;

                private:
                template <typename T>
                bool connect_impl(T* ObjPtr,void (T::*MFunctor)(Args...),meta_signal_manager_t::signal_manager_t __sig_mngr){
                    using delegate_data::delegate_data;
                    
                    lock_guard(this->guard) my_lock;
                    if(occupied)
                        return false;
                    else{
                        occupied = true;
                        new (&this->get_delegate()) delegate_t(fptr,__sig_mngr);
                        return true;
                    }
                }
            };

            template <bool is_trivially_constructed_manager> // default --- false
            struct connect_functionality : public delegate_data{
                template <typename T>
                inline bool connect(T* ObjPtr,void (T::*MFunctor)(Args...),meta_signal_manager_t::signal_manager_t __sig_mngr){
                    this->connect_impl(ObjPtr,MFunctor,std::move(__sig_mngr));
                }
            };
            template <> // default --- false
            struct connect_functionality<true> : public delegate_data{
                template <typename T>
                inline bool connect(T* ObjPtr,void (T::*MFunctor)(Args...),meta_signal_manager_t::signal_manager_t __sig_mngr = {}){
                    this->connect_impl(ObjPtr,MFunctor,std::move(__sig_mngr));
                }
            };

            typedef connect_functionality <
                std::is_trivially_constructible <
                    typename meta_signal_manager_t::signal_manager_t
                >::value > connectable_signal;

            //default is_void_call_type false
            template <bool is_void_call_type,typename connectable_delegate_t>
            struct callable_delegate : public connectable_delegate_t{
                using connectable_delegate_t::connectable_delegate_t;
                void operator()(signal_manager_t::call_type call_info,Args...args){
                    this->guard->lock();
                    if(this->occupied){

                        if constexpr(meta_signal_manager_t::meta_direct_call_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_direct_call_t::constexp_value) {
                                goto DirectCall;
                            } else {
                                goto DelayedCall;
                            }
                        } else {
                            if(get_delegate().meta_direct_call(call_info)){
                                goto DirectCall;
                            } else {
                                goto DelayedCall;
                            }
                        }
                        
                        DirectCall:
                        if constexpr(meta_signal_manager_t::meta_call_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_call_ready_t::constexp_value) {
                                (Delegat.ObjPtr->*Delegat.MFunctor)(args...);
                            } 
                        } else {
                            if(get_delegate().call_ready(call_info)){
                                (Delegat.ObjPtr->*Delegat.MFunctor)(args...);
                            }
                        } 
                        goto Continue;
                        DelayedCall:
                        if constexpr(meta_signal_manager_t::meta_call_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_call_ready_t::constexp_value) {
                                task_queue_getter_t::get::put_bind<Args...>([Delegat = get_delegate()](Args...args1) { 
                                    (Delegat.ObjPtr->*Delegat.MFunctor)(args1...);
                                    },args...);
                            } 
                        } else {
                            if(get_delegate().call_ready(call_info)){
                                task_queue_getter_t::get::put_bind<Args...>([Delegat = get_delegate()](Args...args1) { 
                                    (Delegat.ObjPtr->*Delegat.MFunctor)(args1...);
                                    },args...);
                            }
                        }
                        goto Continue;
                        Continue:
                        if constexpr(meta_signal_manager_t::meta_destroy_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_destroy_ready_t::constexp_value) {
                                task_queue_getter_t::get::put_bind<Args...>(get_delegate().fptr,args...);
                            } 
                        } else {
                            if(get_delegate().meta_destroy_ready(call_info)){
                                task_queue_getter_t::get::put_bind<Args...>(get_delegate().fptr,args...);
                            }
                        }
                    }
                    this->guard->unlock();
                }
            };

            typedef callable_delegate<meta_signal_manager_t::is_void, connectable_signal> signal_type;

        };

        

        template <typename mem_array_gatter_t,typename default_guard_t,typename signal_manager_t,typename signal_signature_t>
        struct __signal_impl__;
    
        
        template <typename mem_array_getter_t,typename default_guard_t,typename signal_manager_t,typename...Args>
        struct __signal_impl__<mem_array_getter_t,default_guard_t,signal_manager_t,void(Args...)>{};
    };
};

#endif//SIGNAL_IMPL_HPP