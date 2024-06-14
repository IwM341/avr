/*
 * type_traits.h
 *
 * Created: 09.04.2023 12:24:40
 *  Author: MainUser
 */ 


#ifndef TYPE_TRAITS_H_
#define TYPE_TRAITS_H_

#define __INLINE__ __attribute__((always_inline))

namespace aos{
	/**
	 * same as std::conditional
	*/
	template <bool b,typename type1,typename type2>
	struct conditional{
		typedef type1 type;
	};
	template <typename type1,typename type2>
	struct conditional<false,type1,type2>{
		typedef type2 type;
	};
	
	/**
	 * same as std::enable if
	*/
	template <bool condition,typename T = void>
	struct enable_if{};
	
	template <typename T>
	struct enable_if<true,T>{
		typedef T type;
	};

	/**
	 * same as std::is_same 
	*/
	template <typename T,typename U>
	struct is_same{
		constexpr static bool value = false;
	};
	template <typename T>
	struct is_same<T,T>{
		constexpr static bool value = true;
	};

	
	/**
	 * empty variadic size_t template class
	*/
	template<size_t...I>
	struct index_sequence{};
	
	/**
	 * gets value from index_sequence
	*/
	template <size_t i,typename seq>
	struct get_value;
	
	template <size_t i,size_t I0,size_t...I>
	struct get_value<i,index_sequence<I0,I...>>{
		constexpr static size_t value = get_value<i-1,index_sequence<I...>>::value;
	};
	template <size_t I0,size_t...I>
	struct get_value<0,index_sequence<I0,I...>>{
		constexpr static size_t value = I0;
	};
	
	
	/**
	 * insert value left to index_sequence
	*/
	template <size_t I,typename Seq2>
	struct index_sequence_cat_left;
	
	template <size_t I,size_t...J>
	struct index_sequence_cat_left<I,index_sequence<J...>>{
		typedef index_sequence<I,J...> type;
	};
	
	/**
	 * insert value right to index_sequence
	*/
	template <typename Seq2,size_t I>
	struct index_sequence_cat_right;
	
	template <size_t I,size_t...J>
	struct index_sequence_cat_right<index_sequence<J...>,I>{
		typedef index_sequence<J...,I> type;
	};
	

	/**
	 * variadic arg sequence
	*/
	template <typename...Args>
	struct arg_sequence{};

	/**
	 * number of args
	*/
	template <typename...Args>
	struct arg_count;
	

	/**
	 * sum for all sizeof(Args)
	*/
	template <typename...Args>
	struct args_size;
	
	template <>
	struct arg_count<>{
		constexpr static size_t value = 0;
	};
	
	
	template <>
	struct args_size<>{
		constexpr static size_t value = 0;
	};
	
	
	template <typename Arg0,typename...Args>
	struct arg_count<Arg0,Args...>{
		constexpr static size_t value = 1 + arg_count<Args...>::value;
	};
	
	template <typename Arg0,typename...Args>
	struct args_size<Arg0,Args...>{
		constexpr static size_t value = sizeof(Arg0) + args_size<Args...>::value;
	};

	/**
	 * makes index_sequence<start,start+1,...,start + num_of_args>
	*/
	template  <size_t start,typename ...Args>
	struct make_index_sequence;

	template  <size_t start,typename Arg0,typename...Args>
	struct make_index_sequence<start,Arg0,Args...>{
		typedef typename index_sequence_cat_left<start,
			typename make_index_sequence<start+1,Args...>::type
		>::type type;	
	};
	template  <size_t start,typename Arg0>
	struct make_index_sequence<start,Arg0>{
		typedef index_sequence<start> type;
	};
	template  <size_t start>
	struct make_index_sequence<start>{
		typedef index_sequence<> type;
	};
	
	
	/**
	 * same as std::remove_reference
	*/
	template <typename T>
	struct rm_ref{
		typedef T type;	
	};
	template <typename T>
	struct rm_ref<T&&>{
		typedef T type;
	};
	template <typename T>
	struct rm_ref<T&>{
		typedef T type;
	};

	template<typename T>
	constexpr bool always_false = false;
	template <typename T>
	T && declval(){
		static_assert(always_false<T>, "declval not allowed in an evaluated context");
	}
	
};


#endif /* TYPE_TRAITS_H_ */