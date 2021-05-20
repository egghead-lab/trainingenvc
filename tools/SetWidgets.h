// SetWidgets.h	: interface for the superset class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#if !defined(SETWIDGETS_H)
#define SETWIDGETS_H

#include <vector>

//////////////////////////////////////////////////////////////////////
//	template struct CSetWidgets - functions that help managing vectors coupled to superset
//////////////////////////////////////////////////////////////////////

template<typename T> struct CSetWidgets
{
	static void Erase(std::vector<T>& _vector, int _i)					// when T is a pointer, etc
	{
		if(_i>=0)
		{
			assert(_vector.size()>0);
			unsigned int size=_vector.size()-1;
			if(_i<size)
				_vector[_i]=_vector[size];
			_vector.resize(size);
		}
	}

	static void EraseBySwap(std::vector<T>& _vector, int _i)			// T.swap must be defined
	{
		if(_i>=0)
		{
			assert(_vector.size()>0);
			int size=_vector.size()-1;
			assert(size>=0);
			if(_i<size)
				_vector[_i].swap(_vector[size]);
			_vector.resize(size);
		}
	}
};

#endif // !defined(SETWIDGETS_H)
