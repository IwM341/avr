/*
 * size_types.h
 *
 * Created: 09.04.2023 11:58:28
 *  Author: MainUser
 */ 


#ifndef SIZE_TYPES_H_
#define SIZE_TYPES_H_


#include <limits.h>
#include "type_traits.h"

namespace aos{
	
	/**
		\brief meta class, which contains the shortest int type for value
		example of usage
		\code
		typename min_required_size_type<256>::type;
		\endcode
	*/
	template <int64_t value>
	struct min_required_size_type;
	
	/**
		\brief meta class, indicating bounds of int_type
		have static members min and max
	*/
	template <typename int_type>
	struct int_bounds;
	
	template <>
	struct int_bounds<unsigned char>{
		constexpr static auto min = 0;
		constexpr static auto max = UCHAR_MAX;	
	};
	template <>
	struct int_bounds<signed char>{
		constexpr static auto min = SCHAR_MIN;
		constexpr static auto max = SCHAR_MAX;
	};
	
	template <>
	struct int_bounds<char>{
		constexpr static auto min = CHAR_MIN;
		constexpr static auto max = CHAR_MAX;
	};
	
	
	template <>
	struct int_bounds<unsigned int>{
		constexpr static auto min = 0;
		constexpr static auto max = UINT_MAX;
	};
	template <>
	struct int_bounds<int>{
		constexpr static auto min = INT_MIN;
		constexpr static auto max = INT_MAX;
	};
	
	template <>
	struct int_bounds<unsigned short>{
		constexpr static auto min = 0;
		constexpr static auto max = USHRT_MAX;
	};
	template <>
	struct int_bounds<short>{
		constexpr static auto min = SHRT_MIN;
		constexpr static auto max = SHRT_MAX;
	};
	
	
	template <>
	struct int_bounds<unsigned long int>{
		constexpr static auto min = 0;
		constexpr static auto max = ULONG_MAX;
	};
	template <>
	struct int_bounds<long int>{
		constexpr static auto min = LONG_MIN;
		constexpr static auto max = LONG_MAX;
	};
	
	template <>
	struct int_bounds<unsigned long long int>{
		constexpr static auto min = 0;
		constexpr static auto max = ULLONG_MAX;
	};
	template <>
	struct int_bounds<long long int>{
		constexpr static auto min = LLONG_MIN;
		constexpr static auto max = LLONG_MAX;
	};
	
	template <size_t index>
	struct type_array;
	
	template <>
	struct type_array<0>{
		typedef unsigned char type;
	};
	template <>
	struct type_array<1>{
		typedef unsigned short type;
	};
	template <>
	struct type_array<2>{
		typedef unsigned int type;
	};
	template <>
	struct type_array<3>{
		typedef unsigned long int type;
	};

	template <>
	struct type_array<4>{
		typedef unsigned long long int type;
	};

	template <>
	struct type_array<5>{
		typedef char type;
	};
	template <>
	struct type_array<6>{
		typedef signed char type;
	};
	
	template <>
	struct type_array<7>{
		typedef short type;
	};
	
	template <>
	struct type_array<8>{
		typedef int type;
	};
	
	template <>
	struct type_array<9>{
		typedef long int type;
	};
	
	template <>
	struct type_array<10>{
		typedef  long long int type;
	};
	
	template <size_t index,int64_t value>
	struct loop_type_array{
		typedef typename aos::conditional<int_bounds<typename type_array<index>::type>::min <= value && 
			int_bounds<typename type_array<index>::type>::max >= value,typename type_array<index>::type,
			typename loop_type_array<index+1,value>::type>::type type;	
	};
	template <int64_t value>
	struct loop_type_array<10,value>{
		typedef type_array<10>::type type;
	};
	
	template <int64_t value>
	struct min_required_size_type{
		typedef typename loop_type_array<0,value>::type type;
	};
		
};


#endif /* SIZE_TYPES_H_ */