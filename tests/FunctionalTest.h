// FunctionalTest.h: interface for the CFunctionalTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(FUNCTIONALTEST_H)
#define FUNCTIONALTEST_H

//////////////////////////////////////////////////////////////////////
// class CFunctionalTest
//////////////////////////////////////////////////////////////////////

class CFunctionalTest  
{
	static unsigned int myComplete, myUserTerminated, myFail, myTotal;

public:
	static void Init();
	static void FinalizeTest(bool);
	static void Skip();
	static void Report();

	virtual void Run(bool);
};

#endif // !defined(FUNCTIONALTEST_H)
