#include "Jedi.h"
#include "util/StringUtility.h"
#include "RL/Data/GraphDataManager.h"
#include "RL/Cache/CacheQueryManager.h"
#include <boost/signals2/signal.hpp>
#include <boost/signals2/shared_connection_block.hpp>
#include <boost/unordered_map.hpp>
#include <algorithm>

#include "RL/Util/LogCommon.h"

using namespace boost;
using namespace RL::Cache;
using namespace RL::Data;

namespace RL
{
	namespace Client
	{

		typedef signals2::signal<void (double)> OnKVData;
		typedef boost::shared_ptr<OnKVData> SPOnKVData;
		typedef OnKVData::slot_type OnKVDataCallback;
		typedef boost::signals2::connection JediApprenticeIOConnection;

		typedef signals2::shared_connection_block ApprenticeConnectionBlocker;
		typedef boost::shared_ptr<ApprenticeConnectionBlocker> SPApprenticeConnectionBlocker;
		
		LoggerPtr logger = Logger::getLogger("Jedi");

		struct JediApprenticeIOConnectionDetails
		{
			JediApprenticeIOConnection _oConnection;
			SPApprenticeConnectionBlocker _oBlocker; // by default, we are not blocked
			JediApprenticeIOConnectionDetails(JediApprenticeIOConnection c) ;

			bool Block();
			bool UnBlock();
		};

		class JediApprenticeIO
		{
		private:
			typedef unordered_map<string, SPOnKVData> DataSignalCache;
			DataSignalCache::value_type SignalEntryValueType;
			typedef DataSignalCache::iterator DataSignalCacheIter;
			DataSignalCache _mapSignaleCache;

			typedef boost::unordered_map<string, JediApprenticeIOConnectionDetails> ConnectionCache;
			ConnectionCache _mapConnection;

		public:
			bool HasShownInterest(const string& sQuestion)
			{
				DataSignalCacheIter it = _mapSignaleCache.find(sQuestion);
				return (it != _mapSignaleCache.end()) ? true : false;				
			}

			bool ShowingInterest(const string& sQuestion, OnKVDataCallback& cbOnData)
			{
				/* test for already registered condition */
				if(HasShownInterest(sQuestion))
					return false; 

				DataSignalCache::iterator it = _mapSignaleCache.find(sQuestion);
				if(it == _mapSignaleCache.end())
				{
					SPOnKVData spOnKVData(new OnKVData());			
					JediApprenticeIOConnection c = spOnKVData->connect(cbOnData);
					_mapSignaleCache.insert(DataSignalCache::value_type(sQuestion, spOnKVData));
					return true;
				}
				return false; // how did we reach here ?
			}

		};


		bool Jedi::IsValidRequest(const string& sQuestion)
		{
			//string sCleanQuestion = StringUtility::ToLowerAndTrim(sQuestion);
			vector<string>::iterator it = find(_vecPowers.begin(), _vecPowers.end(), sQuestion);
			return (it != _vecPowers.end()) ? true : false;
		}

		Jedi::Jedi(const string& sName, const vector<string>& vecPowers) :
		_sName(sName),
		_vecPowers(vecPowers),
		_spApprenticeIO(new JediApprenticeIO()),
		_spGraphDataManager(new GraphDataManager())
		{

		}

		Jedi::Jedi() :
		_sName("Roy"),		
		_spApprenticeIO(new JediApprenticeIO()),
		_spGraphDataManager(new GraphDataManager())
		{
			_vecPowers.push_back("avg");
			_vecPowers.push_back("Double");
			_vecPowers.push_back("Half");
			_vecPowers.push_back("Checker");

			_vecPowers.push_back("Sum");
			_vecPowers.push_back("Mean");
			_vecPowers.push_back("AutoCorrelation");
			_vecPowers.push_back("Correlation");
			_vecPowers.push_back("LinerRegression");
			_vecPowers.push_back("StandardDeviation");

			if(_spGraphDataManager)
				_spGraphDataManager->InitEventHandling();
		}

		bool Jedi::Interested(const string& sQuestion, const Callback& oCallback)
		{
			

			/* is this a valid request */
			if(!IsValidRequest(sQuestion))
				return false;

			/* is this already registered */
			if(_spApprenticeIO->HasShownInterest(sQuestion))
				return false;

			return true;
		}

		/*
			Expression: 
			source: [cache or memory] // if memory, we select data with a given tag from a given cache - TODO
			type: [rt only, rt and hist, hist only]
			ns:   [ns1.collection1, .. nsn.collectionn]
			qryparams: []

			or

			Expression: Filter
		*/

		int Jedi::Ask(const string& sQuestion, const string& sKey, const string& sTag, const string& sExpression)
		{
			if(!IsValidRequest(sQuestion))
				return -1;

			if(_spGraphDataManager)
				_spGraphDataManager->AddCNode(sQuestion, sKey, sTag);
			else
			{
				
				log4cxx::logstream ls(logger, Level::getInfo()); 
				ls << "GraghDataManager isn't initialized."<<LOG4CXX_ENDMSG;

				return -1; //TODO - return code
			}

			/* 
				TODO
				analyze the expression and instantiates the appropriate types of 
				query objects and tags to realtime tailed query. See CacheQueryManager.
			*/
			
			string sDataStream = sExpression;	//TODO
			CacheQueryManager::Instance().AddTag(sDataStream, sTag);

			return 0;
		}

		int Jedi::Connect(const string& sSourceQuestion, const string& sDestQuestion)
		{
			if(!IsValidRequest(sSourceQuestion)||!IsValidRequest(sDestQuestion))
				return -1;

		
			if(_spGraphDataManager)
				_spGraphDataManager->Connect(sSourceQuestion,sDestQuestion);

		}
		
		int Jedi::Save(const string& sFileName)
		{
			if(_spGraphDataManager)
				_spGraphDataManager->SaveGraph(sFileName);

			return 0;
		}
		
		int Jedi::Load(const string& sFileName)
		{
			if(_spGraphDataManager)
				_spGraphDataManager->LoadGraph(sFileName);

			return 0;


		}
		
		//TODO: AddFilter should map to specific Filter
		int Jedi::AddFilter( const std::string &sNodeName, const  string &sStartTime, long lPeriod, const string& sProperty)
		{

			
			if(_spGraphDataManager)
				_spGraphDataManager->AddFilterNode(sNodeName,sStartTime,lPeriod,sProperty);

			return 0;

		}

		int Jedi::AttachFilter(const std::string &sFilterName, const std::string &sCalcName)
		{

			if(_spGraphDataManager)
				_spGraphDataManager->ConnectFilterWithCalc(sFilterName,sCalcName);

			
			return 0;

		}

		bool Jedi::TakeBreak(const string& sQuestion) 
		{
			return true;
		}

		bool Jedi::Done(const string& sQuestion)
		{
			return true;
		}

	}
}