/*
 * type_traits.h
 *
 * Created: 05.06.2024 19:13:31
 *  Author: MainUser
 */ 


#ifndef TYPE_TRAITS_H_
#define TYPE_TRAITS_H_

#include "_std_detail/_type_traits.h"

#include <stdint.h>
#include <stdlib.h>

namespace Std{
	template <typename T,T _value>
	struct integral_constant{
		constexpr static T value = _value;	
	};
	
	struct true_type:public integral_constant<bool,true> {};
	struct false_type:public integral_constant<bool,false> {};
	
	template <typename T,typename U>
	struct is_same : false_type{};
	
	template <typename T>
	struct is_same<T,T> : true_type{};
	
	template <typename T,typename U>
	constexpr bool is_same_v = is_same<T,U>::value;
	
	
	template <bool _condition,typename T>
	struct enable_if{};
	
	
	template <typename T>
	struct enable_if<true,T>{
		typedef T type;
	};
	
	template <bool _condition,typename T>
	using enable_if_t = typename enable_if<_condition,T>::type;
	
	template <typename _T1,typename _T2,typename _TRes>
	struct enable_if_same:enable_if<is_same_v<_T1,_T2>,_TRes>{};
		
	template <typename _T1,typename _T2,typename _TRes>
	struct enable_if_not_same:enable_if<!is_same_v<_T1,_T2>,_TRes>{};
	
	template <typename _T1,typename _T2,typename _TRes>
	using enable_if_same_t = typename enable_if_same<_T1,_T2,_TRes>::type;
	
	template <typename _T1,typename _T2,typename _TRes>
	using enable_if_not_same_t = typename enable_if_not_same<_T1,_T2,_TRes>::type;
	
	template <bool _condition,typename _type_if_true,typename _type_if_false>
	struct conditional{
		typedef _type_if_true type;
	};
	
	template <typename _type_if_true,typename _type_if_false>
	struct conditional<false,_type_if_true,_type_if_false>{
		typedef _type_if_false type;
	};
	
	template <bool _condition,typename _type_if_true,typename _type_if_false>
	using conditional_t = typename conditional<_condition,_type_if_true,_type_if_false>::type;

	template <typename T>
	struct type_identity{
		typedef T type;
	};

	template< class T >
	using type_identity_t = typename type_identity<T>::type;
	
	
	

	
	template <typename T>
	struct remove_reference{
		typedef T type;	
	};
	template <typename T>
	struct remove_reference<T &>{
		typedef T type;
	};
	template <typename T>
	struct remove_reference<T &&>{
		typedef T type;
	};
	template <typename T>
	using remove_reference_t = typename remove_reference<T>::type;
	
	
	template <typename T>
	struct remove_cv{
		typedef T type;
	};
	template <typename T>
	struct remove_cv<const T>{
		typedef T type;
	};
	template <typename T>
	struct remove_cv<volatile T>{
		typedef T type;
	};
	template <typename T>
	struct remove_cv<const volatile T>{
		typedef T type;
	};
	template <typename T>
	struct remove_cv<T &>{
		typedef typename remove_cv<T>::type  & type;
	};
	template <typename T>
	struct remove_cv<T &&>{
		typedef typename remove_cv<T>::type  && type;
	};
	
	template <typename T>
	using remove_cv_t = typename remove_cv<T>::type;
	
	template <typename T>
	struct decay{
		typedef remove_cv_t<remove_reference_t<T>> type;
	};
	template <typename T>
	using decay_t = typename decay<T>::type;
	
	template <typename T>
	struct is_lvalue_reference:public false_type{};
	
	template <typename T>
	struct is_lvalue_reference<T &>:public false_type{};
	
	template <typename T>
	struct is_lvalue_reference<T &&>:public true_type{};
	
	template <typename T>
	constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;
	
	
	
	namespace __detail
	{
		template<class T> // Note that “cv void&” is a substitution failure
		auto try_add_lvalue_reference(int) -> type_identity<T&>;
		template<class T> // Handle T = cv void case
		auto try_add_lvalue_reference(...) -> type_identity<T>;
		
		template<class T>
		auto try_add_rvalue_reference(int) -> type_identity<T&&>;
		template<class T>
		auto try_add_rvalue_reference(...) -> type_identity<T>;
	} // namespace detail
	
	template<class T>
	struct add_lvalue_reference
	: decltype(__detail::try_add_lvalue_reference<T>(0)) {};
	
	template<class T>
	struct add_rvalue_reference
	: decltype(__detail::try_add_rvalue_reference<T>(0)) {};
	
	template<typename T>
	typename add_rvalue_reference<T>::type declval() noexcept
	{
		static_assert(!is_same_v<T,T>, "declval not allowed in an evaluated context");
	}
	
	template<class _Func_t, class...ArgTypes>
	struct invoke_result{
		typedef decltype(declval<_Func_t>() (declval<ArgTypes>()...) ) type;	
	};
	
	template<class _Func_t, class...ArgTypes>
	using invoke_result_t = typename invoke_result<_Func_t,ArgTypes...>::type;
	
	template <typename T>
	inline constexpr T && move(T && _arg){
		return static_cast<T &&>(_arg);
	}
	
	template <typename T>
	constexpr T&& forward(remove_reference_t<T>& arg) noexcept {
		return static_cast<T&&>(arg);
	}

	template <typename T>
	constexpr T&& forward(remove_reference_t<T>&& arg) noexcept {
		static_assert(is_lvalue_reference_v<T>, "Forwarding an rvalue as an lvalue is not allowed.");
		return static_cast<T&&>(arg);
	}
	
	
	
	template <typename T,size_t N>
	struct array{
		T _data[N];
		
		array(){}
		constexpr inline array(T * m_data){
			for (size_t i=0;i<N;++i)
			{
				_data[i] = m_data[i];
			}
		}
		template <typename...Args>
		inline array(Args &&... args){
			
		}
		
		inline constexpr size_t size()const{
			return N;
		}
		inline T & operator [](size_t i){
			return _data[i];
		}
		inline T const & operator [](size_t i)const{
			return _data[i];
		}
		T * begin(){
			return _data;
		}
		T * end(){
			return _data+N;
		}
		const T * cbegin()const{
			return _data;
		}
		const T * cend()const{
			return _data+N;
		}
		const T * data()const{
			return _data;
		}
		T * data(){
			return _data;
		}
		
		template <typename Condition_t>
		inline size_t find_if(Condition_t && m_condition) const{
			for(size_t i=0;i<N;++i){
				if(m_condition(_data[i])){
					return i;
				}
			}
			return N;
		}
		
		template <typename U>
		inline size_t find(const U & _cmprtr) const{
			return find_if([&_cmprtr](const T & _this){return  _cmprtr == _this	;});
		}

		private:
		template <size_t idx,typename _T,typename...Args>
		inline void _fill_args(_T && _first,Args&&...other,integral_constant<size_t,idx>){
			_data[idx] = forward<T>(_first);
			_fill_args(forward<Args>(other)...,integral_constant<size_t,idx+1>{});
		}
		
		template <size_t idx>
		inline void _fill_args(integral_constant<size_t,idx>){
			static_assert(idx < N,"out of range");
		}
	};
};





#endif /* TYPE_TRAITS_H_ */