#pragma once

#include "CacheFwd.h"
#include <boost/noncopyable.hpp>
#include <boost/unordered_map.hpp>

#include <string>

namespace RL
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
			SPACacheHandle GetCache(const CacheConfig& oCache, bool bAutoRegisterForCacheAdminEvents = true);

		};
	}
}