// ReinforcingBot.cpp: implementation of the CReinforcingBot class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReinforcingBot.h"
#include "../../../env/TrainProgram.h"
#include "../../../supplements/agents/AgentLib.h"
#include "../../../env/Key.h"

#include "../../../tools/Random.h"
#include "../../../tools/Num2Str.h"
#include "../../../tools/SetWidgets.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
// class CBasicReinforcingBot
//////////////////////////////////////////////////////////////////////

CBasicReinforcingBot::CBasicReinforcingBot()
{
	myNumeration=3;
	myPayoffModel=-1;
		
	Init();
}

CBasicReinforcingBot::CBasicReinforcingBot(const unsigned int _numeration, int _model)
{
	myNumeration=_numeration;
	myPayoffModel=_model;

	Init();
}

void CBasicReinforcingBot::Init()
{
	myCycle=0;
	myPeriod=1;
	myChoice=-1;
	myPayoffSum=0;

	for(int i=0; i<myNumeration; ++i)
	{
		myActiveDigitKeys.push_back(CKey::GetKey("Active digit for "+Num2String(i)));
		myPassiveDigitKeys.push_back(CKey::GetKey("Passive digit for "+Num2String(i)));
		AddActionKey(myActiveDigitKeys[i]);
	}

	myPayoffKey=CKey::GetKey("Payoff");
	myPayoffWeight=myPayoffModel<4?1.0:-1.0;
	SetPayoffType(myPayoffKey, INTEGRAL, myPayoffWeight);

	myExploitationWeight=myPayoffModel%4<2?1.0:-1.0;
	SetExploitationWeight(myExploitationWeight*0.8);

	myPayoffValue=myPayoffModel%2==0?1.0:-1.0;

	myEcho=false;
}

void CBasicReinforcingBot::SetTask()
{
	assert(myChoice==-1);
	if(myExamTasks.empty())
	{
		myChoice=CRandom::GetInt(0, myNumeration);
		TuitionKey(myPassiveDigitKeys[myChoice]);
	}
	else
	{
		unsigned int choice=CRandom::GetInt(0, myExamTasks.size());
		myChoice=myExamTasks[choice];
		TuitionKey(myPassiveDigitKeys[myChoice]);
		CSetWidgets<unsigned int>::Erase(myExamTasks, choice);
	}

	if(myEcho)
		std::cout << std::endl << "q: " << myActiveDigitKeys[myChoice] << " ";
}

CBot* CBasicReinforcingBot::SetExamTask()
{
	if(myCycle==90)
	{
		SetExploitationWeight(myExploitationWeight);	// подготовка к экзамену
		if(myEcho)
			std::cout << "- prep: ";
	}

	if(myCycle==100)
	{
		if(myEcho)
			std::cout << "- begin: ";
		for(unsigned int i=0; i<myNumeration; ++i)
			for(unsigned int j=0; j<3; j++)
				myExamTasks.push_back(i);

		SetTask();
		return this;
	}
	else if (myCycle>100)
	{
		SetTask();
		return this;
	}

	return NULL;
}

void CBasicReinforcingBot::Round()
{
	if(myCycle==0)
	{
		SetExploitationWeight(myExploitationWeight*0.8);
		if(myPeriod!=0 && myEcho)
			std::cout << "-end ";
	}
	myPeriod++;
	myCycle++;
}

void CBasicReinforcingBot::Update(int _key)
{
	if(myEcho)
		std::cout << "a: " << _key << " ";

	if(myChoice>=0)
	{
		if(!((myExploitationWeight*myPayoffValue*myPayoffWeight>=0) ^ (myActiveDigitKeys[myChoice]==_key)))
		{
			Payoff(myPayoffKey, myPayoffValue);
			++myPayoffSum;
			if(myEcho)
			{
				if(myExploitationWeight*myPayoffValue*myPayoffWeight>=0)
					std::cout << double(myPayoffSum)/myPeriod;
				else
					std::cout << 1.0-double(myPayoffSum)/myPeriod;
			}
		}

		if(myCycle>=100 && myActiveDigitKeys[myChoice]!=_key)
		{
			myExamTasks.clear();
			myCycle=0;		// конец экзамену
		}

		myChoice=-1;			// чтобы избежать повторной выплаты за одну задачу, есть assert()
	}

	Round();
}

void CBasicReinforcingBot::Update()
{
	if(myEcho)
		std::cout << "noa ";

	if(myCycle>=100)
	{
		myExamTasks.clear();
		myCycle=0;
	}
	myChoice=-1;				// для assert() в постановке задачи

	Round();
}

bool CBasicReinforcingBot::ContinueTask()
{
	if(myCycle>100)
		return true;

	return false;
}

bool CBasicReinforcingBot::GetSuccess()
{
	unsigned int size=myExamTasks.size();
	return myCycle>=100 && size==0;
}

//////////////////////////////////////////////////////////////////////
// class CReinforcingBot
//////////////////////////////////////////////////////////////////////

OBJECTCOUNTER(CReinforcingBot);
CReinforcingBot::CReinforcingBot():CBasicReinforcingBot()	
{	
	mySeparator=CKey::GetKey("Separator");
}

CReinforcingBot::CReinforcingBot(const unsigned int _numeration, int _task):CBasicReinforcingBot(_numeration, _task)	
{	
	mySeparator=CKey::GetKey("Separator");
}

void CReinforcingBot::SetTask()
{
	CBasicReinforcingBot::SetTask();
	TuitionKey(mySeparator);
}

TDescription CReinforcingBot::GetDescription()
{
	return "separator is used";
}

//////////////////////////////////////////////////////////////////////
// class CNoSeparatorReinforcingBot
//////////////////////////////////////////////////////////////////////

OBJECTCOUNTER(CNoSeparatorReinforcingBot);
CNoSeparatorReinforcingBot::CNoSeparatorReinforcingBot():CBasicReinforcingBot()	{	}

CNoSeparatorReinforcingBot::CNoSeparatorReinforcingBot(const unsigned int _numeration, int _task):CBasicReinforcingBot(_numeration, _task)	{	}

TDescription CNoSeparatorReinforcingBot::GetDescription()
{
	return "no separator is used";
}
