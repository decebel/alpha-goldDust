#pragma once

#include "CacheCommon.hpp"
#include "CacheTail.hpp"
#include <boost\noncopyable.hpp>
class CacheTail;

namespace RL 
{
	namespace Cache
	{
		class CacheUpsertObserver : boost::noncopyable
		{
		private:
			//CacheTail _TailCursor;				// 
			CacheUpsertCallback _Callback;		// external callback
			void ObjectIDCallback(BSONObj& );	// tail callback


		public:
			CacheUpsertObserver(const CacheUpsertCallback& callback, const char* ns, bool start = false);
			virtual void Start();
			~CacheUpsertObserver();
		};

	}
}
