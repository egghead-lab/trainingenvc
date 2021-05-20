// Superset.h	: interface for the superset class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#if !defined(SUPERSET_H)
#define SUPERSET_H

#include <vector>
#include <map>
#include <assert.h>
#include <math.h>
#include "SetWidgets.h"
#include "Random.h"

//////////////////////////////////////////////////////////////////////
// template class superset	- provides quick access by numbers to elements of a set
//							- quick random choice of an element in a set
//////////////////////////////////////////////////////////////////////

template<typename T> class superset  
{
	std::vector<T> myVector;
	std::map<T, unsigned int> myMap;
	typename std::map<T, unsigned int>::iterator myIt;
	bool myItDefined;

	void FindIt(T _element)
	{
		if(!myItDefined || myIt->first!=_element)
		{
			myIt=myMap.find(_element);
			if(myIt!=myMap.end())
				myItDefined=true;
			else
				myItDefined=false;
		}
	}

public:
	typedef typename std::vector<T>::iterator iterator;

	superset()
	{
		myIt=myMap.begin();
		myItDefined=false;
	}

	T& operator [] (const unsigned int _number)
	{
		assert(_number<myVector.size());
		return myVector[_number];
	}

	int push_back(T _element)	
	{
		FindIt(_element);
		if(!myItDefined)
		{
			myIt=myMap.insert(myMap.begin(), std::make_pair(_element, myVector.size()));
			myVector.push_back(_element);
			return myVector.size()-1;
		}
		return -1;
	}

	int erase(T _element)
	{
		FindIt(_element);
		if(!myItDefined)
			return -1;
		
		int size=myVector.size()-1;
		assert(size>=0);
		int result=myIt->second;

		if(result<size)
		{
			myVector[result]=myVector[size];
			myMap[myVector[result]]=result;
		}
		myVector.resize(size);
		myMap.erase(myIt);
		myItDefined=false;

		return result;
	}

	int erase(iterator _it)
	{
		return erase(*_it);
	}

	int eraseBy(int _number)
	{
		if(_number<int(myVector.size()))
			return erase(myVector[_number]);
		return -1;
	}

	void swap(superset<T>& _target)
	{
		myVector.swap(_target.myVector);
		myMap.swap(_target.myMap);
		myItDefined=false;
		_target.myItDefined=false;
	}

	unsigned int size()
	{
		assert(myVector.size()==myMap.size());
		return (unsigned int)myVector.size();
	}

	iterator random()
	{
		if(myVector.size()==0)
			return myVector.end();

		int choice=CRandom::GetInt(0, myVector.size());
		return myVector.begin()+choice;
	}

	iterator begin()
	{
		return myVector.begin();
	}

	iterator end()
	{
		return myVector.end();
	}

	int find(T _element)
	{
		FindIt(_element);
		if(!myItDefined)
			return -1;
		
		return myIt->second;
	}

	bool empty()
	{
		return myVector.size()==0;
	}

	void clear()
	{
		myVector.clear();
		myMap.clear();
		myIt=myMap.begin();
		myItDefined=false;
	}
};

#endif // !defined(SUPERSET_H)
