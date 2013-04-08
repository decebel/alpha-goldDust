#ifndef DF_CLIENTFWD_H
#define DF_CLIENTFWD_H

#include <boost/shared_ptr.hpp>
//using namespace boost;

namespace DF
{
	namespace Client
	{
		class Jedi;
		typedef boost::shared_ptr<Jedi> SPJedi;

		class MarketData;
		typedef boost::shared_ptr<MarketData> SPMarketData;

		class MarketDataInfo;
		typedef boost::shared_ptr<MarketDataInfo> SPMarketDataInfo;

		class JediApprenticeIO;
		typedef boost::shared_ptr<JediApprenticeIO> SPJediApprenticeIO;

	}
}
#endif