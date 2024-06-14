#ifndef SIGNAL_IMPL_HPP
#define SIGNAL_IMPL_HPP

#include <type_traits>
#include "int_traits.hpp"
namespace rtu{

    /*
        signal_manager_t{
            typedef ... guard_t; // guard type, default --- default_guard_t in...
            typedef ... call_type; // type of argument in functions, default --- void
            typedef ... slot_type; // type of slot e.g. void (*)(void); default --- any

            constexpr static size_t size = [lambda_size] // mean, max size of capture, default: size_t

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
            typedef decltype(call_type_check(sstd::declval<__signal_manager_t>())) call_type;
            //additional parameter to call, which is used to determine if slot should be called/destroyed
            constexpr static bool is_void =  __is_void<call_type>::value;
            //true if call type is void (empty)
        };

        struct __default_signal_manager_t{
            typedef void call_type;

            constexpr static bool default_call_ready = true;
            constexpr static bool default_destroy_ready = false;
            constexpr static bool default_direct_call = false;
        };

        #define __SIGNAL_MANAGER_SFINAE__(funcname) \
            template <typename __signal_manager_t,bool = __signal_manager_t::funcname() >\
            constexpr auto constexpr_check_##funcname(__signal_manager_t)->std::true_type;\
            constexpr auto constexpr_check_##funcname(__constructed_from_any__)->std::false_type;\
            \
            template <bool is_void_ct,typename __signal_manager_t>\
            struct __call_##funcname{ \
                typedef decltype(std::declval<__signal_manager_t>().funcname(std::declval<__signal_manager_t::call_type>())) type;\
            };\
            template <typename __signal_manager_t>\
            struct __call_##funcname<true,__signal_manager_t>{ \
                typedef decltype(std::declval<__signal_manager_t>().funcname()) type;\
            };\
            template <typename __signal_manager_t,typename = typename __call_##funcname<signal_manager_call_t<__signal_manager_t>::is_void,__signal_manager_t>::type>\
            constexpr auto has_check_##funcname(__signal_manager_t)->std::true_type;\
            constexpr auto has_check_##funcname(__constructed_from_any__)->std::false_type;\
            template <typename __signal_manager_t>\
            struct __info_##funcname{\
                constexpr statis bool is_constexpr_function = decltype(constexpr_check_##funcname(std::declval<__signal_manager_t>()))::value;\
                constexpr static bool has_function = decltype(has_check_##funcname(std::declval<__signal_manager_t>()))::value;\
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

        #define __CHECK_PROPERTY__(type,property,default_value) \
            template <typename __signal_manager_t>\
            constexpr auto __get_value_##property(__signal_manager_t) -> std::integral_constant<type,__signal_manager_t::property>;
            constexpr auto __get_value_##property(__constructed_from_any__) -> std::integral_constant<type,default_value>;

        struct alignas(alignof(max_align_t)) __max_align_size_t{
            size_t x;
        };
        __CHECK_PROPERTY__(size_t,size,sizeof(__max_align_size_t))
        __CHECK_PROPERTY__(bool,fast_call,false)


        template <typename __default_guard_t,typename __signal_manager_t>
        constexpr auto __get_guard_t(__signal_manager_t) -> typename __signal_manager_t::guard_t;

        template <typename __default_guard_t,typename __signal_manager_t>
        constexpr __default_guard_t __get_guard_t(__constructed_from_any__);


        template <typename __signal_manager_t, typename = typename __signal_manager_t::slot_type>
        constexpr auto __specified_slot_t(__signal_manager_t) -> std::true_type;
        constexpr auto __specified_slot_t(__constructed_from_any__) -> std::false_type;

        template <typename __signal_manager_t>
        constexpr auto __get_slot_t(__signal_manager_t) ->  typename __signal_manager_t::slot_type;
        constexpr auto __get_slot_t(__constructed_from_any__) -> void;

        template <typename T>
        struct empty_struct_check : T{
            max_align_t x;
        };

        template <typename T>
        struct is_empty_struct{
            constexpr static bool value = (sizeof(empty_struct_check<T>) == sizeof(max_align_t));
        };

        template <typename T,bool = T::__signal_marker__>
        constexpr auto is_signal_check(T) -> std::true_type;
        constexpr auto is_signal_check(__constructed_from_any__)-> std::false_type;
        template <typename T>
        struct is_signal{
            constexpr static bool value = is_signal_check(std::declval<T>());
        }
        template <typename T>
        struct __signal_crtp_marker{
            T & get(){
                return static_cast<T &>(*this);
            }
        };


    
        template <typename signal_t,typename...Args>
        struct delegate_functions_size_test{
            virtual void invoke(signal_t *,Args...) = 0;
            virtual void make_task(signal_t *,Args...) = 0;
            virtual void destroy(signal_t*) = 0;
        };
        //
        // TODO 
        // Leaf, delegate
        



        /*META CLASS, DEFINIG ALL*/
        template <typename __default_guard_t,typename __signal_manager_t>
        struct meta_signal_manager_t : signal_manager_call_t<__signal_manager_t>{
            typedef __signal_manager_t signal_manager_t;
            typedef decltype(__get_guard_t<__default_guard_t>(std::declval<__signal_manager_t>())) guard_t;

            constexpr static bool size = decltype(__get_value_size(std::declval<__signal_manager_t>()))::value;
            //preliminary size of slot
            constexpr static bool is_empty_manager = is_empty_struct<__signal_manager_t>::value;
            //if the body of class signal_manager_t is empty (only methods)
            constexpr static bool fast_call =  decltype(__get_value_fast_call(std::declval<__signal_manager_t>()))::value;
            //if true, slot type don't have ref counter and coplicated destructor system
            //but works only for trivially_copyable slots 
            constexpr static bool slot_specified = decltype(_specified_slot_t(std::declval<__signal_manager_t>()))::value;
            //specification of slot type, e.g. void (*) (Args...)
            typedef  decltype(__get_slot_t(std::declval<__signal_manager_t>())) slot_type;
            /*call_type and is_void inhereted*/

            //inherited:
            //call_type
            //is_void

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

        //************************
        // SERIALIZED INTO char * slot
        //
        //***********************

        /*
        template <bool , typename index_type,typename signal_t>
        struct delegate_leaf{
            virtual void make_task(Args...) = 0;
            virtual void destroy() = 0;
            virtual void invoke(Args...) = 0;
            
            static constexpr size_t data_size = ( ((leaf_size + alignof(index_type) - 1) / alignof(index_type) ) * alignof(index_type)  )-
                                        3*sizeof(index_type) - sizeof(delegate_functions_size_test<Args...>); 
            char data[data_size];
            inline delegate_leaf(){
                static_assert(leaf_size > sizeof(delegate_leaf), "too little size of delegate list in signals");
                static_assert(data_size > sizeof(index_type), "too little size of delegate list in signals");
            }
            index_type ref_counter;
            index_type prev,next;
        };*/

        //Allocator sould have size_t leaf_size, allocate()->index_t and deallocate(index_t), index_t _id should have function _id.to_ptr() -> void *, 
        
        //for only slot signals and signals with trivially copyable slots 
        template <typename...Args>
        struct __any_slot_functions{
            void (*make_task) (void * slot_ptr,Args...) ;
            void (*destroy) (void * slot_ptr) ;
            void (*invoke) (void * slot_ptr,Args...);
        };

        //for only slot signals and signals with not trivially copyable (destructible) slots 
        template <typename...Args>
        struct __any_slot_signal_functions{
            void (*make_task) (void * slot_ptr,void * signal_ptr,Args...) ;
            void (*destroy) (void * slot_ptr) ;
            void (*invoke) (void * slot_ptr,Args...);
        };

        template <typename LabelClass,typename FuncType1,typename FuncType2,typename FuncType3,typename...Args>
        struct __vtable_slot_functions : __any_slot_functions<Args...>{
            static __vtable_slot_functions * get_instance(FuncType1 f1,FuncType2 f2,FuncType3 f3){
                static __vtable_slot_functions funs{{f1,f2,f3}};
                return &funs;
            } 
            private:
            __vtable_slot_functions(__any_slot_functions<Args...> funcs) :__any_slot_functions<Args...>(funcs){}
            __vtable_slot_functions(__vtable_slot_functions const &) = delete;
            __vtable_slot_functions(__vtable_slot_functions &&) = delete;
        };

        template <typename LabelType,typename...Args, typename FuncType1,typename FuncType2,typename FuncType3>
        auto make_vtable_slot_functions(FuncType1 f1,FuncType2 f2, FuncType3 f3){
            return __vtable_slot_functions<LabelType,FuncType1,FuncType2,FuncType3,Args...>::get_instance(f1,f2,f3);
        }

        template <typename LabelClass,typename FuncType1,typename FuncType2,typename FuncType3,typename...Args>
        struct __vtable_slot_signal_functions : __any_slot_signal_functions<Args...>{
            static __vtable_slot_signal_functions * get_instance(FuncType1 f1,FuncType2 f2,FuncType3 f3){
                static __vtable_slot_signal_functions funs{{f1,f2,f3}};
                return &funs;
            } 
            private:
            __vtable_slot_signal_functions(__any_slot_signal_functions<Args...> funcs) :__any_slot_signal_functions<Args...>(funcs){}
            __vtable_slot_signal_functions(__any_slot_signal_functions const &) = delete;
            __vtable_slot_signal_functions(__any_slot_signal_functions &&) = delete;
        };

        template <typename LabelType,typename...Args, typename FuncType1,typename FuncType2,typename FuncType3>
        auto make_vtable_slot_signal_functions(FuncType1 f1,FuncType2 f2, FuncType3 f3){
            return __vtable_slot_signal_functions<LabelType,FuncType1,FuncType2,FuncType3,Args...>::get_instance(f1,f2,f3);
        }
        
        template <typename T>
        T default_value(){
            static_assert(std::is_trivially_constructible<meta_signal_t>::value,
                            "non trivially constructible classes couldn't be used as default parametrs");
            return T{};
        }
        
        /*
        template <bool _size_enough, size_t _size,typename FuncType,typename Allocator,typename...Args>
        struct __any_slot : public __any_slot_base{
            template 
        };*/

        //****0*****************************************
        //***00**1) SPECIFIED ONLY SLOT*****************
        //**0*0**1) SPECIFIED ONLY SLOT*****************
        //****0**1) SPECIFIED ONLY SLOT*****************
        //****0*****************************************

        template <typename task_queue_getter_t,typename meta_signal_manager_t,typename...Args>
        struct __signal_specified_only_slot{
            typedef typename meta_signal_manager_t::signal_manager_t signal_manager_t;
            struct __slot_t{
                typedef typename meta_signal_manager_t::slot_type slot_type;
                slot_type slot;
                inline __slot_t(slot_type slot):slot(std::move(slot)){}
            };



            template <bool __first_slot_than_meta>
            struct __managed_slot_option : public __slot_t, public signal_manager_t{
                inline __managed_slot(__slot_t __slot,signal_manager_t __meta) :
                __slot_t(std::move(__slot)),signal_manager_t(std::move(__meta)){}
            };
            template <>
            struct __managed_slot_option<false> : public signal_manager_t , public __slot_t{
                inline __managed_slot(__slot_t __slot,signal_manager_t __meta) :
                signal_manager_t(std::move(__meta)),__slot_t(std::move(__slot)){}
            };

            typedef __managed_slot_option<(alignof(__slot_t) > alignof(signal_manager_t))> __managed_slot;

            struct alignas(alignof(__managed_slot)) __connectable_managed_slot_placement{
                inline typename __managed_slot & get_managed_slot(){
                    return *reinteret_cast<__managed_slot*>(data);
                }
                typename __managed_slot::slot_type & get_slot(){
                    return get_managed_slot().slot;
                }
                typename __managed_slot::slot_type & get_meta(){
                    return static_cast<signal_manager_t &> (get_managed_slot());
                }
                template <bool __trivially_constructed_manager>
                
                inline bool connect(__slot_t __slot,signal_manager_t __smanager = default_value<signal_manager_t>()){
                    bool ret = true;
                    guard.lock();
                    if(!ref_counter){
                        new (&data) __managed_slot(std::move(__slot),std::move(__smanager));
                        ref_counter |= 1;
                    } else {
                        ret= false;
                    }
                    guard.unlock();
                    return ret;
                }
                inline void disconnect(){
                    guard.lock();
                    __disconnect_impl();
                    guard.unlock();
                }

                protected:
                char data[sizeof(__managed_slot)];
                meta_signal_manager_t::guard_t guard;
                uint8_t ref_counter;

                inline void __disconnect_impl(){
                    ref_counter &= ~((uint8_t)1);
                    if(!ref_counter){
                        get_managed_slot().~__managed_slot();
                    }
                }

                inline void __make_task_impl(Args...args){
                    if constexpr (meta_signal_manager_t::fast_call){
                        task_queue_getter_t::get().put_bind<Args...>([_slot = get_slot()](Args...args){ _slot(args...);},args...);
                    } else {
                        static_assert("in only slot signal it possible to use only fast_call");
                        /*
                        ref_counter += 2;
                        task_queue_getter_t::get().put_bind<Args...>([this](Args...args){ 
                            guard.lock();
                            get_slot()(args...);
                            ref_counter -= 2;
                            if(!ref_counter){
                                __disconnect_impl();
                            }
                            guard.unlock();
                        },args...);
                        */
                    }
                }
                inline void __direct_call_impl(Args...args){
                    get_slot()(args...);
                }


            };
            template <bool is_void_call_type>
            struct __callable_slot : public __connectable_managed_slot_placement{
                void operator()(signal_manager_t::call_type call_info,Args...args){
                    this->guard->lock();
                    if(this->ref_counter){
                        if constexpr(meta_signal_manager_t::meta_direct_call_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_direct_call_t::constexp_value) {
                                goto DirectCall;
                            } else {
                                goto DelayedCall;
                            }
                        } else {
                            if(get_meta().direct_call(call_info)){
                                goto DirectCall;
                            } else {
                                goto DelayedCall;
                            }
                        }
                        
                        DirectCall:
                        if constexpr(meta_signal_manager_t::meta_call_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_call_ready_t::constexp_value) {
                                __direct_call_impl(args...);
                            } 
                        } else {
                            if(get_delegate().call_ready(call_info)){
                                __direct_call_impl(args...);
                            }
                        } 
                        goto Continue;
                        DelayedCall:
                        if constexpr(meta_signal_manager_t::meta_call_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_call_ready_t::constexp_value) {
                                __make_task_impl(args...);
                            } 
                        } else {
                            if(get_delegate().call_ready(call_info)){
                                __make_task_impl(args...);
                            }
                        }
                        goto Continue;
                        Continue:
                        if constexpr(meta_signal_manager_t::meta_destroy_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_destroy_ready_t::constexp_value) {
                                __disconnect_impl();
                            } 
                        } else {
                            if(get_delegate().meta_destroy_ready(call_info)){
                                __disconnect_impl();
                            }
                        }
                    }
                    this->guard->unlock();
                }
            };
            template <>
            struct __callable_slot<true> : public __connectable_managed_slot_placement{
                void operator()(Args...args){
                    this->guard->lock();
                    if(this->ref_counter){
                        if constexpr(meta_signal_manager_t::meta_direct_call_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_direct_call_t::constexp_value) {
                                goto DirectCall;
                            } else {
                                goto DelayedCall;
                            }
                        } else {
                            if(get_meta().direct_call()){
                                goto DirectCall;
                            } else {
                                goto DelayedCall;
                            }
                        }
                        
                        DirectCall:
                        if constexpr(meta_signal_manager_t::meta_call_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_call_ready_t::constexp_value) {
                                __direct_call_impl(args...);
                            } 
                        } else {
                            if(get_delegate().call_ready()){
                                __direct_call_impl(args...);
                            }
                        } 
                        goto Continue;
                        DelayedCall:
                        if constexpr(meta_signal_manager_t::meta_call_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_call_ready_t::constexp_value) {
                                __make_task_impl(args...);
                            } 
                        } else {
                            if(get_delegate().call_ready()){
                                __make_task_impl(args...);
                            }
                        }
                        goto Continue;
                        Continue:
                        if constexpr(meta_signal_manager_t::meta_destroy_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_destroy_ready_t::constexp_value) {
                                __disconnect_impl();
                            } 
                        } else {
                            if(get_delegate().meta_destroy_ready()){
                                __disconnect_impl();
                            }
                        }
                    }
                    this->guard->unlock();
                }
            };
        };

        //**00******************************************
        //*0**0**2) NOT SPECIFIED ONLY SLOT*************
        //***0 **2) NOT SPECIFIED ONLY SLOT*************
        //**0  **2) NOT SPECIFIED ONLY SLOT*************
        //*0000*****************************************

        //Allocator shoud have static constaant Allocator::size, type ptr_type, 
        //  function  ptr_type allocate(), deallocate(ptr_type), ptr_type should have functon ptr()
        template <typename Allocator,typename task_queue_getter_t,typename meta_signal_manager_t,typename...Args>
        struct __signal_not_specified_only_slot{

            typedef typename meta_signal_manager_t::signal_manager_t signal_manager_t;
            struct alignas(alignof(max_align_t)) __slot_t{
                typedef typename Allocator::ptr_type ptr_type;
                constexpr static size_t size = meta_signal_manager_t::size;
                char data[size];
                inline void * lambda_ptr(){
                    return reinterpret_cast<ptr_type*>(&data)->ptr();
                }
                __any_slot_functions *vtable_ptr;
            };



            struct __managed_slot_option : public __slot_t, public signal_manager_t{
                inline __managed_slot(signal_manager_t __meta) :
                signal_manager_t(std::move(__meta)){}
            };

            struct alignas(alignof(__managed_slot)) __connectable_managed_slot_placement{
                inline typename __managed_slot & get_managed_slot(){
                    return *reinteret_cast<__managed_slot*>(data);
                }
                typename __managed_slot::slot_type & get_slot(){
                    return get_managed_slot();
                }
                typename __managed_slot::slot_type & get_meta(){
                    return static_cast<signal_manager_t &> (get_managed_slot());
                }
                template <bool __trivially_constructed_manager>
                            
                private:
                template <typename Lambda_t>
                inline auto set_slot(Lambda_t __slot){
                    constexpr bool is_directly_not_invokable = 
                        meta_signal_manager_t::meta_direct_call_t::is_constexpr_function && 
                        !meta_signal_manager_t::meta_direct_call_t::constexp_value;
                    
                    if constexpr(sizeof(Lambda) < __slot_t::size) {
                        new (&get_slot().data) Lambda_t(std::move(__slot));

                        auto invoke_function = [](){
                            if(is_directly_not_invokable) {
                                return reinterpret_cast<(void)(*)(void *,Artg...)>(0);
                            } else {
                                return [](void *slot_ptr,Args...args){
                                    auto * _this = static_cast<__connectable_managed_slot_placement*>(slot_ptr);
                                    *reinterpret_cast<Lambda_t*>(_this->get_slot().data)(args...);
                                };
                            }

                        } ();

                        get_slot().vtable_ptr = make_vtable_slot_functions<void>(
                            /*make_task function*/
                            [](void *signal_ptr,Args...args){
                                auto * _this = static_cast<__connectable_managed_slot_placement*>(slot_ptr);
                                if constexpr(meta_signal_manager_t::fast_call){
                                    task_queue_getter_t::get().put_bind<Args...>([_slot = *reinterpret_cast<Lambda_t*>(_this->get_slot().data)](Args...args){ _slot(args...);},args...);
                                } else {
                                    static_assert("in only slot signal it possible to use only fast_call");
                                    /*
                                    _this->ref_counter += 2;
                                    task_queue_getter_t::get().put_bind<Args...>([_this](Args...args){ 
                                        _this->guard.lock();
                                        *reinterpret_cast<Lambda_t*>(_this->get_slot().data)(args...);
                                        _this->ref_counter -= 2;
                                        if(!_this->ref_counter){
                                            _this->__disconnect_impl();
                                        }
                                        _this->guard.unlock();
                                    },args...);
                                    */
                                }
                            },/*destroy function*/
                            [](void * slot_ptr){
                                auto * _this = static_cast<__slot_t*>(slot_ptr);
                                reinterpret_cast<Lambda_t*>(_this->data)->~Lambda_t();
                            },/*invoke function*/
                            std::move(invoke_function)
                            );     

                    } else {
                        static_assert(sizeof(Lambda_t) < Allocator::size,"size of slot type should be less than allocated bye mem_array");
                        get_slot().lambda_ptr() = Allocator::allocate();
                        new (get_slot().lambda_ptr()->ptr()) Lambda_t(std::move(__slot));
                       
                        auto invoke_function = [](){
                            if constexpr (is_directly_not_invokable) {
                                return reinterpret_cast<(void)(*)(void *,Artg...)>(0);
                            } else {
                                return [](void *slot_ptr,Args...args){
                                    auto * _this = static_cast<__connectable_managed_slot_placement*>(slot_ptr);
                                    *reinterpret_cast<Lambda_t*>(_this->get_slot().lambda_ptr()->ptr())(args...);
                                };
                            }
                        } ();

                        get_slot().vtable_ptr = make_vtable_slot_functions<void>(
                            /*make_task function*/
                            [](void *signal_ptr,Args...args){
                                auto * _this = static_cast<__connectable_managed_slot_placement*>(slot_ptr);
                                if constexpr(meta_signal_manager_t::fast_call){
                                    task_queue_getter_t::get().put_bind<Args...>(
                                        [_slot = *reinterpret_cast<Lambda_t*>(_this->get_slot().lambda_ptr()->ptr())]
                                        (Args...args){ _slot(args...);},args...);
                                } else {
                                    static_assert("in only slot signal it possible to use only fast_call");
                                    /*
                                    _this->ref_counter += 2;
                                    task_queue_getter_t::get().put_bind<Args...>([_this](Args...args){ 
                                        _this->guard.lock();
                                        *reinterpret_cast<Lambda_t*>(_this->get_slot().lambda_ptr()->ptr())(args...);
                                        _this->ref_counter -= 2;
                                        if(!_this->ref_counter){
                                            _this->__disconnect_impl();
                                        }
                                        _this->guard.unlock();
                                    },args...);
                                    */
                                }
                            },/*destroy function*/
                            [](void * slot_ptr){
                                auto * _this = static_cast<__slot_t*>(slot_ptr);
                                reinterpret_cast<Lambda_t*>(_this->data)->~Lambda_t();
                                Allocator::deallocate(_this->get_slot().lambda_ptr());
                            },/*invoke function*/
                            std::move(invoke_function)
                            );     

                    
                    }
                }
                public:
                template <typename T>
                inline bool connect(T *Reciever, void (T::*Slot)(Args...) ,signal_manager_t __smanager = default_value<signal_manager_t>()){
                    return connect([Reciever,Slot](Args...args){(Reciever->*Slot)(args...)},std::move(__smanager));
                }

                template <typename Lambda_t>
                inline bool connect(Lambda_t __slot,signal_manager_t __smanager = default_value<signal_manager_t>()){
                    bool ret = true;
                    guard.lock();
                    if(!ref_counter){
                        new (&data) __managed_slot(std::move(__smanager));
                        set_slot(std::move(__slot));
                        ref_counter = 1;
                    } else {
                        ret= false;
                    }
                    guard.unlock();
                    return ret;
                }
                inline void disconnect(){
                    guard.lock();
                    __disconnect_impl();
                    guard.unlock();
                }

                protected:
                char data[sizeof(__managed_slot)];
                meta_signal_manager_t::guard_t guard;
                uint8_t ref_counter;

                inline void __disconnect_impl(){
                    if(!ref_counter){
                        get_slot().vtable_ptr->destroy(static_cast<void *>(&get_slot()));
                        get_managed_slot().~__managed_slot();
                        ref_counter = 0;
                    }
                }

                inline void __make_task_impl(Args...args){
                    if constexpr (meta_signal_manager_t::fast_call && std::is_trivially_copiable<__slot_t>::value){
                        task_queue_getter_t::get().put_bind<Args...>([_slot = get_slot()](Args...args){ _slot(args...);},args...);
                    } else {
                        static_assert("in only slot signal it possible to use only fast_call");
                        /*
                        ref_counter += 2;
                        task_queue_getter_t::get().put_bind<Args...>([this](Args...args){ 
                            guard.lock();
                            get_slot()(args...);
                            ref_counter -= 2;
                            if(!ref_counter){
                                __disconnect_impl();
                            }
                            guard.unlock();
                        },args...);
                        */
                    }
                }
                inline void __direct_call_impl(Args...args){
                    get_slot()(args...);
                }


            };
            template <bool is_void_call_type>
            struct __callable_slot : public __connectable_managed_slot_placement{
                void operator()(signal_manager_t::call_type call_info,Args...args){
                    this->guard->lock();
                    if(this->ref_counter){
                        if constexpr(meta_signal_manager_t::meta_direct_call_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_direct_call_t::constexp_value) {
                                goto DirectCall;
                            } else {
                                goto DelayedCall;
                            }
                        } else {
                            if(get_meta().direct_call(call_info)){
                                goto DirectCall;
                            } else {
                                goto DelayedCall;
                            }
                        }
                        
                        DirectCall:
                        if constexpr(meta_signal_manager_t::meta_call_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_call_ready_t::constexp_value) {
                                __direct_call_impl(args...);
                            } 
                        } else {
                            if(get_delegate().call_ready(call_info)){
                                __direct_call_impl(args...);
                            }
                        } 
                        goto Continue;
                        DelayedCall:
                        if constexpr(meta_signal_manager_t::meta_call_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_call_ready_t::constexp_value) {
                                __make_task_impl(args...);
                            } 
                        } else {
                            if(get_delegate().call_ready(call_info)){
                                __make_task_impl(args...);
                            }
                        }
                        goto Continue;
                        Continue:
                        if constexpr(meta_signal_manager_t::meta_destroy_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_destroy_ready_t::constexp_value) {
                                __disconnect_impl();
                            } 
                        } else {
                            if(get_delegate().meta_destroy_ready(call_info)){
                                __disconnect_impl();
                            }
                        }
                    }

                }
            };
            template <>
            struct __callable_slot<true> : public __connectable_managed_slot_placement{
                void operator()(Args...args){
                    this->guard->lock();
                    if(this->ref_counter){
                        if constexpr(meta_signal_manager_t::meta_direct_call_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_direct_call_t::constexp_value) {
                                goto DirectCall;
                            } else {
                                goto DelayedCall;
                            }
                        } else {
                            if(get_meta().direct_call()){
                                goto DirectCall;
                            } else {
                                goto DelayedCall;
                            }
                        }
                        
                        DirectCall:
                        if constexpr(meta_signal_manager_t::meta_call_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_call_ready_t::constexp_value) {
                                __direct_call_impl(args...);
                            } 
                        } else {
                            if(get_delegate().call_ready()){
                                __direct_call_impl(args...);
                            }
                        } 
                        goto Continue;
                        DelayedCall:
                        if constexpr(meta_signal_manager_t::meta_call_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_call_ready_t::constexp_value) {
                                __make_task_impl(args...);
                            } 
                        } else {
                            if(get_delegate().call_ready()){
                                __make_task_impl(args...);
                            }
                        }
                        goto Continue;
                        Continue:
                        if constexpr(meta_signal_manager_t::meta_destroy_ready_t::is_constexpr_function){
                            if constexpr( meta_signal_manager_t::meta_destroy_ready_t::constexp_value) {
                                __disconnect_impl();
                            } 
                        } else {
                            if(get_delegate().meta_destroy_ready()){
                                __disconnect_impl();
                            }
                        }
                    }

                }
            };
        };
        

        template <typename mem_array_gatter_t,typename default_guard_t,typename signal_manager_t,typename signal_signature_t>
        struct __signal_impl__;
    
        
        template <typename mem_array_getter_t,typename default_guard_t,typename signal_manager_t,typename...Args>
        struct __signal_impl__<mem_array_getter_t,default_guard_t,signal_manager_t,void(Args...)>{};
    };
};

#endif//SIGNAL_IMPL_HPP