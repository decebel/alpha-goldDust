#include "DFFramework.h"
//#include "RL/cn/CalcNodesRegistrar.h"
//#include "RL/util/AppConfig.h"
//#include "RL/util/LogCommon.h"
#include <string>

using namespace std;
//using namespace RL::Config;

//
// Automatic initialization of the framework
//
#if defined(_WIN32) && !defined(DATAFLOW_FRAMEWORK_NO_AUTOMATIC_INIT)
namespace
{
	class DFInitializer
	{
	public:
		DFInitializer()
		{
			DF::initializeDataFlow();
		}
		

		~DFInitializer()
		{
			DF::unInitializeDataFlow();	
		}
	};
	
	static DFInitializer initializer;
}
#endif // _WIN32

namespace DF
{

	void LoadLogger()
	{
		//const string& sBasePath = AppConfig::GetAppConfig().GetBasePath();

		////TODO - check if base path and file exists

		//PropertyConfigurator::configure(sBasePath+"\\log4cxx.properties");		
		//LoggerPtr logger = Logger::getLogger("RLFramework");
		//LOG4CXX_INFO(logger, "==========RLFramework Version 1.0==============");
		//if(logger->isInfoEnabled())
		//{
		//	log4cxx::logstream ls(logger, Level::getInfo()); 
		//	ls << "Initializing Framework "<<LOG4CXX_ENDMSG;
		//}

	}

	void initializeDataFlow()
	{
		#if defined(_WIN32)		
			// some win specific stuff
		#endif // _WIN32

		//AppConfig::GetAppConfig();
		//LoadLogger();
		//CalcNodesRegistrar::RegisterNodeTypes();
	}


	void unInitializeDataFlow()
	{
		#if defined(_WIN32)
			//SomeCleanUP();
		#endif // _WIN32
	}


}