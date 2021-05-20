// Sandbox.h: interface for the CSandbox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(SANDBOX_H)
#define SANDBOX_H

#include "../../../env/Bot.h"
#include "../../../tools/InitInt.h"

#include <map>

//////////////////////////////////////////////////////////////////////
// class CSandbox
//////////////////////////////////////////////////////////////////////

class CSandbox:public CBot
{
	BOTINITIALIZER(CSandbox);

	unsigned int myNumeration;

	std::map<unsigned int, unsigned int> myRelation;

	bool myEcho;

	void Init();

public:
	CSandbox();
	CSandbox(const unsigned int _numeration);

	void SetEcho(bool _echo)	{	myEcho=_echo;	}

	unsigned int GetThreshold()	{	assert(false);	return 0; }
	CBot* SetExamTask()	{	assert(false);	return NULL;	}
	bool GetSuccess()	{	assert(false);	return false;	}
	bool ContinueTask()	{	return false;	}
	void Update()	{	}
	void SetTask()	{	}
	void Vary()	{	}

	void Update(int);
};

#endif // !defined(SANDBOX_H)
