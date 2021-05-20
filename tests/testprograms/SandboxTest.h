// SandboxTest.h: interface for the CSandboxTest struct.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#if !defined(SANDBOXTEST_H)
#define SANDBOXTEST_H

#include "../FunctionalTest.h"

#include <vector>

//////////////////////////////////////////////////////////////////////
// struct CSandboxTest - тест бота, который откликается символом на символ
//////////////////////////////////////////////////////////////////////

struct CSandboxTest: public CFunctionalTest  
{
public:
	CSandboxTest();
	void Run(bool);
};

#endif // !defined(SANDBOXTEST_H)
