#ifndef CACHEOBJECTSREGISTRAR_RL_H
#define CACHEOBJECTSREGISTRAR_RL_H
#include <string>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;

namespace RL
{
	namespace Cache
	{
		class CacheConfig;
		class Cache;
		typedef boost::shared_ptr<CacheConfig> SPCacheConfig;
		typedef boost::shared_ptr<Cache> SPCache;

		typedef CacheConfig* (*CacheConfigCreator)(void* );
		typedef Cache* (*CacheCreator)(void* );
		

		class CacheObjectsRegistrar
		{
		private:
			typedef unordered_map<int, CacheConfigCreator> MapCacheConfig;
			MapCacheConfig _mapCacheConfig;
			typedef unordered_map<int, CacheCreator> MapCacheCreator;
			MapCacheCreator _mapCacheCreator;

		public:
			static CacheObjectsRegistrar& CacheObjectRegistrar();
			bool RegisterCacheConfigCallback(int nType, CacheConfigCreator funcCallback);
			bool RegisterCacheCallback(int nType, CacheConfigCreator funcCallback);
			SPCacheConfig CreateCacheConfig(int nType, void* oArg);
			SPCacheConfig CreateCache(int nType, void* oArg);

		};

	}
}