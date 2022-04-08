#pragma once
#include <string>
#include <vector>
#include <algorithm>

struct Dight
{
	char dight;
	int pos;
};

class PuzzleLock
{
private:
	static std::string password;
public:
	static std::vector<std::string> getQuestion();
	static std::string getResult();
};

