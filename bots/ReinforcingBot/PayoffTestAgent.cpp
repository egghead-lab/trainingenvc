// PayoffTestAgent.cpp	: implementation of the CPayoffTestAgent class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PayoffTestAgent.h"
#include "../../../supplements/agents/AgentLib.h"

#include "../../../tools/Random.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
// class CPayoffTestAgent - агент, которому не нужно учиться
//							обладает априорным знанием об окружении
//////////////////////////////////////////////////////////////////////

CPayoffTestAgent::CPayoffTestAgent()
{
	myLastDecision=std::make_pair(-1, -1);
	myReinforcement=false;
	myNegativePayoffs=false;
	myDecisionIsSent=true;
	myResponseIsReceived=false;
	mySeparator=-1;
}

void CPayoffTestAgent::SetExploitationWeight(double _weight)	
{	
	myExploitationWeight=_weight;
}

void CPayoffTestAgent::SetPayoffType(TKey _key, TPayoffType _type, double _weight)
{
	myPayoffKey=_key;
	myPayoffType=_type;
	myWeight=_weight;
}

void CPayoffTestAgent::AddActionKey(TKey _key)
{
	myActionKeys.push_back(_key);
}

void CPayoffTestAgent::Payoff(TKey _key, double _value)
{
	assert(myPayoffKey==_key);
	if(myLastDecision.first>=0)
	{
		if(myWeight*myExploitationWeight*_value>=0)
		{
			assert(myRelation.find(myLastDecision.first)==myRelation.end() || myRelation[myLastDecision.first]==myLastDecision.second);
			myRelation[myLastDecision.first]=myLastDecision.second;
		}
		else
		{
			myNegativePayoffs=true;
			myReinforcement=false;
		}
	}
}

void CPayoffTestAgent::TuitionKey(TKey _key)
{
	if(!myResponseIsReceived)
	{
		if(myReinforcement)
		{
			assert(myLastDecision.first>=0);
			assert(myRelation.find(myLastDecision.first)==myRelation.end() || myRelation[myLastDecision.first]==myLastDecision.second);
			myRelation[myLastDecision.first]=myLastDecision.second;
		}
		myLastDecision.first=_key;
		if(myNegativePayoffs)
			myReinforcement=true;

		myResponseIsReceived=true;
	}
	else
	{
		assert(mySeparator==_key || mySeparator==-1);
		mySeparator=_key;
	}
}

int CPayoffTestAgent::Iterate()
{
	std::map<TKey, TKey>::iterator it=myRelation.find(myLastDecision.first);
	if(it==myRelation.end())
		myLastDecision.second=myActionKeys[CRandom::GetInt(0, myActionKeys.size())];
	else
		myLastDecision.second=it->second;

	myDecisionIsSent=false;
	return 1;
}

int CPayoffTestAgent::ReadOutput()
{
	assert(!myDecisionIsSent);
	myDecisionIsSent=true;
	myResponseIsReceived=false;
	return myLastDecision.second;
}

//////////////////////////////////////////////////////////////////////
// class CPayoffNoSeparatorTestAgent - агент, которому не нужно учиться
//							обладает априорным знанием об окружении
//////////////////////////////////////////////////////////////////////

CPayoffNoSeparatorTestAgent::CPayoffNoSeparatorTestAgent()
{
	myLastDecision=std::make_pair(-1, -1);
	myReinforcement=false;
	myNegativePayoffs=false;
	myDecisionIsSent=true;
}

void CPayoffNoSeparatorTestAgent::TuitionKey(TKey _key)
{
	if(myReinforcement)
	{
		assert(myLastDecision.first>=0);
		assert(myRelation.find(myLastDecision.first)==myRelation.end() || myRelation[myLastDecision.first]==myLastDecision.second);
		myRelation[myLastDecision.first]=myLastDecision.second;
	}
	myLastDecision.first=_key;
	if(myNegativePayoffs)
		myReinforcement=true;
}

int CPayoffNoSeparatorTestAgent::ReadOutput()
{
	assert(myDecisionIsSent==false);
	myDecisionIsSent=true;
	return myLastDecision.second;
}
