#ifndef CACHECONFIG_DF_H
#define CACHECONFIG_DF_H
#include <string>

using namespace std;

namespace DF
{
	namespace Cache
	{
			class CacheConfig
			{
			private:
				string _sCacheName;
			public:
				CacheConfig(const string& sCacheName) :
				_sCacheName(sCacheName)
				{}
				const string& GetCacheName() const { return _sCacheName; }

				virtual ~CacheConfig() {}
			};

			class MongoCacheConfig : public CacheConfig
			{
			private:
				string _sCacheName;
				string _sHostName;
				int _nPortNum;
				static int _nTypeID;
			public:
				MongoCacheConfig(const string& sCacheName, const string& sHost, const int nPort) :
				CacheConfig(sCacheName),
				_sHostName(sHost),
				_nPortNum(nPort)
				{}

				const string& GetHost() const { return _sHostName; }
				const int& GetPort() const { return _nPortNum; }
			};

			class FileCacheConfig : public CacheConfig
			{
			private:
				string _sFileName;
				static int _nTypeID;
			public:
				FileCacheConfig(const string& sCacheName, const string& sFileName) :
				CacheConfig(sCacheName),
				_sFileName(sFileName)
				{}
				const string& GetFile() const { return _sFileName; }


			};
	}
}

#endif