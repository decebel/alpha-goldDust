#ifndef CACHECONNECTIONMANAGER_DF_H
#define CACHECONNECTIONMANAGER_DF_H

#include "CacheFwd.h"
#include <boost/noncopyable.hpp>
#include <boost/unordered_map.hpp>

#include <string>
using namespace std;

namespace DF
{
	namespace Cache
	{

		class CacheConnectionManager : boost::noncopyable
		{
		private:
			CacheConnectionManager();

			typedef boost::unordered_map<std::string, SPACacheHandle> GCacheHandleContainer;
			typedef GCacheHandleContainer::iterator GCacheHandlesIter;
			GCacheHandleContainer _mapGCacheHandle;
			void RegisterCacheAdminEventDefault(const SPACacheHandle& spCacheSession);

		public:
			static CacheConnectionManager& Instance();
			SPACacheHandle SetupCacheConnection(const CacheConfig& oCache, bool bAutoRegisterForCacheAdminEvents = true);
			SPACacheHandle GetCache(const string& sCacheName);
		};
	}
}

#endif