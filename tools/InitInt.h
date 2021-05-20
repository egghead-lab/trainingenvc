// InitInt.h	: interface for the CInitInt class.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#if !defined(INITINT_H)
#define INITINT_H

//////////////////////////////////////////////////////////////////////
// class CInitInt
//////////////////////////////////////////////////////////////////////

class CInitInt  
{
	unsigned int myInt;

public:
	CInitInt() { myInt=0; }

	unsigned int operator ++ (int) { return myInt++; }
	unsigned int operator ++ ()	{ return ++myInt; }
	unsigned int operator -- (int) { return myInt--; }
	unsigned int operator -- () { return --myInt; }
	unsigned int operator + (unsigned int a) { return myInt+a; }
	unsigned int operator - (unsigned int a) { return myInt-a; }
	bool operator == (unsigned int a) { return myInt==a; }
	CInitInt& operator = (unsigned int a) { myInt=a; return *this; }
	int Get()	{	return myInt;	}

	virtual ~CInitInt()	{	}
};

#endif // !defined(INITINT_H)
