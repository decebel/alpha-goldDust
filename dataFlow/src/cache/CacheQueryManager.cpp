#include "dbclient.h"
#include "CacheQueryManager.h"
#include "CacheConnectionManager.h"
#include "CacheQuery.h"
//#include "RL\data\DataIOConnector.h"
//#include "RL\util\LogCommon.h"
#include <fstream>

//using namespace RL::Data;
using namespace std;
using namespace mongo;

namespace DF
{
	namespace Cache
	{

		bool TagKeeper::AddTag(const string& sName, const string& sTag)
		{
			MapName2TagSetIter it = _mapCacheName2TagSet.find(sName);
			if(it != _mapCacheName2TagSet.end())
				(*it).second.insert(sTag); 
			else
				_mapCacheName2TagSet[sName].insert(sTag);

			return true;
		}

		TagSet& TagKeeper::GetTags(const string& sName)
		{
			return _mapCacheName2TagSet[sName];
		}

		bool TagKeeper::ClearTagSet(const string& sName)
		{
			_mapCacheName2TagSet.erase(sName);
			return true;
		}
		bool TagKeeper::ClearTagKeeper()
		{
			_mapCacheName2TagSet.clear();
			return true;
		}


		static ofstream ofs("testQM.txt");
		
		set<string> CacheQueryManager::Query2TagMapper(const string& sQueryName, const string& sNamespace)
		{
			set<string> t;
			t.insert(sQueryName);

			//return sQueryName == "pipelinedata" ? sNamespace : sQueryName;			
			return sQueryName == "pipelinedata" ? _oTagKeeper.GetTags(sNamespace) : t;			
		}

		bool CacheQueryManager::AddTag(const string& sDataStreamName, const string& sTag)
		{
			return _oTagKeeper.AddTag(sDataStreamName, sTag);
		}

		bool CacheQueryManager::ClearTagSet(const string& sName)
		{
			return _oTagKeeper.ClearTagSet(sName); 
		}

		bool CacheQueryManager::ClearTagKeeper()
		{
			return _oTagKeeper.ClearTagKeeper(); 
		}

		/* query name concept is same as tag name */
		/* this handler is for data cache */
		void CacheDataNotificationHandler(const string& sQueryName, const string& sNamespace, mongo::BSONObj& oB)
		{			
			// we got data
			//string sTagName 
			//LoggerPtr logger = Logger::getLogger("CQM");

			//log4cxx::logstream ls(logger, Level::getInfo()); 
			//ls<< " Event Fired on Name Space: "<<sNamespace<<LOG4CXX_ENDMSG;

			set<string> sTags = 
				CacheQueryManager::Instance().Query2TagMapper(sQueryName, sNamespace);

			set<string>::iterator it = sTags.begin();
			
			
			for(it; it != sTags.end(); it++)
			{

				//SPOnBSONData spOnBData = 
				//	DataIOConnector::DefaultIOConnector().GetBSONListenersList((*it));

				//log4cxx::logstream ls(logger, Level::getInfo()); 
				//ls<< " Got Signal Callback for Tag: "<<(*it)<<LOG4CXX_ENDMSG;

				//if(spOnBData)
				//	spOnBData->operator ()(oB,(*it));

				//else
				//{
				//	//log4cxx::logstream ls(logger, Level::getInfo()); 
				//	//ls << "No Listeners for tag "<<(*it)<<LOG4CXX_ENDMSG;
				//}
			}

			//if(logger->isInfoEnabled())
			//{
			//	//log4cxx::logstream ls(logger, Level::getInfo()); 
			//	//ls << "From "<<sQueryName<<" We got realdata: "<<oB.toString()<<LOG4CXX_ENDMSG;
			//}

			//ofs << "From: "<<sQueryName<<" We got realdata: "<<oB.toString();
			//ofs.flush();
		}

		void CacheDataAdminNotificationHandler(mongo::BSONObj& oB)
		{			
			ofs << "Admin Notification for Data Cache: "<<oB.toString()<<std::endl;
			ofs.flush();		
		}

		void CacheAdminNotificationHandler(mongo::BSONObj& oB)
		{			
			ofs << "Admin Notification for Tail Cache: "<<oB.toString()<<std::endl;
			ofs.flush();		
		}

		/* this handler is for update to tailed cache that we are listening by default */
		void CacheQueueNotificationHandler(const string& sQueryName, const string& sNamespace, mongo::BSONObj& oB)
		{	

			//LoggerPtr logger = Logger::getLogger("CQM");
			//
			//log4cxx::logstream ls(logger, Level::getInfo()); 
			//ls <<  "Got Tail Data: "<<oB.toString()<<LOG4CXX_ENDMSG;

			ofs << "Got Tail Data: "<<oB.toString()<<std::endl;

			BSONObjBuilder b;
			BSONElement eo = oB.getField("oid");
			if(!eo.eoo())
			{
				//log4cxx::logstream ls(logger, Level::getInfo()); 
			///	ls << "Found oid field "<<eo.number()<<LOG4CXX_ENDMSG;
				ofs << "Found oid field "<<eo.number()<<std::endl;
			}
			else
			{
				//log4cxx::logstream ls(logger, Level::getInfo()); 
				//ls << "Not Found oid field "<<LOG4CXX_ENDMSG;

				ofs << "Not Found oid field "<<std::endl;
				return;
			}

			BSONElement en = oB.getField("ns");
			if(!en.eoo())
			{
				//log4cxx::logstream ls(logger, Level::getInfo()); 
				//ls <<  "Found \"ns\" field "<<en.str()<<LOG4CXX_ENDMSG;

				ofs << "Found \"ns\" field "<<en.str()<<std::endl;
			}
			else
			{
				//log4cxx::logstream ls(logger, Level::getInfo()); 
				//ls <<  "Not Found \"ns\" field "<<LOG4CXX_ENDMSG;
				ofs << "Not Found \"ns\" field "<<std::endl;
				return;
			}

			BSONObj oSubQ = BSON("oid" << eo.number());

			//log4cxx::logstream ls(logger, Level::getInfo()); 
			//ls << "Preparing Query1: "<<oSubQ.toString()<<LOG4CXX_ENDMSG;
			ofs << "Preparing Query1: "<<oSubQ.toString()<<std::endl;
			BSONObj oQ = 
				b.append("ns", oB["ns"].str()).append("q", oSubQ).obj();						
			
			//log4cxx::logstream ls(logger, Level::getInfo()); 
			//ls <<"Preparing Query2: "<<oQ.toString()<<LOG4CXX_ENDMSG;
			ofs << "Preparing Query2: "<<oQ.toString()<<std::endl;
			ofs.flush();

			if(!CacheQueryManager::Instance().GetUpsertQuery())
				return;

			//SPCacheQueryBase spQuery = 
			//	CacheQueryManager::Instance().BlockingCloudSimpleQuery("local", "pipelinedata", oQ);

			CacheQueryManager::Instance().GetUpsertQuery()->RunQuery("pipelinedata", oQ);
		}


		CacheQueryManager::CacheQueryManager()
		{			
		}
		
		bool CacheQueryManager::Initialize()
		{	

			//LoggerPtr logger = Logger::getLogger("CQM");

			//log4cxx::logstream ls(logger, Level::getInfo()); 
		 //   ls << "Initialize CQM "<<LOG4CXX_ENDMSG;
			//
			BSONObjBuilder b;
			string sCacheName("local");
			string sQueryName("pipeline");
			string sNamespace("pl.nq");

			b.append("ns", sNamespace);	
			BSONObj oObj = b.obj();
			SPCacheQueryBase spTQuery = SetCloudTailQuery(sCacheName, sQueryName, oObj, false);
			spTQuery->SubscribeData(CacheQueueNotificationHandler);
			spTQuery->SubscribeCacheEvents(CacheAdminNotificationHandler, true);

			/* for extracting data pointed by the tailed cache */
			//BSONObj oQEmpty;
			//_spBQuery = 
			//	CacheQueryManager::Instance().BlockingCloudSimpleQuery(sCacheName, "pipelinedata", oQEmpty);

			//_spBQuery->SubscribeData(CacheDataNotificationHandler);
			//_spBQuery->SubscribeCacheEvents(CacheDataAdminNotificationHandler, true);

			/* start tailing */
			return spTQuery->Start();
			
		}

		SPCacheQueryBase& CacheQueryManager::GetUpsertQuery()
		{
			return _spBQuery;
		}
		CacheQueryManager& CacheQueryManager::Instance()
		{
			static CacheQueryManager instance;
			return instance;
		}

		SPCacheQueryBase CacheQueryManager::SetCloudTailQuery(const string& sCacheName, const string& sQueryName, mongo::BSONObj& oQuery, bool bAutoStart)
		{
			SPACacheHandle spCacheHandle = CacheConnectionManager::Instance().GetCache(sCacheName);
			GCacheQueryIter iter = _mapGCacheQuery.find(sQueryName);
			if(iter != _mapGCacheQuery.end())
				return (*iter).second;	// TODO: If query with the same name exists, and can be re-used, we must reuse the same object.
			
			SPCacheQueryBase spQuery(new CloudTailQuery(spCacheHandle));
			_mapGCacheQuery[sQueryName] = spQuery;
			
			spQuery->SetQuery(sQueryName, oQuery, bAutoStart);
			
			return spQuery;
		}

		SPCacheQueryBase CacheQueryManager::SetCloudSimpleQuery(const string& sCacheName, const string& sQueryName, mongo::BSONObj& oQuery, bool bAutoStart)
		{
			SPACacheHandle spCacheHandle = CacheConnectionManager::Instance().GetCache(sCacheName);
			GCacheQueryIter iter = _mapGCacheQuery.find(sQueryName);
			if(iter != _mapGCacheQuery.end())
				return (*iter).second;		// TODO: If query with the same name exists, and can be re-used, we must reuse the same object.
			
			SPCacheQueryBase spQuery(new CloudSimpleQuery(spCacheHandle));
			_mapGCacheQuery[sQueryName] = spQuery;
	
			spQuery->SetQuery(sQueryName, oQuery, bAutoStart);

			return spQuery;			
		}

		SPCacheQueryBase CacheQueryManager::BlockingCloudSimpleQuery(const string& sCacheName, const string& sQueryName, mongo::BSONObj& oQuery)
		{
			SPACacheHandle spCacheHandle = CacheConnectionManager::Instance().GetCache(sCacheName);
			GCacheQueryIter iter = _mapGCacheQuery.find(sQueryName);
			if(iter != _mapGCacheQuery.end())
				return (*iter).second;		// TODO: If query with the same name exists, and can be re-used, we must reuse the same object.
			
			SPCacheQueryBase spQuery(new CloudSimpleQuery(spCacheHandle));
			_mapGCacheQuery[sQueryName] = spQuery;

			return spQuery;			
		}

	}
}

