#pragma once

#include "CacheFwd.h"
#include <string>

using namespace std;

namespace RL
{
	namespace Cache
	{
		class QueryExpression
		{

		};

		class FileQuery : public QueryExpression
		{
		};

		class CloudQuery : public QueryExpression
		{
		public:
			string _sNamespace;
			string _sCollection;
		};

		class CacheQuery1
		{

		private:
			
			// Cache handle. Can be local or remote or peer cache
			SPACacheHandle _CacheHandle;			

			// Client notification when a tailed cursor results in new data from cache
			OnCacheUpsertSignal _CacheUpsertSignal;

			// If a cursor gets killed, timeouts etc. we should signal
			OnCacheAdminEvent _CacheTailAdminEvent;

		public:

			CacheQuery1(SPACacheHandle& conn); 
			
			virtual void RunQuery(mongo::BSONObj& oQuery);

			CacheSignalConnection SubscribeData(const CacheUpsertSubscriber& subscriber);
			CacheSignalConnection SubscribeCacheEvents(const CacheAdminEventEventSubscriber& subscriber, bool dummy);

			// we want to make sure the clean-up operation cleans handles from underlying cache
			virtual ~CacheQuery1(); 

		};


		class CacheTail 
		{

		private:
			
			// Cache handle. Can be local or remote or peer cache
			SPACacheHandle _CacheHandle;
			
			QueryExpression _oQuery;

			// Client notification when a tailed cursor results in new data from cache
			OnCacheUpsertSignal _CacheDataSignal;

			// If a cursor gets killed, timeouts etc. we should signal
			OnCacheAdminEvent _CacheTailAdminEvent;


		public:

			CacheTail(SPACacheHandle& conn, const QueryExpression& oQuery); 

			// TODO. Where should we start tailing from?
			virtual void Tail();

			CacheSignalConnection SubscribeData(const CacheUpsertSubscriber& subscriber);
			CacheSignalConnection SubscribeCacheEvents(const CacheAdminEventEventSubscriber& subscriber, bool dummy);

			// we want to make sure the clean-up operation cleans handles from underlying cache
			virtual ~CacheTail(); 

		};


		class CloudCacheTail : public CacheTail
		{
			
		public:
			void Tail();
		};

		class FileCacheTail : public CacheTail
		{
		public:
			void Tail();

		};
		
	}
}

