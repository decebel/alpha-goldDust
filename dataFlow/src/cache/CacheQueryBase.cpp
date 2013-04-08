#include "CacheQueryBase.h"
#include "util/concurrency/BackgroundJob.h"
#include "dbclient.h"
#include <fstream>

using namespace DF::Concurrency;
using namespace std;
namespace DF
{
	namespace Cache
	{

		//static ofstream ofs("testCQ.txt");

		struct CacheQueryBase::QueryBackgroundJob : public BackgroundJob
		{
			string _sJobName;
			CacheQueryBase& _oQueryBase;
			mongo::BSONObj _oQueryStatement;
		public:
			CacheQueryBase::QueryBackgroundJob(const string& sName, CacheQueryBase& oQueryBase, mongo::BSONObj& oQuery) :
			  BackgroundJob(),
			  _sJobName(sName),
			  _oQueryBase(oQueryBase),
			  _oQueryStatement(oQuery)
			  {
			  	//  ofs<<"Inside Job()"<<std::endl;
				  //ofs<<"query="<<_oQueryStatement.toString()<<std::endl;
			  }

			  string name() const { return _sJobName; }
			  void run() 
			  {
				  //ofs<<"Inside run"<<std::endl;
				  //ofs<<"query="<<_oQueryStatement.toString()<<std::endl;
				  _oQueryBase.RunQuery(_sJobName,_oQueryStatement);
			  }

		};

		CacheQueryBase::CacheQueryBase(const SPACacheHandle& spConn) :
		_spCacheHandle(spConn)
		{
		}

		void CacheQueryBase::jobRunner(const string& sQueryName,  mongo::BSONObj& oQuery )
		{
			SPQueryBackgroundJob oQueryJob(new QueryBackgroundJob(sQueryName, *this, oQuery));
			//_oJob.reset(oQueryJob);
			_oJob = oQueryJob;
		}


		void CacheQueryBase::SetQuery(const string& sQueryName, mongo::BSONObj& oQuery, bool bStart)
		{
			jobRunner(sQueryName, oQuery);
			//ofs << oQuery.toString()<<std::endl;
			//ofs.flush();
			if(bStart)
				Start();
		}

		CacheQueryBase::~CacheQueryBase()
		{
			// TODO. Cleanup any queries handle etc.
			// We should never clean up cache handle
			// That is the responsibility of CacheConnectionManager
		}
		
		bool CacheQueryBase::Start()
		{
			if(_oJob->running())
				return false;

			_oJob->go();
			return true;
		}

		string CacheQueryBase::GetJobStatus()
		{
			if(_oJob->getState() == BackgroundJob::Done)
				return "Done";
			else if(_oJob->getState() == BackgroundJob::Running)
				return "Done";
			else if(_oJob->getState() == BackgroundJob::NotStarted)
				return "NotStarted";
			
			return "UnKnown";
		}

		CacheSignalConnection CacheQueryBase::SubscribeData(const CacheDataSubscriber& subscriber)
		{
			return _CacheDataSignal.connect(subscriber);
		}

		CacheSignalConnection CacheQueryBase::SubscribeCacheEvents(const CacheAdminEventEventSubscriber& subscriber, bool dummy)
		{
			return _CacheTailAdminEvent.connect(subscriber);
		}


	}

}