#include "RL/Cache/CacheTail.hpp"
#include <iostream>

using namespace RL::Cache;

void TailCallBackTest(BSONObj& obj)
{
	BSONElement lastId = obj["_id"];
	cout<<"id="<<lastId<<std::endl;	
}

//int main(int argc, char* argv[])
//{
//
// //   DBClientConnection conn;
// //   conn.connect("localhost");                                                                                          	
//
//	//CacheTail tail(conn);
//	//tail.Connect(&TailCallBackTest);
//	//
//	//tail.Tail("smoke.types");
//
//
//	return 0;
//}