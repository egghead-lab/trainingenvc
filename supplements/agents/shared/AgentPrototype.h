// AgentPrototype.h : interface for the CAgent class.
//
// Authors		 : (a)pavelmalyshkin
// License		 : ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#ifndef AGENTPROTOTYPE_H
#define AGENTPROTOTYPE_H

#include <exception>

//////////////////////////////////////////////////////////////////////
// class CAgentPrototype
//////////////////////////////////////////////////////////////////////

#define TKey int

typedef enum				// payoff type
{
	DIFFERENTIAL = 0,		// reinforcement based on payoff moments only
	PROPORTIONAL = 1,		// reinforcement at the moments of payoffs
	INTEGRAL = 2			// reinforcement is a total accumulated payoffs over a period; periodic updated are required 	
} TPayoffType;

class CAgentPrototype
{
public:
	virtual void SetExploitationWeight(double) = 0;					// Exploration/Exploitation coefficient
	virtual void SetPayoffType(TKey, TPayoffType, double) = 0;		// Sets parameters for an key; default: DIFFERENTIAL, 0.0, true
	virtual void AddActionKey(TKey) = 0;							// Adding action key to alphabet
	virtual void Payoff(TKey, double) = 0;							// Payoff event relating to key (INTEGRAL or PROPORTIONAL)
	virtual void TuitionKey(TKey) = 0;								// Event by its key
	virtual TKey Iterate() = 0;										// Main agent cycle
	virtual int ReadOutput() = 0;									// Key from the agent's output sequence
	virtual void Erase() = 0;
};

#endif // !defined AGENTPROTOTYPE_H
