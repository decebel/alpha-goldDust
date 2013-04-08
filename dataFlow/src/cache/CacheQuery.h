#ifndef CACHEQUERY_DF_H
#define CACHEQUERY_DF_H

#include "CacheFwd.h"
#include "CacheQueryBase.h"
#include <string>

using namespace std;
using namespace boost;


namespace DF
{
	namespace Cache
	{


		class CloudTailQuery : public CacheQueryBase
		{	
		public:
			void RunQuery(const string& sQueryName, mongo::BSONObj& oQuery);

		
			CloudTailQuery(const SPACacheHandle& conn);						
		};


		class CloudSimpleQuery : public CacheQueryBase
		{
		public:
			void RunQuery(const string& sQueryName, mongo::BSONObj& oQuery);
		
			CloudSimpleQuery(const SPACacheHandle& conn);
			
		};

		class FileTailQuery : public CacheQueryBase
		{			
		public:
			void RunQuery(const string& sQueryName, mongo::BSONObj& oQuery);
		
			FileTailQuery(const SPACacheHandle& conn);			
			
		};

		class FileSimpleQuery : public CacheQueryBase
		{			
		public:
			void RunQuery(const string& sQueryName, mongo::BSONObj& oQuery);		
			FileSimpleQuery(const SPACacheHandle& conn);
		};


	}
}

#endif