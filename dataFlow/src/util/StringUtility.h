#pragma once

#include <string>
#include <vector>

class StringUtility
{
public:
	static void substitute(std::string& _orig, const std::string& _from, const std::string& _to);
	static void Split(const std::string& s, std::vector<std::string>& , const std::string& delim);
	static std::string ToLowerAndTrim(const std::string& s);
	static std::string ToUpperAndTrim(const std::string& s);

};