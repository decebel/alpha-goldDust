#ifndef DF_JEDI_H
#define DF_JEDI_H

#include "DFFrameWork.h"
#include "JediCouncil.h"
#include <vector>
#include <string>

using namespace std;

namespace DF
{
	namespace Data
	{
		class GraphDataManager;
	}

	namespace Client
	{
		using DF::Data::GraphDataManager;

		typedef boost::shared_ptr<GraphDataManager> SPGraphDataManager;

		class Callback {};

		class DATAFLOW_API_EXPORTS Jedi
		{

		private:	
			string _sName;
			vector<string> _vecPowers;
			SPJediApprenticeIO _spApprenticeIO;
			SPGraphDataManager _spGraphDataManager;
		
		public: // to change back to private. until we know how to use singletons from python
			friend class DF::Client::Internal::JediCouncil;
			Jedi(const string& sJediName, const vector<string>& vecPowers );
			Jedi(const Jedi&) {}
			Jedi& operator = (const Jedi&);

			bool IsValidRequest(const string& sQuestion);
			Jedi();
//		public:
			bool Interested(const string& sQuestion, const Callback& oCallback);	

			/*
				@arg1: What calculation to use
				@arg2: We use the key to figure out what data this calculation is for
				@arg3: Data tag. Can be anything. Represents a "tag" for the data
				@arg4: Expression to query cache for data
				
				Maybe we should combine @arg2 (key), @arg3 (tag) and @arg4(expression) in 
				a single BSON like object.

				Currently we use arg4 (expression) as string until we have BSON exposed 
				to clients.
				
				If Expression is empty, we only do realtime. 
				If Expression is valid, we query cache for data.
				
			*/

			int Ask(const string& sQuestion, const string& sKey, const string& sDataName, const string& sExpression = "" );

			vector<string> GetQuestionPorts(const string& sQuestion);
			//int Connect(const string& sSourceQuestion, const string& outport, const string& sDestQuestion, const string& inport);
			
			int Connect(const string& sSourceQuestion, const string& sDestQuestion);
			int Save(const string& FileName);
			int Load(const string& FileName);
			
			int AddFilter( const std::string &sNodeName, const  string &sStartTime, long lPeriod, const string& sProperty);
			int AttachFilter(const std::string &sFilterName, const std::string &sCalcName);
		   
			bool TakeBreak(const string& sQuestion);
			bool Done(const string& sQuestion);

		};
	}
}

#endif
