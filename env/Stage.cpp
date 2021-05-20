// Stage.cpp	: implementation of the CStage class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Stage.h"
#include "../supplements/agents/AgentLib.h"
#include "Bot.h"

#include "../tools/Random.h"
#include <assert.h>

//////////////////////////////////////////////////////////////////////
// class CStage
//////////////////////////////////////////////////////////////////////

CStage::CStage()
{
	myStep=0; 
	myThreshold=0;
	myTuitor=NULL;
	myStatus=READY;
}

void CStage::AddBot(CBot* _bot)
{
	assert(_bot);
	myBots.push_back(_bot);
}

void CStage::SetTuitor(CBot* _bot)
{
	assert(_bot);
	myBots.push_back(_bot);
	myTuitor=_bot;
	myThreshold=myTuitor->GetThreshold();
}

bool CStage::Run()
{
	CBot* taskBot=NULL;
	CBot* examBot=NULL;
	myStatus=RUN;

	for( ; myStep<myThreshold; ++myStep)
	{
		if(examBot!=NULL && examBot->ContinueTask())
			examBot->SetExamTask();
		else if (taskBot!=NULL && taskBot->ContinueTask())
			taskBot->SetTask();
		else
		{
			taskBot=NULL;
			if(myTuitor)
				examBot=myTuitor->SetExamTask();

			if(examBot==NULL)
			{
				taskBot=*(myBots.random());
				taskBot->SetTask();
			}
		}

		int keyNum=Iterate();
		assert(keyNum>=0);

		if(keyNum>0)
			for(int i=0; i<keyNum; ++i)
			{
				int key=ReadOutput();
				for(std::vector<CBot*>::iterator it=myBots.begin(); it!=myBots.end(); ++it)
					(*it)->Update(key);
			}
		else
			for(std::vector<CBot*>::iterator it=myBots.begin(); it!=myBots.end(); ++it)
				(*it)->Update();

		if(examBot && examBot->GetSuccess())
		{
			myStatus=COMPLETE;
			return true;
		}
	}

	assert(myStep==myThreshold);
	myStatus=FAIL;
	return false;
}

bool CStage::Run(unsigned int _threshold)
{
	myThreshold=_threshold;
	return Run();
}