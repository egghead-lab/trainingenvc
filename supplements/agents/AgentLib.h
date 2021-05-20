// AgentLib.h	: global functions to connect to combinatorial agent
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#if !defined(AGENTLIB_H)
#define AGENTLIB_H

#include "shared/AgentPrototype.h"

#include <windows.h>

typedef void (__stdcall* DOUBLE2VOID)(double);
typedef void (__stdcall* INTINTDOUBLE2VOID)(int, int, double);
typedef void (__stdcall* INTDOUBLE2VOID)(int, double);
typedef void (__stdcall* INT2VOID)(int);
typedef int (__stdcall* VOID2INT)();
typedef void (__stdcall* VOID2VOID)();

extern DOUBLE2VOID SetExploitationWeight;
extern INTINTDOUBLE2VOID SetPayoffType;
extern INTDOUBLE2VOID Payoff;
extern INT2VOID AddActionKey;
extern INT2VOID TuitionKey;
extern VOID2INT Iterate;
extern VOID2INT ReadOutput;
extern VOID2VOID EraseAgent;

bool LoadAgent(const char*);				// Loads agent from DLL
void SetAgent(CAgentPrototype*);			// Sets the agent
void ReleaseAgent();

#endif	// #if !defined(AGENTLIB_H)