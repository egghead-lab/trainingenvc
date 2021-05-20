// Sandbox.cpp: implementation of the CSandbox class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Sandbox.h"
#include "../../../env/TrainProgram.h"
#include "../../../supplements/agents/AgentLib.h"
#include "../../../env/Key.h"

#include "../../../tools/Random.h"
#include "../../../tools/Num2Str.h"
#include "../../../tools/SetWidgets.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
// class CSandbox
//////////////////////////////////////////////////////////////////////

OBJECTCOUNTER(CSandbox);

CSandbox::CSandbox()
{
	myNumeration=3;
		
	Init();
}

CSandbox::CSandbox(const unsigned int _numeration)
{
	myNumeration=_numeration;

	Init();
}

void CSandbox::Init()
{
	for(int i=0; i<myNumeration; ++i)
	{
		int activeKey=CKey::GetKey("Active digit for "+Num2String(i));
		int passiveKey=CKey::GetKey("Passive digit for "+Num2String(i));
		myRelation[activeKey]=passiveKey;
		AddActionKey(activeKey);
	}

	myEcho=false;
}

void CSandbox::Update(int _key)
{
	if(myEcho)
		std::cout << "a: " << _key << " ";

	std::map<unsigned int, unsigned int>::iterator it=myRelation.find(_key);
	assert(it!=myRelation.end());
	TuitionKey(it->second);
}