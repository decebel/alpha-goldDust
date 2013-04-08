#pragma once

#include <boost\function.hpp>
#include <boost\signals2.hpp>
#include <boost/shared_ptr.hpp>
#include <client/dbclient.h>

using namespace mongo;      
typedef int TailID;

//class CacheHandle;
//typedef boost::shared_ptr<CacheHandle> SPCacheHandle;

typedef boost::function<void (BSONObj& )> CallbackWithBSON1ArgType;
typedef CallbackWithBSON1ArgType CacheUpsertCallback;

typedef boost::signals2::signal<void (BSONObj&)> SignalWithBSON1ArgType;
typedef SignalWithBSON1ArgType OnCacheUpsertSignal;
typedef OnCacheUpsertSignal::slot_type CacheUpsertSubscriber;

typedef SignalWithBSON1ArgType OnCacheSessionSignal;
typedef OnCacheSessionSignal::slot_type CacheSessionSignalSubscriber;

typedef boost::signals2::signal<void (const std::string& ns, const std::string& cacheName)> OnCacheTailCreated;
typedef OnCacheTailCreated::slot_type CacheTailCreatedSubscriber;

typedef boost::signals2::signal<void (const std::string& ns, const std::string& cacheName, BSONObj& )> OnCacheTailAdminEvents;
typedef OnCacheTailAdminEvents::slot_type CacheTailAdminEventsSubscriber;

typedef boost::signals2::connection SignalConnection;

