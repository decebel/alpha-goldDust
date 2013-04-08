#include "RL/Util/AppConfig.h"
#include <stdlib.h>

namespace RL
{
	namespace Config
	{
		AppConfig::AppConfig() :
		_sBasePath("")
		{
			Init();
		}
		
		void AppConfig::Init()
		{
			char * pPath;
			pPath = getenv ("RL_HOME");
			if(pPath == NULL)
			{
				_sBasePath = "C:\\RefLib\\RLCommandLine\\lib\\release";
				//_sBasePath = "C:\\RefLib\\TestRL\\bin";
			}
			else
			{
				_sBasePath = string(pPath);
			}
		}

		AppConfig& AppConfig::GetAppConfig()
		{
			static AppConfig oInstance;
			return oInstance;
		}

		const string& AppConfig::GetBasePath()
		{
			return _sBasePath;
		}
	}
}