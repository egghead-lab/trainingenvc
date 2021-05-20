// PayoffTest.h	: interface for the CPayoffTest struct.
//
// Authors		: (a)pavelmalyshkin
// License		: ELEPHANT
//
//////////////////////////////////////////////////////////////////////

#if !defined(PAYOFFTEST_H)
#define PAYOFFTEST_H

#include "../bots/ReinforcingBot/PayoffTestAgent.h"
#include "../FunctionalTest.h"
#include "../../env/TrainInclude.h"

#include <vector>
#include <iostream>

//////////////////////////////////////////////////////////////////////
// struct CPayoffTest - тест на подкрепления, 8 кругов с боевым
// агентом. Каждый круг соответствует варианту подкрепления.
//////////////////////////////////////////////////////////////////////

template <typename T> struct CPayoffTest: public CFunctionalTest  
{
	void PrintTask(bool _echo)
	{
		if(_echo)
		{
			T* bot=T::GetBot();
			assert(bot);

			int payoffModel=bot->GetPayoffModel();
			std::cout << "  Model " << payoffModel+1;

			if(bot->GetExploitationWeight()>0)
				std::cout << ": targeted agent, ";
			else
				std::cout << ": avoiding agent, ";

			if(bot->GetPayoffWeight()>0)
				std::cout << "weight +, ";
			else
				std::cout << "weight -, ";

			if(bot->GetPayoffValue()>0)
				std::cout << "payoffs +";
			else
				std::cout << "payoffs -";
		}
	};

public:
	void Run(bool _echo)
	{
		_echo=true;
		std::cout << " Use of different positive payoff models, ";
		std::cout << T::GetDescription();
		if(_echo)
			std::cout << std::endl;
		bool result=true;

		CPayoffTestAgent* agent=new CPayoffTestAgent();
		SetAgent(agent);

		PROGRAM
		DO(8)
		{
			CLEAR;
			STAGE
				TUITOR(T);
				PrintTask(_echo);
//				T::GetBot()->SetEcho(true);

			if(!STAGE_RESULT)
			{
				result=false;
				break;
			}

			if(_echo)
				std::cout << "  passed at " << STAGE_STEPS << " steps\n";
		}

		END_PROGRAM;
		delete agent;

		FinalizeTest(result);
	}
};

#endif // !defined(PAYOFFTEST_H)
