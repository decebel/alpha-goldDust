#include "RL/Cache/CacheTailRegistrar.hpp"
#include "RL/Cache/CacheTail.hpp"
#include "RL/Cache/CacheConnectionManager.hpp"

namespace RL
{
	namespace Cache
	{
		CacheTailRegistrar& CacheTailRegistrar::Instance()
		{
			static CacheTailRegistrar registrar;
			return registrar;
		}

		SPCacheTail CacheTailRegistrar::CreateCacheTail(const std::string& ns, const std::string& cacheName)
		{			
			//SPCacheHandle spCacheHandle =  CacheConnectionManager::Instance().Cache(cacheName);
			//SPCacheTail spCacheTail(new CacheTail(spCacheHandle, ns));
			SPCacheTail spCacheTail;
			return spCacheTail;
		}

		SPCacheTail CacheTailRegistrar::GetCacheTail(const std::string& ns, const std::string& cache)
		{
			std::string cacheKey = cache + ns;
			CachedTailsIter iter = _CachedTails.find(cacheKey);
			
			if(iter != _CachedTails.end())
				return _CachedTails[cacheKey];

			SPCacheTail spCacheTail = CreateCacheTail(ns, cache);
			_CachedTails[cacheKey] = spCacheTail;
			
			if(!_CacheTailCreatedSignal.empty())
				_CacheTailCreatedSignal(ns, cache);
			
			return spCacheTail;
		}

		SignalConnection CacheTailRegistrar::Connect(const CacheTailCreatedSubscriber& subscriber)
		{
			return _CacheTailCreatedSignal.connect(subscriber);
		}

	}
}