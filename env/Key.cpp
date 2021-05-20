// Key.cpp		: implementation of the CKey class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Key.h"
#include <string>
#include <assert.h>

//////////////////////////////////////////////////////////////////////
// class CKeyIndex
//////////////////////////////////////////////////////////////////////

CKey* CKeyIndex::GetKey(const std::string &_string, unsigned int _charNo)
{
	if(_string.size()==_charNo)
	{
		if(myKey==NULL)
			myKey=new CKey();
		return myKey;
	}

	char chr=_string[_charNo];
	std::map<char, CKeyIndex*>::iterator it=myIndex.find(chr);
	if(it==myIndex.end())
	{
		myIndex[chr]=new CKeyIndex;
		it=myIndex.find(chr);
	}
	return it->second->GetKey(_string, _charNo+1);
}

void CKeyIndex::Clear()
{
	for(std::map<char, CKeyIndex*>::iterator it=myIndex.begin(); it!=myIndex.end(); ++it)
		delete it->second;

	myIndex.clear();
}

CKeyIndex::~CKeyIndex()
{
	if(myKey)
		delete myKey;

	for(std::map<char, CKeyIndex*>::iterator it=myIndex.begin(); it!=myIndex.end(); ++it)
		delete it->second;
}

//////////////////////////////////////////////////////////////////////
// class CKey
//////////////////////////////////////////////////////////////////////

CKeyIndex CKey::myIndex;
std::vector<std::string> CKey::myKeyNames;

unsigned int CKey::GetKey(const std::string &_name)
{
	unsigned int keySize=myKeyNames.size();
	std::string str=_name;
	assert(str.size()>0);
	CKey* key=myIndex.GetKey(str, 0);
	if(keySize==key->GetKey())
		myKeyNames.push_back(_name);
	return key->GetKey();
}

CKey::CKey()
{
	myKey=myKeyNames.size();
}
