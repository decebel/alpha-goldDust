#ifndef CACHEFWD_DF_H
#define CACHEFWD_DF_H

#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <string>

using namespace boost;
using namespace std;

namespace mongo
{
	class DBClientConnection; 
	class BSONObj;
}

namespace DF
{
	namespace Cache
	{
		class CacheSessionSignalArgs;

		class CacheConfig;

		class ACacheHandle;
		typedef boost::shared_ptr<ACacheHandle> SPACacheHandle;

		typedef boost::shared_ptr<mongo::DBClientConnection> SPDBClientConnection;

		class CacheQueryBase;
		typedef boost::shared_ptr<CacheQueryBase> SPCacheQueryBase;

		class CacheTail;
		typedef boost::shared_ptr<CacheTail> SPCacheTail;

		class CacheSessionSignalArgs;
		typedef boost::signals2::signal<void (CacheSessionSignalArgs&)> CacheSessionSignalType;

		using mongo::BSONObj;
		typedef boost::signals2::signal<void (BSONObj&)> SignalWithBSON1Arg;
		//typedef SignalWithBSON1Arg OnCacheUpsertSignal;
		typedef SignalWithBSON1Arg OnCacheAdminEvent;	

		typedef boost::signals2::signal<void (const string&, const string&, BSONObj&)> SignalWithStringBSONArg;
		typedef SignalWithStringBSONArg OnCacheDataSignal;
		typedef SignalWithStringBSONArg::slot_type CacheDataSubscriber;

		//typedef OnCacheUpsertSignal::slot_type CacheUpsertSubscriber;
		typedef OnCacheAdminEvent::slot_type CacheAdminEventEventSubscriber;

		typedef boost::signals2::connection CacheSignalConnection;
	}
}

#endif
