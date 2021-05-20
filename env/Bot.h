// Bot.h		: interface for the CBot class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#if !defined(BOT_H)
#define BOT_H

#include "FTypes.h"
#include <vector>
#include <set>

#define BOTINITIALIZER(cls) static std::vector<cls*> myObjects;	\
public:															\
	static cls* GetLastObject()	{								\
		if(myObjects.size()==0)									\
			myObjects.push_back(new cls);						\
		return myObjects.back();	}							\
	static cls* MakeNewObject()	{								\
		myObjects.push_back(new cls);							\
		return myObjects.back();	}							\
	static void AddAsBot();										\
	static void AddAsTuitor();									\
	static void AddAsNewBot();									\
	static void AddAsNewTuitor();								\
	static cls* GetBot()	{	return myObjects.empty() ? NULL : myObjects.back();	}	\
	void ClearObjects()	{	myObjects.clear();	}

#define OBJECTCOUNTER(cls) std::vector<cls*> cls::myObjects;	\
void cls::AddAsBot()	{										\
	CBot* bot=GetLastObject();									\
	AddBot(bot);	}											\
void cls::AddAsTuitor()	{										\
	CBot* bot=GetLastObject();									\
	AddTuitor(bot);	}											\
void cls::AddAsNewBot()	{										\
	CBot* bot=MakeNewObject();									\
	AddBot(bot);	}											\
void cls::AddAsNewTuitor()	{									\
	CBot* bot=MakeNewObject();									\
	AddTuitor(bot);	}

#define TUITOR(cls) cls::AddAsTuitor()
#define BOT(cls) cls::AddAsBot()
#define NEW_TUITOR(cls) cls::AddAsNewTuitor()
#define NEW_BOT(cls) cls::AddAsNewBot()

//////////////////////////////////////////////////////////////////////
// class CBot
//////////////////////////////////////////////////////////////////////

class CBot  
{
	static std::set<CBot*> myBotsToDelete;

public:
	virtual CBot* SetExamTask() = 0;			// setting examination task
	virtual void SetTask() = 0;					// setting regular task
	virtual void Update(int) = 0;				// updating by agent's response
	virtual void Update() = 0;					// updating in case of no response from the agent
	virtual bool ContinueTask() = 0;			// bot may need more than one step to complete the task for the agent
	virtual bool GetSuccess() = 0;				// if the exam is passed
	virtual unsigned int GetThreshold()	= 0;	// if the bot is a tuitor, it has to set the threshold
	virtual void Vary()	= 0;					// makes variations to the behavior

	virtual void ClearObjects() = 0;			// to clear static std::vector<cls*> myObjects

	static void AddBot(CBot*);
	static void AddTuitor(CBot*);
	static void Clear();
};

#endif // !defined(BOT_H)
