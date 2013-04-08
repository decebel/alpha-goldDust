#include "BackgroundJob.h"

#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/date_time.hpp>
using namespace boost;

namespace DF
{
	namespace Concurrency
	{
    // both the BackgroundJob and the internal thread point to JobStatus
    struct BackgroundJob::JobStatus {
        JobStatus( bool delFlag )
            : deleteSelf(delFlag), state(NotStarted) { }

        const bool deleteSelf;

        boost::recursive_mutex m;  // protects state below
        boost::condition finished; // means _state == Done
        State state;
    };

    BackgroundJob::BackgroundJob( bool selfDelete ) {
        _status.reset( new JobStatus( selfDelete ) );
    }

    // Background object can be only be destroyed after jobBody() ran
    void BackgroundJob::jobBody( boost::shared_ptr<JobStatus> status ) {
		
		 status->state = Running;

        const string threadName = name();
        //if( ! threadName.empty() )
        //    setThreadName( threadName.c_str() );

        try {
            run();
        }
        catch ( std::exception& e ) {
            //log( LL_ERROR ) << "backgroundjob " << name() << "error: " << e.what() << endl;
        }
        catch(...) {
            //log( LL_ERROR ) << "uncaught exception in BackgroundJob " << name() << endl;
        }

        {
			boost::recursive_mutex::scoped_lock l( status->m );
            status->state = Done;
            status->finished.notify_all();
        }

        if( status->deleteSelf )
            delete this;
    }

    BackgroundJob& BackgroundJob::go() {
        boost::thread t( boost::bind( &BackgroundJob::jobBody , this, _status ) );
        return *this;
    }

    bool BackgroundJob::wait( unsigned msTimeOut ) {
		boost::recursive_mutex::scoped_lock l( _status->m );
        while ( _status->state != Done ) {
            if ( msTimeOut ) {
                // add msTimeOut millisecond to current time
                boost::xtime xt;
                boost::xtime_get( &xt, boost::TIME_UTC );

                unsigned long long ns = msTimeOut * 1000000ULL; // milli to nano
                if ( xt.nsec + ns < 1000000000 ) {
                    xt.nsec = (xtime::xtime_nsec_t) (xt.nsec + ns);
                }
                else {
                    xt.sec += 1 + ns / 1000000000;
                    xt.nsec = ( ns + xt.nsec ) % 1000000000;
                }

                if ( ! _status->finished.timed_wait( l , xt ) )
                    return false;

            }
            else {
                _status->finished.wait(l);
            }
        }
        return true;
    }

    BackgroundJob::State BackgroundJob::getState() const {
		boost::recursive_mutex::scoped_lock l( _status->m);
        return _status->state;
    }

    bool BackgroundJob::running() const {
		boost::recursive_mutex::scoped_lock l( _status->m);
        return _status->state == Running;
    }

	}
}