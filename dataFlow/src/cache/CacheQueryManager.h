#ifndef CACHEQUERYMANAGER_DF_H
#define CACHEQUERYMANAGER_DF_H

#include "CacheFwd.h"
#include <boost/noncopyable.hpp>
#include <boost/unordered_map.hpp>
#include <string>
#include <set>

using namespace std;
using namespace boost;

namespace DF
{
	namespace Cache
	{
		typedef set<string> TagSet;

		class TagKeeper
		{
		private:
			
			// key is namespace.collection
			typedef boost::unordered_map<string, TagSet> MapName2TagSet;
			typedef MapName2TagSet::iterator MapName2TagSetIter;
			MapName2TagSet _mapCacheName2TagSet;			
		public:
			bool AddTag(const string& sName, const string& sTag);
			TagSet& GetTags(const string& sName);
			bool ClearTagSet(const string& sName);
			bool ClearTagKeeper();

		};

		/*
			Concept: A query name is esentially same as "tag" you place on your data
		*/
		class CacheQueryManager : boost::noncopyable
		{

		private:
			CacheQueryManager();			
			typedef boost::unordered_map<std::string, SPCacheQueryBase> GCacheQueryContainer;
			typedef GCacheQueryContainer::iterator GCacheQueryIter;
			GCacheQueryContainer _mapGCacheQuery;
			SPCacheQueryBase _spBQuery; /* for updates, we want to cache the query object.  */
			TagKeeper _oTagKeeper;

		public:
			static CacheQueryManager& Instance();
			bool Initialize();

			// TODO - private impl required. should not be exposed
			SPCacheQueryBase& GetUpsertQuery(); 

			// documentation - TODO
			set<string> Query2TagMapper(const string& sQueryName, const string& sExtra); 
			bool AddTag(const string& sDataStreamName, const string& sTag);			
			bool ClearTagSet(const string& sName);
			bool ClearTagKeeper();

			SPCacheQueryBase SetCloudTailQuery(const string& sCacheName, const string& sQueryName, mongo::BSONObj& oQuery, bool bAutoStart = true);
			SPCacheQueryBase SetCloudSimpleQuery(const string& sCacheName, const string& sQueryName, mongo::BSONObj& oQuery, bool bAutoStart = true);
			SPCacheQueryBase BlockingCloudSimpleQuery(const string& sCacheName, const string& sQueryName, mongo::BSONObj& oQuery);
			
		};
	}
}

#endif