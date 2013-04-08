#ifndef CACHEHANDLEBASE_DF_H
#define CACHEHANDLEBASE_DF_H

#include "CacheFwd.h"
#include <string>

using namespace std;
using namespace boost;

namespace DF
{
	namespace Cache
	{
		//class CacheSessionSignalArgs
		//{
		//};

		class ACacheHandle
		{
			std::string _sName;
		protected:
			ACacheHandle(const string& sName);			

		public:
			
			/* 
				Cache admin events 
				Such as Connection setup, disconnect, reset, network error, data error.
				We should have error code for each error type
			*/
			OnCacheAdminEvent _onAdminEvent;
			std::string GetCacheName() const;		
			CacheSignalConnection SubscribeAdminEvents(const CacheAdminEventEventSubscriber& subscriber);

			virtual bool Connect() = 0;

		};

	}
}

#endif