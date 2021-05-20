// AgentLib.cpp: implementation of the AgentLib functions 
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AgentLib.h"
#include <assert.h>

//////////////////////////////////////////////////////////////////////
// agent connection library
//////////////////////////////////////////////////////////////////////

HINSTANCE DLLHandle;						// handle to DLL, optional
CAgentPrototype* agent;						// handle to agent, optional

DOUBLE2VOID SetExploitationWeight;
INTINTDOUBLE2VOID SetPayoffType;
INTDOUBLE2VOID Payoff; 
INT2VOID AddActionKey;
INT2VOID TuitionKey;
VOID2INT Iterate;
VOID2INT ReadOutput;
VOID2VOID EraseAgent;

struct CAgentInitializer
{
	CAgentInitializer();
	static void SetPointersToNull();
};

void CAgentInitializer::SetPointersToNull()
{
	SetExploitationWeight=NULL;
	SetPayoffType=NULL;
	Payoff=NULL;
	AddActionKey=NULL;
	TuitionKey=NULL;
	Iterate=NULL;
	ReadOutput=NULL;
	EraseAgent=NULL;
}

CAgentInitializer::CAgentInitializer()
{
	DLLHandle=NULL;
	agent=NULL;
	SetPointersToNull();
}

CAgentInitializer initializer;				// sets initial NULL to the agent and the DLL handle

void __stdcall A_SetExploitationWeight(double _k)
{
	assert(agent);
	agent->SetExploitationWeight(_k);
}

void __stdcall A_SetPayoffType(TKey _key, int _type, double _weight)
{
	assert(agent);
	agent->SetPayoffType(_key, TPayoffType(_type), _weight);
}

void __stdcall A_Payoff(TKey _key, double _payoff)
{
	assert(agent);
	agent->Payoff(_key, _payoff);
}

void __stdcall A_AddActionKey(TKey _key)
{
	assert(agent);
	agent->AddActionKey(_key);
}

void __stdcall A_TuitionKey(TKey _tag)
{
	assert(agent);
	agent->TuitionKey(_tag);
}

int __stdcall A_Iterate()
{
	assert(agent);
	return agent->Iterate();
}

int __stdcall A_ReadOutput()
{
	assert(agent);
	return agent->ReadOutput();
}

void __stdcall A_Erase()
{
	assert(agent);
	agent->Erase();
}

void LoadSymbols()
{
	assert(DLLHandle);

	SetExploitationWeight=(DOUBLE2VOID)GetProcAddress(DLLHandle, "GSetExploitationWeight");
	SetPayoffType=(INTINTDOUBLE2VOID)GetProcAddress(DLLHandle, "GSetPayoffType");
	Payoff=(INTDOUBLE2VOID)GetProcAddress(DLLHandle, "GPayoff");
    AddActionKey=(INT2VOID)GetProcAddress(DLLHandle, "GAddActionKey");
	TuitionKey=(INT2VOID)GetProcAddress(DLLHandle, "GTuitionKey");
	Iterate=(VOID2INT)GetProcAddress(DLLHandle, "GIterate");
	ReadOutput=(VOID2INT)GetProcAddress(DLLHandle, "GReadOutput");
	EraseAgent=(VOID2VOID)GetProcAddress(DLLHandle, "GErase");

	assert(SetExploitationWeight);
	assert(SetPayoffType);
	assert(Payoff);
	assert(AddActionKey);
	assert(TuitionKey);
	assert(Iterate);
	assert(ReadOutput);
	assert(EraseAgent);
}

void SetAgent(CAgentPrototype* _prototype)
{
	agent=_prototype;
	if(agent)
	{
		SetExploitationWeight=A_SetExploitationWeight;
		SetPayoffType=A_SetPayoffType;
		Payoff=A_Payoff;
		AddActionKey=A_AddActionKey;
		TuitionKey=A_TuitionKey;
		Iterate=A_Iterate;
		ReadOutput=A_ReadOutput;
		EraseAgent=A_Erase;
	}
	else if(DLLHandle)
		LoadSymbols();
	else
		CAgentInitializer::SetPointersToNull();
}

bool LoadAgent(const char* _lib)
{
	DLLHandle=LoadLibrary(_lib);
	if(GetLastError()==0)
    {
		assert(DLLHandle);
		LoadSymbols();
		return true;
    }

	return false;
}

void ReleaseAgent()
{
	if(DLLHandle)
	{
		FreeLibrary(DLLHandle);
		DLLHandle=NULL;
	}

	if(agent==NULL)
		CAgentInitializer::SetPointersToNull();
	else
		SetAgent(agent);
}