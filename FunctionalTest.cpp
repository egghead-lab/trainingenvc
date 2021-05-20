// FunctionalTest.cpp	: implementation of the CFunctionalTest class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FunctionalTest.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
// class CFunctionalTest
//////////////////////////////////////////////////////////////////////

unsigned int CFunctionalTest::myComplete;
unsigned int CFunctionalTest::myUserTerminated; 
unsigned int CFunctionalTest::myFail; 
unsigned int CFunctionalTest::myTotal;

void CFunctionalTest::Init()
{
	std::cout << "Functional testing\n";
	myComplete=0;
	myUserTerminated=0;
	myFail=0;
	myTotal=0;
}

void CFunctionalTest::Skip()
{
	++myUserTerminated;
	++myTotal;
}

void CFunctionalTest::FinalizeTest(bool _result)
{
	if(_result)
	{
		std::cout << " COMPLETE\n";
		++myComplete;
	}
	else
	{
		std::cout << " FAIL\n";
		++myFail;
	}

	++myTotal;
}

void CFunctionalTest::Report()
{
	std::cout << "Functional testing done\n";
	if(myTotal>0)
	{
		if(myComplete>0)
			std::cout << myComplete << " COMPLETE | ";
		if(myUserTerminated>0)
			std::cout << myUserTerminated << " TERMINATED | ";
		if(myFail>0)
			std::cout << myFail << " FAILED | ";
		std::cout << myTotal << " TOTAL\n\n";
	}
}

void CFunctionalTest::Run(bool _echo)
{
	std::cout << " Blank test";
	if(_echo)
		std::cout << std::endl;
	FinalizeTest(true);
}
