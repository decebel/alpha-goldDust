#pragma once

#include <boost\noncopyable.hpp>
#include <boost\unordered_map.hpp>
#include <string>
#include "CacheCommon.hpp"
#include "CacheFwd.h"
//#include "CacheTail.hpp"


namespace RL
{
	namespace Cache
	{
		typedef boost::unordered_map<std::string, SPCacheTail> CachedTails;
		typedef CachedTails::iterator CachedTailsIter;

		class CacheTailRegistrar : boost::noncopyable
		{

		private:
			
			CachedTails _CachedTails;
			OnCacheTailCreated _CacheTailCreatedSignal;
			SPCacheTail CreateCacheTail(const std::string& ns, const std::string& cacheName);

		public:
			
			static CacheTailRegistrar& Instance();

			/**
			*	Will create a new CacheTail if does not exist. 
			*   Otherwise will return cached CacheTail object
			*   @arg1: By convention "dbname.collectionname"
			*   @arg2: Cache name. Default to "local"
			**/

			SPCacheTail GetCacheTail(const std::string& ns, const std::string& cache = "local");		

			SignalConnection Connect(const CacheTailCreatedSubscriber& subscriber);

		};
	}
}