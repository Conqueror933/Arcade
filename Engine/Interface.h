#pragma once

class Interface
{
public:
	virtual ~Interface() = 0;
	virtual int Update() = 0;
	virtual void Draw() = 0;
};

#include <vector>

struct DataPass
{
	DataPass() = default;
	std::vector<char> c;
	std::vector<int> i;
	std::vector<double> d;

	//could also do void* here
};