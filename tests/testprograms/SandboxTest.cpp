// SandboxTest.cpp	: implementation of the CSandboxTest class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SandboxTest.h"
#include "../../env/TrainInclude.h"
#include "../bots/ReinforcingBot/ReinforcingBot.h"
#include "../bots/Sandbox/SandboxTestAgent.h"
#include "../bots/Sandbox/Sandbox.h"

#include <iostream>

//////////////////////////////////////////////////////////////////////
// class CSandboxTest
//////////////////////////////////////////////////////////////////////

CSandboxTest::CSandboxTest():CFunctionalTest()
{

}

void CSandboxTest::Run(bool _echo)
{
	std::cout << " Use of sandbox in combination with a reinforcing bot, separator is used";
	if(_echo)
		std::cout << std::endl;
	bool result=true;

	CSandboxTestAgent* agent=new CSandboxTestAgent();
	SetAgent(agent);

	PROGRAM
	for(unsigned int i=0; i<8; ++i)
	{
		CLEAR;
		STAGE
			BOT(CSandbox);
//			TUITOR(CReinforcingBot);
			THRESHOLD(25000);

		result=result && STAGE_RESULT;
		if(_echo)
			std::cout << "  " << i << ": " << (STAGE_RESULT ? "OK in " : "FAIL in ") << STAGE_STEPS << " steps\n";
	}
	END_PROGRAM;

	FinalizeTest(result);
}
