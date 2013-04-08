#ifndef CACHEQUERYBASE_DF_H
#define CACHEQUERYBASE_DF_H

#include "CacheFwd.h"
#include <string>

using namespace std;
using namespace boost;


namespace DF
{
	namespace Cache
	{

		class CacheQueryBase
		{
		protected:			

			// Cache handle. Can be local or remote or peer cache
			SPACacheHandle _spCacheHandle;			

			// Client notification when a tailed cursor results in new data from cache
			OnCacheDataSignal _CacheDataSignal;

			// If a cursor gets killed, timeouts etc. we should signal
			OnCacheAdminEvent _CacheTailAdminEvent;		

			// construct the cache handle
			CacheQueryBase(const SPACacheHandle& conn); 

			// background worker
			struct QueryBackgroundJob;
			typedef boost::shared_ptr<QueryBackgroundJob> SPQueryBackgroundJob;
			SPQueryBackgroundJob _oJob; 					

			void jobRunner( const string& sName,  mongo::BSONObj& oQuery);
			

		public:
						
			void SetQuery(const string& sQueryName, mongo::BSONObj& oQuery, bool bStart = true);
			bool Start();
			string GetJobStatus();
			SPACacheHandle GetCacheHandle() { return _spCacheHandle; }
			CacheSignalConnection SubscribeData(const CacheDataSubscriber& subscriber);
			CacheSignalConnection SubscribeCacheEvents(const CacheAdminEventEventSubscriber& subscriber, bool dummy);
			virtual void RunQuery(const string& sQueryName, mongo::BSONObj& oQuery) = 0;
			// we want to make sure the clean-up operation cleans handles from underlying cache
			virtual ~CacheQueryBase(); 
		};
	}

}

#endif