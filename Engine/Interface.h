#pragma once

#include <stack>
#include <memory>

class Interface
{
public:
	virtual ~Interface() = 0 {};
	virtual int Update() = 0;
	virtual void Draw(){}
};

#include <vector>

struct DataPass
{
	std::vector<char> c;
	std::vector<int> i;
	std::vector<double> d;

	//could also do void* here
};