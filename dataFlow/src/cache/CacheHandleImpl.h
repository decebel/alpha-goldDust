#ifndef CACHEHANDLEIMPL_DF_H
#define CACHEHANDLEIMPL_DF_H

#include "CacheFwd.h"
#include "CacheHandleBase.h"
#include "CacheConfig.h"
#include <string>

namespace DF
{
	namespace Cache
	{
		class MongoCacheHandle : public ACacheHandle
		{

		private:
			MongoCacheConfig _oConfig;			
			SPDBClientConnection _spConnectionHandle;

		public:
			MongoCacheHandle(const MongoCacheConfig& oConfig);
			const string& GetHost() const { return _oConfig.GetHost(); }
			const int& GetPort() const { return _oConfig.GetPort(); }						
			SPDBClientConnection GetHandle();
			bool Connect();
		};

		class FileCacheHandle :  public ACacheHandle
		{
		private:
			FileCacheConfig _oConfig;
		public:
			FileCacheHandle(const FileCacheConfig& oConfig);
			const string& GetFileName() const { return _oConfig.GetFile(); }
			bool Connect();
		};
	}
}

#endif