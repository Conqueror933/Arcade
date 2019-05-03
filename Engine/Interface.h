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
//
//#include <vector>
//
//struct DataPass
//{
//	std::vector<char> c;
//	std::vector<int> i;
//	std::vector<double> d;
//	//could also do void* here
//};

/*
either do the 3 vectors, there is no telling what value is where then tho, which might be bad
	-and certainly is bad design

make an std::unordered_map<std::string, union>
*/