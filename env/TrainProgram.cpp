// TrainProgram.cpp	: implementation of the CTrainProgram class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrainProgram.h"

//////////////////////////////////////////////////////////////////////
// class CTrainProgram
//////////////////////////////////////////////////////////////////////

CStage* CTrainProgram::myStage;
CStage::TStatus CTrainProgram::myStatus;
CStage::TStatus CTrainProgram::myStageStatus;
unsigned int CTrainProgram::myStageSteps;
unsigned int CTrainProgram::myStepsNumber;

void CTrainProgram::Reset()	
{	
	myStage=NULL;	
	myStatus=CStage::READY;
	myStageStatus=CStage::READY;
	myStageSteps=0;
	myStepsNumber=0;
}

void CTrainProgram::SetNextStage()	
{
	if(myStatus!=CStage::FAIL)
	{
		RunStage();
		myStageSteps=0;
		myStageStatus=CStage::READY;
		assert(myStage==NULL);
		myStage=new CStage;
	}
}

void CTrainProgram::RunStage()
{
	if(myStage)
	{
		assert(myStage->GetStatus()==CStage::READY);
		assert(myStatus!=CStage::FAIL);

		myStatus=CStage::RUN;
		myStage->Run();

		assert(myStage->GetStatus()!=CStage::READY && myStage->GetStatus()!=CStage::RUN);
		myStageSteps=myStage->GetStep();
		myStepsNumber+=myStageSteps;
		myStageStatus=myStage->GetStatus();
		delete myStage;
		myStage=NULL;
	}
}

CStage::TStatus CTrainProgram::GetStageStatus()
{	
	RunStage(); 
	return myStageStatus;	
}

unsigned int CTrainProgram::GetStageSteps()	
{	
	RunStage(); 
	return myStageSteps;	
}

void CTrainProgram::Check()	
{	
	RunStage();

	if(myStatus!=CStage::FAIL)
		myStatus=myStageStatus;
	assert(myStatus!=CStage::RUN);
}

bool CTrainProgram::GetResult()
{
	return myStatus==CStage::COMPLETE;
}
