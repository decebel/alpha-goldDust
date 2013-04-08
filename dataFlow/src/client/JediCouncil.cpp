#include "JediCouncil.h"
#include "Apprentice.h"
#include "Jedi.h"
#include <vector>
#include <algorithm>

namespace DF
{
	namespace Client
	{
		namespace Internal
		{
			
			const char *chrJNames[] ={
				"Janu", "Nabu",
				"MasterLuke", "Obiwan",
				"SkyWalker", "Odan",
				"Mermit", "Ooroo", NULL
			};

			class JediNamePool
			{
			private:
				vector<string> vecJediNames;
				int iAvailableIndex;				

			public:
				JediNamePool() : iAvailableIndex(-1){}
				
				JediNamePool(const char* names[], int count = 8) :
				iAvailableIndex(-1)
				{
					for(int i=0; i<count; i++)
					{
						if(names[i] != NULL)
							vecJediNames.push_back(string(names[i]));
					}

					if(vecJediNames.size() > 0)
						iAvailableIndex = 0;
					
				}

				static JediNamePool& Default()
				{
					static JediNamePool instance(chrJNames);
					return instance;
				}

				void Add(const string& sName) { vecJediNames.push_back(sName); }

				bool IsJediAvailable(string& sJediName)
				{
					if((iAvailableIndex < 0) || (iAvailableIndex == vecJediNames.size()-1)) 
						return false;

					sJediName = vecJediNames.at(iAvailableIndex);
					return true;
				}

				bool Exists(const string& sJediName)
				{
					vector<string>::iterator it = find(vecJediNames.begin(), vecJediNames.end(), sJediName);
					return (it != vecJediNames.end()) ? true : false;
				}

			};
			
			SPJedi JediCouncil::CreateJedi(const string& sJediName, const Apprentice& oApp)
			{			
				SPJedi spJedi(new Jedi(sJediName, JediPowers(oApp.Code())));				
				return spJedi;
			}


			// TODO:
			// 1. JediPower object instead of simple string
			// 2. Add some intelligence based on code and user history to decide what powers to provide
			vector<string> JediCouncil::JediPowers(const JediCode& oJediCode)
			{
				vector<string> vecPowers;
				vecPowers.push_back("PortReaperTester");
				vecPowers.push_back("BMCalculator");
				vecPowers.push_back("Checker");
				return vecPowers;
			}


			JediCouncil& JediCouncil::GetJediCouncil()
			{
				static JediCouncil instance;
				return instance;
			}

			SPJedi JediCouncil::GetJedi(const Apprentice& oApprentice)
			{
				SPJedi spJedi;
				string sJediName;

				CacheType::iterator it = _Cache.find(oApprentice.GetJediName());

				/* return if we have found the item */
				if(it != _Cache.end())
					return (*it).second;

				/* no more available */
				if(!JediNamePool::Default().IsJediAvailable(sJediName))
					return spJedi;

				//TODO:
				//oApprentice.SetJediName(sJediName);

				/* now create if not found */
				if(it == _Cache.end())
				{
					spJedi = CreateJedi(sJediName, oApprentice);
					_Cache.insert(make_pair(sJediName, spJedi));
					return spJedi;
				}
				
				return spJedi;				
			}

			vector<string> JediCouncil::GetJediNames()
			{
				vector<string> vNames;
				CacheType::iterator it = _Cache.begin();
				while(it != _Cache.end())				
					vNames.push_back((*it).first);
				
				return vNames;
			}
		}
	}
}