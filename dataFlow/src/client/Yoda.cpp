#include "Yoda.h"
#include "Jedi.h"
#include "JediCouncil.h"
#include "CacheBootStrapper.h"

namespace DF
{
	namespace Client
	{
		string GetJediName(const string& sApprenticeName) 
		{ return "Jedi For " + sApprenticeName; }

		Yoda::Yoda()
		{
			Initialize();
		}

		Yoda& Yoda::GetYoda()
		{
			static Yoda instance;
			return instance;
		}

		bool Yoda::Initialize()
		{
			using DF::Client::Internal::CacheBootStrapper;
			if(CacheBootStrapper::GetBootStrapper().LoadCacheConfig(""))
				return CacheBootStrapper::GetBootStrapper().InitializeStartupObjects();	

			return false;
		}

		SPJedi Yoda::GetJedi(const Apprentice& oApprentice)
		{
			SPJedi spDummy;
			return spDummy;
			//using namespace DF::Client::Internal;
			//return JediCouncil::GetJediCouncil().GetJedi(oApprentice); //.Name(), GetJediName(oApprentice.Name())); //"Jedi For " + oApprentice.Name());			
		}

		vector<string> Yoda::Markets()
		{
			vector<string> ret;
			return ret;
		}

		MarketStats Yoda::GetMarketStats(const string& sMarket)
		{
			MarketStats s;
			return s;
		}

	}

}