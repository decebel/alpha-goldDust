#ifndef JediCouncil_RL_H
#define JediCouncil_RL_H

#include "ClientFwd.h"
#include <string>
#include <vector>
#include <boost/unordered_map.hpp>
using namespace boost;
using namespace std;

namespace DF
{
	namespace Client
	{
		class Apprentice;
		class JediCode;

		namespace Internal
		{
			class JediCouncil
			{
				typedef unordered_map<string, SPJedi> CacheType;
				CacheType _Cache;				
				SPJedi CreateJedi(const string& sJediName, const Apprentice& oJediCode);
				vector<string> JediPowers(const JediCode& oJediCode);
			public:
				static JediCouncil& GetJediCouncil();				
				SPJedi GetJedi(const Apprentice& oApprentice);
				vector<string> GetJediNames();
			};
		}

	}
}


#endif