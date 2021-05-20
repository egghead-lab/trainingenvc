// SandboxTestAgent.h	: interface for the CSandboxTestAgent class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#if !defined(SandboxTESTAGENT_H)
#define SandboxTEST_H

#include "../../../env/Key.h"
#include "../../../supplements/agents/shared/AgentPrototype.h"

#include "../../../tools/Superset.h"
#include <map>
#include <list>

//////////////////////////////////////////////////////////////////////
// class CSandboxTestAgent - агент, которому не нужно учиться
//							обладает априорным знанием об окружении
//////////////////////////////////////////////////////////////////////

class CSandboxTestAgent:public CAgentPrototype
{
	superset<TKey> myActionKeys;						// ключи возможных действий	(решений)
	std::map<TKey, TKey> myRelation;					// пара действие - полученный отклик
	std::list<TKey> myDecisionList;						// список действий

	bool myDecisionIsSent;

public:
	CSandboxTestAgent();
	void SetExploitationWeight(double)	{	}
	void SetPayoffType(TKey, TPayoffType, double)	{	}
	void Payoff(TKey, double)	{	}

	void AddActionKey(TKey _key);
	void TuitionKey(TKey);
	int Iterate();
	int ReadOutput();

	void Erase()	{	}
};

#endif // !defined(SandboxTESTAGENT_H)
