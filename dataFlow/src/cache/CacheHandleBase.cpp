#include "CacheHandleBase.h"

namespace DF
{
	namespace Cache
	{
		ACacheHandle::ACacheHandle(const string& sName) :
		_sName(sName)
		{}

		std::string ACacheHandle::GetCacheName() const
		{
			return _sName;
		}


		CacheSignalConnection ACacheHandle::SubscribeAdminEvents(const CacheAdminEventEventSubscriber& subscriber)
		{
			return _onAdminEvent.connect(subscriber);
		}
	}

}