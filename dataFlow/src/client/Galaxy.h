#ifndef GALAXY_RL_H
#define GALAXY_RL_H

#include "ClientFwd.h"

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/unordered_map.hpp>
#include <boost/functional/hash.hpp>

using namespace boost;
using namespace std;

namespace RL
{
	namespace Client
	{
		class QuestionInfo
		{

		private:

			string _sQuestionName;
			string _sQuestionDescription;

		public:

			friend std::size_t hash_value(QuestionInfo const& p)
			{
				std::size_t seed = 0;
				boost::hash_combine(seed, p._sQuestionName);
				boost::hash_combine(seed, p._sQuestionDescription);
				return seed;
			}
			QuestionInfo(const string& sQN, const string& sQD);

			const string& QuestionName() const { return _sQuestionName; }
			const string& QuestionDesc() const { return _sQuestionDescription; }
		};

		class AnswerInfo
		{

		private:

			string _sAnswerFunctionName;
			string _sAnswerFunctionDesc;

		public:

			AnswerInfo(const string& sAN, const string&
				sAD);

			const string& AnswerName() { return _sAnswerFunctionName; }
			const string& AnswerDesc() { return _sAnswerFunctionDesc; }
		};

		struct Question
		{
			Question(const string& sMarketName);

		};

		class Answer
		{
			// callback method
			// siganl 
			// connector for blocking etc..
		};

		typedef unordered_map<QuestionInfo, AnswerInfo, boost::hash<QuestionInfo> > QuestionsCache;			
		typedef QuestionsCache::iterator QuestionsIter;
		typedef QuestionsCache::value_type QuestionsCacheItem;
		typedef unordered_map<string, Answer> AnswerCache;

		class Galaxy : boost::noncopyable
		{
		private:
						
			AnswerCache _AnswersInProgress;
			QuestionsCache _QuestionsCache;
			bool GetQuestionAnswerInfo(const string& sQuestion, QuestionInfo& oQItem, AnswerInfo& oAItem);

			
		public:
			static Galaxy& GALAXY();
			
			bool HasAnswer(const string& sQuestion);
			const string& AnswerKind(const string& sQuestion);
			const string& AnswerDesc(const string& sQuestion);
			vector<string> AllKnownQuestions();	

			vector<string> ApprenticesToJedi(const string& sJedi);





		};

	}
}

#endif