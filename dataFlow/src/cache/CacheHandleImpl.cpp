#include "CacheHandleImpl.h"

#include "dbclient.h"

using namespace mongo;

namespace DF
{
	namespace Cache
	{		

		MongoCacheHandle::MongoCacheHandle(const MongoCacheConfig& oConfig) :
		ACacheHandle(oConfig.GetCacheName()),
		_oConfig(oConfig)
		{
			
			_spConnectionHandle = SPDBClientConnection(new DBClientConnection());
		}


		bool MongoCacheHandle::Connect()
		{			
			string msg;			
			return _spConnectionHandle->connect(_oConfig.GetHost(), msg);			
		}	

		SPDBClientConnection MongoCacheHandle::GetHandle()
		{
			return _spConnectionHandle;
		}

		FileCacheHandle::FileCacheHandle(const FileCacheConfig& oConfig) :
		ACacheHandle(oConfig.GetCacheName()),
		_oConfig(oConfig)
		{						
		}


		bool FileCacheHandle::Connect()
		{			
			return true;	
		}

	}
}