#include "RL/Cache/CacheHandle.hpp"

namespace RL
{
	namespace Cache
	{
		CacheHandle::CacheHandle(const std::string& name, const std::string& host , int port )
		{

		}

		bool CacheHandle::Connect() const
		{

			// on successful connection, we fire the event

			return true;
		}

		CacheConnection& CacheHandle::GetHandle()
		{
			return _Connection;
		}

		std::string CacheHandle::GetCacheName() const
		{
			return _Name;
		}

		SignalConnection CacheHandle::Connect(const CacheSessionSignalSubscriber& subscriber)
		{
			return _SessionSignal.connect(subscriber);
		}
	}
}