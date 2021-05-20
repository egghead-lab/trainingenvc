// TrainProgram.h	: interface for the TrainProgram class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#if !defined(TRAINPROGRAM_H)
#define TRAINPROGRAM_H

#include "FTypes.h"
#include "Stage.h"

#include <vector>

#define CLEAR EraseAgent();
#define PROGRAM CKey::Init(); CBot::Clear(); EraseAgent(); CTrainProgram::Reset();
#define STAGE CTrainProgram::RunStage(); CTrainProgram::SetNextStage();
#define END_PROGRAM CTrainProgram::RunStage(); EraseAgent(); CKey::Clear(); CBot::Clear();
#define STAGE_RESULT (CTrainProgram::GetStageStatus()==CStage::COMPLETE)
#define STAGE_STEPS CTrainProgram::GetStageSteps()
#define STEPS CTrainProgram::GetStepsNumber()
#define THRESHOLD(steps) CTrainProgram::GetStage()->SetThreshold(steps);
#define DO(times) for(unsigned int i=0; i<times; ++i)
#define CHECK CTrainProgram::Check();

//////////////////////////////////////////////////////////////////////
// class CTrainProgram
//////////////////////////////////////////////////////////////////////

class CTrainProgram  
{
	static CStage* myStage;
	static CStage::TStatus myStatus;
	static CStage::TStatus myStageStatus;
	static unsigned int myStepsNumber;
	static unsigned int myStageSteps;

public:
	static unsigned int GetStepsNumber()	{	return myStepsNumber;	}
	static CStage* GetStage()	{	return myStage;	}

	static void Reset();
	static void SetNextStage();
	static CStage::TStatus GetStageStatus();
	static unsigned int GetStageSteps();
	static void RunStage();
	static void Complete();
	static bool GetResult();
	static void Check();
};

#endif // !defined(TRAINPROGRAM_H)
