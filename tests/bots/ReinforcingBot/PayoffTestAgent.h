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
// class CPayoffTestAgent - �����, �������� �� ����� �������
//							�������� ��������� ������� �� ���������
//////////////////////////////////////////////////////////////////////

class CPayoffTestAgent:public CAgentPrototype
{
	TKey mySeparator;

protected:
	superset<TKey> myActionKeys;					// ����� ��������� ��������	(�������)		
	std::map<TKey, TKey> myRelation;				// ���� ������ - �������
	std::pair<TKey, TKey> myLastDecision;			// ��������� ������ � �������� ��� ��� �������

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
// class CPayoffNoSeparatorTestAgent - �����, �������� �� ����� �������
//							�������� ��������� ������� �� ���������
//							����� ��, ��� ����������, �� �� ������������ �� ���������
//////////////////////////////////////////////////////////////////////

class CPayoffNoSeparatorTestAgent:public CPayoffTestAgent
{
public:
	CPayoffNoSeparatorTestAgent();
	void TuitionKey(TKey);
	int ReadOutput();
};

#endif // !defined(PAYOFFTESTAGENT_H)
