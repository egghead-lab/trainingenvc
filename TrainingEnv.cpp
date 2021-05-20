// TrainingEnv.cpp	: Defines the entry point for the console application.
// Author			: Pavel Malyshkin, Egghead OU
// License			: GNU GPL v3.0
//

#include "stdafx.h"
#include "FunctionalTest.h"
#include "tests/bots/ReinforcingBot/ReinforcingBot.h"
#include "tests/testprograms/SandboxTest.h"
#include "tests/testprograms/PayoffTest.h" 

#define FUNCTIONALTEST(a)	\
	test=new a();			\
	test->Run(echo);		\
	delete test		

int main(int argc, char* argv[])
{
	bool echo=false;
	CFunctionalTest* test=NULL;
	
	FUNCTIONALTEST(CPayoffTest<CNoSeparatorReinforcingBot>);
	FUNCTIONALTEST(CPayoffTest<CReinforcingBot>);
	FUNCTIONALTEST(CSandboxTest);

	CFunctionalTest::Report();

	return 0;
}
