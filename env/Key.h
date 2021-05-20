// Key.h		: interface for the CKey class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#if !defined(KEY_H)
#define KEY_H

#include "FTypes.h"

#include <string>
#include <vector>
#include <map>
#include <assert.h>

class CKey;

//////////////////////////////////////////////////////////////////////
// class CKeyIndex
//////////////////////////////////////////////////////////////////////

class CKeyIndex
{
	CKey* myKey;
	std::map<char, CKeyIndex*> myIndex;

public:
	CKeyIndex() {	
		myKey=NULL;	
	}

	CKey* GetKey(const std::string&, unsigned int);
	void Clear();

	~CKeyIndex();
};

//////////////////////////////////////////////////////////////////////
// class CKey
//////////////////////////////////////////////////////////////////////

class CKey  
{
	static CKeyIndex myIndex;
	static std::vector<std::string> myKeyNames;

	unsigned int myKey;

public:
	static Init()	
	{	
		Clear();
	}

	static Clear()	
	{			
		myIndex.Clear();
		myKeyNames.clear();
	}

	static unsigned int Size()
	{
		return myKeyNames.size();
	}

	static std::string& GetName(int _key)
	{
		assert(_key>=0 && _key<myKeyNames.size());
		return myKeyNames[_key];
	}

	static unsigned int GetKey(const std::string&);

	CKey();
	unsigned int GetKey()	{	return myKey;	}
};

#endif // !defined(KEY_H)
