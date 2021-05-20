// Author			: Pavel Malyshkin, Egghead OU
// License			: GNU GPL v3.0
//

#if !defined(AFX_STDAFX_H)
#define AFX_STDAFX_H

#ifndef ECLIPSE							// MSVC 6.0
#pragma warning (disable : 4786)
#pragma warning (disable : 4172)
#pragma warning (disable : 4503)
#pragma warning (disable : 4996)
#pragma once
#define WIN32_LEAN_AND_MEAN				// Exclude rarely-used stuff from Windows headers
#include <windows.h>

#elif defined UNIX						// eclipse - unix
#include <unistd.h>

#else
#include <windows.h>					// eclipse - windows
#endif

#endif // !defined(AFX_STDAFX_H)
