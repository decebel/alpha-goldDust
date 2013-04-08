#include "CacheQuery.h"
#include "CacheHandleImpl.h"
#include "util/StringUtility.h"
#include "dbclient.h"
//#include "RL\util\LogCommon.h"



using namespace std;
using namespace mongo;

namespace DF
{
	namespace Cache
	{
		static ofstream ofs("testTail.txt");

		CloudTailQuery::CloudTailQuery(const SPACacheHandle& conn) :
		CacheQueryBase(conn)
		{

		}

		void CloudTailQuery::RunQuery(const string& sQueryName, mongo::BSONObj& oQuery)
		{

			//LoggerPtr logger = Logger::getLogger("CQM");

				// impl for tailing
				// we need to specify the start key to query
				// reason. we restart the app or we have implemented a pub/sub model 
				// and we dont have update notification mechanism
				// MAYBE WE CAN SIMPLY IMPLEMENT - START, END, QUERY_ID

				// minKey is smaller than any other possible value
				// BSONElement lastId = minKey.firstElement();                                                                         

				//char* ns = _Query["namespace"];
				
				ACacheHandle* oCacheHandle = GetCacheHandle().get();
				MongoCacheHandle* oMongoCacheHandle = dynamic_cast<MongoCacheHandle*>(oCacheHandle);
				if(!oMongoCacheHandle)
					return;
				
				//if(logger->isInfoEnabled())
				//{
				//	log4cxx::logstream ls(logger, Level::getInfo()); 
				//	ls <<"Query Object toString: "<<oQuery.toString()<<LOG4CXX_ENDMSG;
				//}

				ofs<<"Query Object toString: "<<oQuery.toString()<<std::endl;

				mongo::BSONElement e = oQuery.getField("ns");				
				if(e.eoo())
				{	
					//log4cxx::logstream ls(logger, Level::getInfo()); 
					//ls<<"no ns field found in query: "<<oQuery.toString()<<LOG4CXX_ENDMSG;
					return;
				}
				
				string sNamespace = e.str(); //oQuery["ns"];
				//TODO - replace
				vector<string> vecTokens;
				StringUtility::Split(sNamespace, vecTokens, ".");				
				if(vecTokens.size() != 2)
				{

					//log4cxx::logstream ls(logger, Level::getInfo()); 
					//ls<<"Incorrect namespace: "<<sNamespace<<LOG4CXX_ENDMSG;
				
					ofs<<"Incorrect namespace: "<<sNamespace<<std::endl;
					ofs.flush();
					return;
				}
				
				//log4cxx::logstream ls(logger, Level::getInfo()); 
				//ls<<"querying namespace: "<<sNamespace<<LOG4CXX_ENDMSG;
				ofs<<"querying namespace: "<<sNamespace<<std::endl;
				ofs.flush();
				Query query = Query().sort("$natural");
				auto_ptr<DBClientCursor> c = oMongoCacheHandle->GetHandle()->query(sNamespace.c_str(), query, 0, 0, 0,
					QueryOption_CursorTailable | QueryOption_NoCursorTimeout | QueryOption_AwaitData);
			
				while( true ) 
				{
					if( !c->more() )
					{						
						if( c->isDead() )
						{
							if(!_CacheTailAdminEvent.empty())
							{
								BSONObj bsonObj("cursor dead");									
								_CacheTailAdminEvent(bsonObj);
							}
							break;
						}
						continue;
					}					
					BSONObj& o = c->next();
					if(!_CacheDataSignal.empty())
					{
						//log4cxx::logstream ls(logger, Level::getInfo()); 
						//ls<<"Signalling Data "<<o.toString()<<LOG4CXX_ENDMSG;
						ofs<<"Signalling Data "<<o.toString()<<std::endl;
						cout<<"Signalling Data "<<o.toString()<<std::endl;
						//_CacheDataSignal(sQueryName, vecTokens[1], o);					
						//_CacheDataSignal(sQueryName, sNamespace, o);					
					}
					else
					{
						//log4cxx::logstream ls(logger, Level::getInfo());
						cout<<"No Data Listeners  "<<std::endl;
						//ls<<"No Data Listeners "<<LOG4CXX_ENDMSG;
					}

					ofs.flush();
					
					//_CacheUpsertSignal(o);
					//lastId = o["_id"];
					//cout<<"id="<<lastId<<std::endl;
					// prepare to requery from where we left off
					// query = QUERY( "_id" << GT << lastId ).sort("$natural");

				}	
		}

		CloudSimpleQuery::CloudSimpleQuery(const SPACacheHandle& conn) :
		CacheQueryBase(conn)
		{

		}

		void CloudSimpleQuery::RunQuery(const string& sQueryName, mongo::BSONObj& oQuery)
		{
				// impl for simple query
				ACacheHandle* oCacheHandle = GetCacheHandle().get();
				MongoCacheHandle* oMongoCacheHandle = dynamic_cast<MongoCacheHandle*>(oCacheHandle);
				if(!oMongoCacheHandle)
					return;
			
				BSONElement oNS = oQuery.getField("ns");
				if(oNS.eoo())
					return; // TODO - fire admin event

				string sNamespace = oNS.str();
				mongo::BSONObj oBsonQuery = oQuery.getObjectField("q");

				//TODO - replace
				vector<string> vecTokens;
				StringUtility::Split(sNamespace, vecTokens, ".");				
				if(vecTokens.size() != 2)
				{
					ofs<<"Incorrect namespace: "<<sNamespace<<std::endl;
					ofs.flush();
					return;
				}

				auto_ptr<DBClientCursor> c = oMongoCacheHandle->GetHandle()->query(sNamespace.c_str(), oBsonQuery);			
				while( c->more() ) 
				{
					BSONObj& o = c->next();
					if(!_CacheDataSignal.empty())
						//_CacheDataSignal(sQueryName, vecTokens[1], o);										
						_CacheDataSignal(sQueryName, sNamespace, o);
				}	
		}

		FileTailQuery::FileTailQuery(const SPACacheHandle& conn) :
		CacheQueryBase(conn)
		{

		}

		void FileTailQuery::RunQuery(const string& sQueryName, mongo::BSONObj& oQuery)
		{
			// impl for file tailing
		}

		FileSimpleQuery::FileSimpleQuery(const SPACacheHandle& conn) :
		CacheQueryBase(conn)
		{

		}

		void FileSimpleQuery::RunQuery(const string& sQueryName, mongo::BSONObj& oQuery)
		{
			// impl for simple query
		}
	}

}

