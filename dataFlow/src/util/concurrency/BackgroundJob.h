#ifndef BACKGROUND_RL_H
#define BACKGROUND_RL_H

#include "DFFramework.h"
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <string>

using namespace std;

namespace DF
{
	namespace Concurrency
	{

		class DATAFLOW_API_EXPORTS BackgroundJob : boost::noncopyable {
		protected:
			/**
			* sub-class must intantiate the BackgrounJob
			*
			* @param selfDelete if set to true, object will destruct itself after the run() finished
			* @note selfDelete instantes cannot be wait()-ed upon
			*/
			explicit BackgroundJob(bool selfDelete = false);

			virtual string name() const = 0;

			/**
			* define this to do your work.
			* after this returns, state is set to done.
			* after this returns, deleted if deleteSelf true.
			*
			* NOTE:
			*   if run() throws, the exception will be caught within 'this' object and will ultimately lead to the
			*   BackgroundJob's thread being finished, as if run() returned.
			*
			*/
			virtual void run() = 0;

		public:
			enum State {
				NotStarted,
				Running,
				Done
			};

			virtual ~BackgroundJob() { }

			/**
			* starts job.
			* returns immediatelly after dispatching.
			*
			* @note the BackgroundJob object must live for as long the thread is still running, ie
			* until getState() returns Done.
			*/
			BackgroundJob& go();

			/**
			* wait for completion.
			*
			* @param msTimeOut maximum amount of time to wait in millisecons
			* @return true if did not time out. false otherwise.
			*
			* @note you can call wait() more than once if the first call times out.
			* but you cannot call wait on a self-deleting job.
			*/
			bool wait( unsigned msTimeOut = 0 );

			// accessors
			State getState() const;
			bool running() const;

		private:
			struct JobStatus;
			boost::shared_ptr<JobStatus> _status;  // shared between 'this' and body() thread

			void jobBody( boost::shared_ptr<JobStatus> status );

		};
	}
}
#endif