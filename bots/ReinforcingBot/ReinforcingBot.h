// ReinforcingBot.h	: interface for the CReinforcingBot class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#if !defined(REINFORCINGBOT_H)
#define REINFORCINGBOT_H

#include "../../../env/Bot.h"
#include "../../../tools/InitInt.h"

#include <vector>

typedef const char* TDescription; 

//////////////////////////////////////////////////////////////////////
// class CBasicReinforcingBot
//////////////////////////////////////////////////////////////////////

class CBasicReinforcingBot:public CBot
{
	int myPayoffModel;
	unsigned int myNumeration;

	std::vector<unsigned int> myActiveDigitKeys;
	std::vector<unsigned int> myPassiveDigitKeys;
	unsigned int myPayoffKey;

	std::vector<unsigned int> myExamTasks;		// задачи на экзамен, каждого символа по три раза

	int myChoice;
	unsigned int myCycle;						// шаг внутри цикла от одного экзамена до другого
	unsigned int myPeriod;						// общее число шагов, используется для вычисления среднего количества выплат
	unsigned int myPayoffSum;					// сумма выплат, используется для вычисления среднего

	double myPayoffValue;
	double myPayoffWeight;
	double myExploitationWeight;

	bool myEcho;

	void Init();
	void Round();

public:
	CBasicReinforcingBot();
	CBasicReinforcingBot(const unsigned int _numeration, int _task);

	double GetPayoffValue()	{	return myPayoffValue;	}
	double GetPayoffWeight()	{	return myPayoffWeight;	}
	double GetExploitationWeight()	{	return myExploitationWeight;	}
	void SetEcho(bool _echo)	{	myEcho=_echo;	}

	void Vary()	{	myPayoffModel=++myPayoffModel%8; Init();	}
	unsigned int GetThreshold()	{	return 25000;	}
	int GetPayoffModel()	{	return myPayoffModel;	}

	virtual void SetTask();
	CBot* SetExamTask();
	void Update(int);
	void Update();
	bool ContinueTask();
	bool GetSuccess();
};

//////////////////////////////////////////////////////////////////////
// class CReinforcingBot
//////////////////////////////////////////////////////////////////////

class CReinforcingBot:public CBasicReinforcingBot
{
	BOTINITIALIZER(CReinforcingBot);

	unsigned int mySeparator;

public:
	static TDescription GetDescription();

	CReinforcingBot();
	CReinforcingBot(const unsigned int _numeration, int _task);

	void SetTask();
};

//////////////////////////////////////////////////////////////////////
// class CNoSeparatorReinforcingBot
//////////////////////////////////////////////////////////////////////

class CNoSeparatorReinforcingBot:public CBasicReinforcingBot
{
	BOTINITIALIZER(CNoSeparatorReinforcingBot);

public:
	static TDescription GetDescription();

	CNoSeparatorReinforcingBot();
	CNoSeparatorReinforcingBot(const unsigned int _numeration, int _task);
};

#endif // !defined(REINFORCINGBOT_H)
