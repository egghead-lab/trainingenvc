// SandboxTestAgent.cpp	: implementation of the CSandboxTestAgent class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SandboxTestAgent.h"
#include "../../../supplements/agents/AgentLib.h"

#include "../../../tools/Random.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
// class CSandboxTestAgent - агент, которому не нужно учиться
//							обладает априорным знанием об окружении
//////////////////////////////////////////////////////////////////////

CSandboxTestAgent::CSandboxTestAgent()
{
	myDecisionIsSent=false;
}

void CSandboxTestAgent::AddActionKey(TKey _key)
{
	myActionKeys.push_back(_key);
}

void CSandboxTestAgent::TuitionKey(TKey _key)
{
	assert(myDecisionIsSent);
	assert(myDecisionList.size()>0);
	assert(myRelation.find(myDecisionList.front())==myRelation.end() || myRelation[myDecisionList.front()]==_key);

	myRelation[myDecisionList.front()]=_key;
	myDecisionList.pop_front();
	myDecisionIsSent=false;
}

int CSandboxTestAgent::Iterate()
{
	assert(!myDecisionIsSent);
	assert(myDecisionList.empty());

	assert(myActionKeys.size()>0);
	for( ; CRandom::GetBool(0.75); )
		myDecisionList.push_back(*(myActionKeys.random()));
		
	return myDecisionList.size();			// число ключей, которые нужно передать вызовом ReadOutput()
}

int CSandboxTestAgent::ReadOutput()
{
	assert(!myDecisionIsSent);
	myDecisionIsSent=true;
	return myDecisionList.front();
}
