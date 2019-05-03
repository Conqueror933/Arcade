#pragma once

#include <unordered_map>
#include <string>
#include <assert.h>

template<class Union>
class StringSwitch
{
public:
	void AddEntry(std::string s, Union u)
	{
		assert(map.find(s) == map.end());
		map.emplace(s, u);
	}
	void ChangeEntry(std::string s, Union u)
	{
		assert(!(map.find(s) == map.end()));
		map.insert_or_assign(s, u);
	}
	Union GetValue(std::string s)
	{
		assert(!(map.find(s) == map.end()));
		return map.at(s);
	}
	void Flush()
	{
		map.clear();
	}

private:
	std::unordered_map<std::string, Union> map;
};

union DataPass
{
	DataPass(char c) : c(c) {}
	DataPass(int i) : i(i) {}
	DataPass(double d) : d(d) {}
	int i;
	char c;
	double d;
};