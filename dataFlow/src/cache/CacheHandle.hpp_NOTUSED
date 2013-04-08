#pragma once


#include "CacheHandleBase.h"
#include "CacheConfig.h"
#include <client/dbclient.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include "CacheCommon.hpp"
#include "CacheFwd.h"

using namespace mongo;      

namespace RL
{
	namespace Cache
	{



		class c {};

		//typedef DBClientConnection CacheConnection;
		typedef c CacheConnection;
		class CacheHandle
		{
			private:
				CacheConnection _Connection;
				std::string _Name;
				std::string _Host;
				int _Port;
				OnCacheSessionSignal _SessionSignal; //TODO. Default subscriber to add

			public:
				CacheHandle(const std::string& name = "local", const std::string& host = "127.0.0.1", int port = 27017);
				bool Connect() const;
				CacheConnection& GetHandle();
				std::string GetCacheName() const;
				SignalConnection Connect(const CacheSessionSignalSubscriber& subscriber);

		};


	}
}