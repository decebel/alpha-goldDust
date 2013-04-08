#ifndef DF_YODA_H
#define DF_YODA_H

#include "DFFrameWork.h"
#include "Apprentice.h"
#include "ClientFwd.h"
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>

using namespace std;

namespace DF
{
	namespace Client
	{

		class DATAFLOW_API_EXPORTS MarketStats
		{
		private:
			string _sCurrentStatus; /* Connected/Disconnected */
			
			/* other stats about the data */
			/* number of samples */
			/* min/max */
			/* time series related data */
			/* other dataIO metrics - how much transferred, data rate etc*/
		
		};

		class DATAFLOW_API_EXPORTS Yoda //: boost::noncopyable
		{

		private:
			bool Initialize();
			//Yoda(); 
		public:
			Yoda();
			int test() { return 0; }
			static Yoda& GetYoda();			
			SPJedi GetJedi(const Apprentice& oApprentice = Apprentice("me"));
			vector<string> Markets();
			MarketStats GetMarketStats(const string& sMarket);

		};
		
	}

}



#endif