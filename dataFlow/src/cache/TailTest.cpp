#include <client/dbclient.h>
#include <memory>

using namespace mongo;          
using namespace std;

//int main(int argc, char* argv[])
//{
//    DBClientConnection conn;
//    conn.connect("localhost");                                                                                          
//
//    // minKey is smaller than any other possible value
//    BSONElement lastId = maxKey.firstElement();                                                                         
//
//    // { $natural : 1 } means in forward capped collection insertion order
//    Query query = Query().sort("$natural");                                                                             
//
//	//Query query = QUERY( "_id" << GT << lastId ).sort("$natural");
//
//    cout << "loc,val" << std::endl;
//    uint32_t i = 0;
//    struct timeval tv;
//
//	auto_ptr<DBClientCursor> c = conn.query("smoke.types", query, 0, 0, 0,
//		QueryOption_CursorTailable | QueryOption_NoCursorTimeout | QueryOption_AwaitData);
//    
//        while( true ) {
//            if( !c->more() ) {
//				cout<<"more() returned false"<<std::endl;
//                if( c->isDead() )
//                    break;
//                //sleepsecs(1);
//                continue; // we will try more() again
//            }
//			cout<<"more() returned true"<<std::endl;
//            const BSONObj& o = c->next();
//            lastId = o["_id"];
//			cout<<"id="<<lastId<<std::endl;
//            //const double time = o["time"].Double();
//
//            //gettimeofday(&tv, NULL);
//            //const double curr = tv.tv_sec + tv.tv_usec / 1000000.0;
//            //cout << i++ << ", " << curr - time << endl;
//        }
//
//        // prepare to requery from where we left off
//        //query = QUERY( "_id" << GT << lastId ).sort("$natural");
//   
//
//    return 0;
//}