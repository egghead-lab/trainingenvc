// PayoffTestAgent.h: interface for the CPayoffTestAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(PAYOFFTESTAGENT_H)
#define PAYOFFTESTAGENT_H

#include "../../../env/Key.h"
#include "../../../supplements/agents/shared/AgentPrototype.h"

#include "../../../tools/Superset.h"
#include <vector>

//////////////////////////////////////////////////////////////////////
// class CPayoffTestAgent - агент, которому не нужно учиться
//							обладает априорным знанием об окружении
//////////////////////////////////////////////////////////////////////

class CPayoffTestAgent:public CAgentPrototype
{
	TKey mySeparator;

protected:
	superset<TKey> myActionKeys;					// ключи возможных действий	(решений)		
	std::map<TKey, TKey> myRelation;				// пара задача - решение
	std::pair<TKey, TKey> myLastDecision;			// последняя задача и принятое для нее решение

	double myExploitationWeight;

	TKey myPayoffKey;
	TPayoffType myPayoffType;
	double myWeight;

	bool myReinforcement;
	bool myNegativePayoffs;
	bool myDecisionIsSent;
	bool myResponseIsReceived;

public:
	CPayoffTestAgent();
	void SetExploitationWeight(double _weight);
	void SetPayoffType(TKey _key, TPayoffType _type, double _weight);
	void AddActionKey(TKey _key);
	void Payoff(TKey _key, double _value);
	virtual void TuitionKey(TKey);
	int Iterate();
	virtual int ReadOutput();

	void Erase()	{	}
};

//////////////////////////////////////////////////////////////////////
// class CPayoffNoSeparatorTestAgent - агент, которому не нужно учиться
//							обладает априорным знанием об окружении
//							такой же, как предыдущий, но не рассчитывает на сепаратор
//////////////////////////////////////////////////////////////////////

class CPayoffNoSeparatorTestAgent:public CPayoffTestAgent
{
public:
	CPayoffNoSeparatorTestAgent();
	void TuitionKey(TKey);
	int ReadOutput();
};

#endif // !defined(PAYOFFTESTAGENT_H)
