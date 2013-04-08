#include "CacheConnectionManager.h"
#include "CacheHandleImpl.h"
#include "CacheConfig.h"
#include "dbclient.h"

namespace DF
{
	namespace Cache
	{

		/**
		* Default Cache Session Events Handler
		* @arg : SessionEvent Details. Such as
		* Successfully Connected, Disconnected etc
		**/

		void OnCacheSessionEvent(BSONObj& bson)
		{
			
			// log the event to log file, web admin etc
			// bson["cache"] 
			// bson["event"]
			// bson["desc"]
		}

		CacheConnectionManager::CacheConnectionManager() 
		{
			// notify log file, web admin ?
		}

		CacheConnectionManager& CacheConnectionManager::Instance()
		{
			static CacheConnectionManager instance;
			return instance;
		}

		void CacheConnectionManager::RegisterCacheAdminEventDefault(const SPACacheHandle& spCacheSession)
		{
			spCacheSession->SubscribeAdminEvents(&OnCacheSessionEvent);
		}


		// We should use a registrar function to create the cache handle object - TODO
		SPACacheHandle CacheConnectionManager::SetupCacheConnection(const CacheConfig& oCacheConfig, bool bAutoRegisterForCacheAdminEvents)
		{
			string sCacheName(oCacheConfig.GetCacheName());
			GCacheHandlesIter iter = _mapGCacheHandle.find(sCacheName);
			if(iter != _mapGCacheHandle.end())
				return (*iter).second;

			const MongoCacheConfig* oMConfig = dynamic_cast<const MongoCacheConfig*>(&oCacheConfig);
			const FileCacheConfig* oFConfig  = dynamic_cast<const FileCacheConfig*>(&oCacheConfig);
			SPACacheHandle spHandle;
			if(oMConfig)
			{
				spHandle = SPACacheHandle(new MongoCacheHandle(*oMConfig));
				_mapGCacheHandle[sCacheName] = spHandle;

			}
			else if(oFConfig)
			{
				spHandle = SPACacheHandle(new FileCacheHandle(*oFConfig));
				_mapGCacheHandle[sCacheName] = spHandle;
			}

			/* make a connection with the cache */
			if(!spHandle->Connect())
			{
				//TODO
				//If are here, we have an error. Until we have error code reporting, we return an empty object
				SPACacheHandle spError;
				return spError;
			}

			if(bAutoRegisterForCacheAdminEvents)
				RegisterCacheAdminEventDefault(spHandle);

			return spHandle;

		}

		SPACacheHandle CacheConnectionManager::GetCache(const string& sCacheName)
		{
		
			GCacheHandlesIter iter = _mapGCacheHandle.find(sCacheName);
			if(iter != _mapGCacheHandle.end())
				return _mapGCacheHandle[sCacheName];

			SPACacheHandle spHandle;
			return spHandle;
		}
	}
}