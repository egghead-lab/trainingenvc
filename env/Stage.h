// Stage.h		: interface for the CStage class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#if !defined(STAGE_H)
#define STAGE_H

#include "FTypes.h"
#include "../tools/Superset.h"

//////////////////////////////////////////////////////////////////////
// class CStage
//////////////////////////////////////////////////////////////////////

class CStage  
{
public:
	typedef enum
	{
		READY,
		RUN,
		COMPLETE,
		FAIL
	} TStatus;

private:
	unsigned int myThreshold;
	unsigned int myStep;
	TStatus myStatus;

	CBot* myTuitor;
	superset<CBot*> myBots;

public:
	CStage();

	unsigned int GetStep()	{	return myStep;	}
	TStatus GetStatus()	{	return myStatus;	}
	void SetThreshold(unsigned int _threshold)	{	myThreshold=_threshold;	}

	void AddBot(CBot*);
	void SetTuitor(CBot*);
	bool Run();
	bool Run(unsigned int);
	virtual ~CStage()	{	}
};

#endif // !defined(STAGE_H)
