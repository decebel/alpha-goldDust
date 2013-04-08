#include "RL/Cache/CacheTail.hpp"
#include <client/dbclient.h>
using namespace mongo;

namespace RL
{
	namespace Cache
	{

			CacheTail::CacheTail(SPACacheHandle& conn, const QueryExpression& oQuery) :
			_CacheHandle(conn),
			_oQuery(oQuery)
			{

			}

			void CacheTail::Tail()
			{
				//// we need to specify the start key to query
				//// reason. we restart the app or we have implemented a pub/sub model 
				//// and we dont have update notification mechanism
				//// MAYBE WE CAN SIMPLY IMPLEMENT - START, END, QUERY_ID

				//// minKey is smaller than any other possible value
				//// BSONElement lastId = minKey.firstElement();                                                                         

				////char* ns = _Query["namespace"];
				//
				//Query query = Query().sort("$natural");
				//auto_ptr<DBClientCursor> c = _CacheConnection->GetHandle().query(_sNameSpace.c_str(), query, 0, 0, 0,
				//	QueryOption_CursorTailable | QueryOption_NoCursorTimeout | QueryOption_AwaitData);
			
				//while( true ) 
				//{
				//	if( !c->more() )
				//	{						
				//		if( c->isDead() )
				//		{
				//			if(!_CacheTailAdminSignal.empty())
				//			{
				//				BSONObj bsonObj("cursor dead");									
				//				_CacheTailAdminSignal(_sNameSpace, _sCacheName, bsonObj);
				//			}
				//			break;
				//		}
				//		continue;
				//	}

				//	//cout<<"more() returned true"<<std::endl;
				//	BSONObj& o = c->next();
				//	//_Callback(o);
				//	
				//	_CacheUpsertSignal(o);
				//	//lastId = o["_id"];
				//	//cout<<"id="<<lastId<<std::endl;
				//	// prepare to requery from where we left off
				//	// query = QUERY( "_id" << GT << lastId ).sort("$natural");

				//}												
			}

			CacheTail::~CacheTail()
			{
				// TODO. Cleanup any cache handles. queries etc.
			}


			CacheSignalConnection CacheTail::SubscribeData(const CacheUpsertSubscriber& subscriber)
			{
				return _CacheUpsertSignal.connect(subscriber);
			}

			CacheSignalConnection CacheTail::SubscribeCacheEvents(const CacheAdminEventEventSubscriber& subscriber, bool dummy)
			{
				return _CacheTailAdminEvent.connect(subscriber);
			}

	}
}