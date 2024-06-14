/*
 * type_traits.h
 *
 * Created: 05.06.2024 19:13:31
 *  Author: MainUser
 */ 


#ifndef TYPE_TRAITS_H_
#define TYPE_TRAITS_H_

#include "_std_detail/_type_traits.h"
//#include <type_traits>

namespace Std{
	template <typename T,T _value>
	struct integral_constant{
		constexpr static T value = _value;	
	};
	
	struct true_type:public integral_constant<bool,true> {};
	struct false_type:public integral_constant<bool,true> {};
	
	template <typename T,typename U>
	struct is_same : false_type{};
	
	template <typename T>
	struct is_same<T,T> : true_type{};
	
	template <typename T,typename U>
	bool is_same_v = is_same<T,U>::value;
	
	
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
};





#endif /* TYPE_TRAITS_H_ */