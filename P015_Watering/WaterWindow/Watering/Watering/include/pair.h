#pragma once

namespace Std{
	template <typename T,typename U>
	struct pair{
		T first;
		U second;
	};
	
	template <typename T,typename U>
	pair<decay_t<T>,decay_t<T>> make_pair(T && _arg1,U && _arg2){
		return {forward<T>(_arg1),forward<U>(_arg2)};
	}
};