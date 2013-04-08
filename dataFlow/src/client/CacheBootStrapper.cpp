#include "CacheBootStrapper.h"
#include "cache/CacheConnectionManager.h"
#include "cache/CacheQueryManager.h"
#include "cache/CacheConfig.h"
#include "cache/CacheHandleImpl.h"

using namespace DF::Cache;

namespace DF
{
	namespace Client
	{
		namespace Internal
		{
			CacheBootStrapper::CacheBootStrapper()
			{

			}

			CacheBootStrapper& CacheBootStrapper::GetBootStrapper()
			{
				static CacheBootStrapper instance;
				return instance;
			}

			bool CacheBootStrapper::LoadCacheConfig(const string& sConfigXml)
			{

				/* de-serialize the config xmls - TODO */

				MongoCacheConfig* oConfig = new MongoCacheConfig("local", "127.0.0.1", 27017);

				/* 
					CacheConnectionManager creates and internally caches the handle,
					so CacheBootStrapper does not require holding the cache handle.
					This should also connect with the actual cache object.
				*/

				SPACacheHandle spHandle = CacheConnectionManager::Instance().SetupCacheConnection(*oConfig);
				delete oConfig;
			
				if(spHandle) 
					return true;

				return false;
			}

			bool CacheBootStrapper::InitializeStartupObjects()
			{				
				return CacheQueryManager::Instance().Initialize();
				
			}


		}
	}
}
