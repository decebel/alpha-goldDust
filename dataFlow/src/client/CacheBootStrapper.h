#ifndef CACHEBOOTSTRAPPER_DF_H
#define CACHEBOOTSTRAPPER_DF_H

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>

using namespace std;

namespace DF
{
	namespace Client
	{
		namespace Internal
		{

			class CacheBootStrapper : boost::noncopyable
			{
			private:
				CacheBootStrapper();

			public:
				
				static CacheBootStrapper& GetBootStrapper();			

				/* loads connection configuration objects */
				/* establishes connection(s) with the cache(s) */
				bool LoadCacheConfig(const string& sConfigXml);
			

				/* downloads admin and control objects from startup cache */
				/* cache names => startup.admin, startup.control */
				/* startup.admin cache holds configuration related to this system */
				/* startup.control cache holds configuration related to the users */
				bool DownloadStartupObjects(const vector<string>& vecObjectNames);

				/* */
				bool InitializeStartupObjects();
			};

		}
	}
}

#endif