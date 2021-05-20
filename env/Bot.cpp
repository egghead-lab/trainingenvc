// Bot.cpp		: implementation of the CBot class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Bot.h"
#include "TrainProgram.h"
#include "Stage.h"

//////////////////////////////////////////////////////////////////////
// class CBot
//////////////////////////////////////////////////////////////////////

std::set<CBot*> CBot::myBotsToDelete;

void CBot::AddBot(CBot* _bot)
{
	CStage* stage=CTrainProgram::GetStage();
	if(stage)
	{
		assert(_bot);
		myBotsToDelete.insert(_bot);
		_bot->Vary();
		stage->AddBot(_bot);
	}
}

void CBot::AddTuitor(CBot* _bot)
{
	CStage* stage=CTrainProgram::GetStage();
	if(stage)
	{
		assert(_bot);
		myBotsToDelete.insert(_bot);
		_bot->Vary();
		stage->SetTuitor(_bot);
	}
}

void CBot::Clear()
{
	for(std::set<CBot*>::iterator it=myBotsToDelete.begin(); it!=myBotsToDelete.end(); ++it)
	{
		(*it)->ClearObjects();
		delete (*it);
	}
	myBotsToDelete.clear();
}