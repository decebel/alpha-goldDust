#ifndef APPRENTICE_RL_H
#define APPRENTICE_RL_H

#include "DFFrameWork.h"
#include "ClientFwd.h"
#include <string>
#include <boost/noncopyable.hpp>

using namespace std;

namespace DF
{
	namespace Client
	{

		/*
		There is no emotion, there is peace. 
		There is no ignorance, there is knowledge. 
		There is no passion, there is serenity. 
		(There is no chaos, there is harmony.)(*) 
		There is no death, there is the Force. 
		—The Jedi Code (Based on the meditations of Odan-Urr) 
		*/

		struct DATAFLOW_API_EXPORTS JediCode
		{
			string sCodeName;
		};


		class DATAFLOW_API_EXPORTS Apprentice
		{
			string _sName;
			JediCode _oJediCode;
			string _sJediName;

		public:

			Apprentice(const string& sName, const JediCode& oJediCode = JediCode());
			const string& Name() const { return _sName; }
			const JediCode& Code() const { return _oJediCode; }
			const string& GetJediName() const { return _sJediName; }
			void  SetJediName(const string& sJediName) { _sJediName = sJediName; }

		};

	}
}


#endif