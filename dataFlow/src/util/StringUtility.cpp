#include "StringUtility.h"
#include <boost/algorithm/string.hpp>
using namespace boost;

void StringUtility::substitute(std::string& _orig, const std::string& _from, const std::string& _to)
{
	//std::string::iterator it1 = _orig.begin();
	//std::string::iterator it2 = _orig.begin();

	size_t offSet = _orig.find(_from);
	if(offSet != std::string::npos)
	{
		//it1 += offSet;
		//it2 = it1 + _from.length();

	_orig.replace(offSet, _from.length(), _to);

	}
}

void StringUtility::Split(const std::string& _s, std::vector<std::string>& _ret, const std::string& _delim)
{
	size_t last = 0;
	for(int i = 0; i + _delim.size() <= _s.size(); i++)
	{
		bool ok = true;
		for(size_t j = 0; j < _delim.size() && ok; j++)
			ok = _s[i + j] == _delim[j];
		if(ok)
		{
			if(i - last) _ret.push_back(_s.substr(last, i - last));
			last = i + _delim.size();
		}
	}
	if(last < _s.size()) _ret.push_back(_s.substr(last));
	return;
}

std::string StringUtility::ToLowerAndTrim(const std::string& s)
{
	std::string lstr = to_lower_copy(s);
	trim(lstr);
	return lstr;
}

std::string StringUtility::ToUpperAndTrim(const std::string& s)
{
	std::string ustr = to_upper_copy(s);
	trim(ustr);
	return ustr;
}