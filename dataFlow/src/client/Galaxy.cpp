#include "RL/Client/Galaxy.h"
#include "RL/Util/StringUtility.h"
#include <functional>
#include <algorithm>


namespace RL
{
	namespace Client
	{
		static string ERRORMSG("ERROR");

		struct QuestionsCacheItemFilter : public unary_function<QuestionsCacheItem, bool>
		{
			string _sQuestionName;
			QuestionsCacheItemFilter(const string& sQName) : _sQuestionName(sQName) {}

			bool operator() (const QuestionsCacheItem& oQCacheItem)
			{
				return oQCacheItem.first.QuestionName() == _sQuestionName ? true : false;
			}
		};
	
		QuestionInfo::QuestionInfo(const string& sQN, const string& sQD) :
			_sQuestionName(sQN),
			_sQuestionDescription(sQD)
			{}

		AnswerInfo::AnswerInfo(const string& sAN, const string& sAD) :
			_sAnswerFunctionName(sAN),
			_sAnswerFunctionDesc(sAD)
			{}


		Galaxy& Galaxy::GALAXY()
		{
			static Galaxy instance;
			return instance;
		}

		bool Galaxy::GetQuestionAnswerInfo(const string& sQuestion, QuestionInfo& oQItem, AnswerInfo& oAItem)
		{
			string sQClean = StringUtility::ToLowerAndTrim(sQuestion);

			QuestionsIter it = find_if(_QuestionsCache.begin(), _QuestionsCache.end(), QuestionsCacheItemFilter(sQClean));
			if(it != _QuestionsCache.end())
			{
				oQItem = (*it).first;
				oAItem = (*it).second;
				return true;
			}

			return false;
		}

		bool Galaxy::HasAnswer(const string& sQuestion)
		{
			QuestionInfo oQItem("", "");
			AnswerInfo oAItem("", "");
			if(GetQuestionAnswerInfo(sQuestion, oQItem, oAItem))
				return true;
			return false;
		}

		const string& Galaxy::AnswerKind(const string& sQuestion)
		{
			QuestionInfo oQItem("", "");
			AnswerInfo oAItem("", "");
			if(GetQuestionAnswerInfo(sQuestion, oQItem, oAItem))
				return oAItem.AnswerName();

			return ERRORMSG;
		}

		const string& Galaxy::AnswerDesc(const string& sQuestion)
		{
			QuestionInfo oQItem("", "");
			AnswerInfo oAItem("", "");
			if(GetQuestionAnswerInfo(sQuestion, oQItem, oAItem))
				return oAItem.AnswerDesc();

			return ERRORMSG;
		}

		vector<string> Galaxy::AllKnownQuestions()
		{
			vector<string> vecQNames;
			QuestionsIter it;
			for(it = _QuestionsCache.begin(); it != _QuestionsCache.end(); it++)
				vecQNames.push_back((*it).first.QuestionName());

			return vecQNames;
		}


	}
}