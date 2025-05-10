#pragma once

#include <list>
#include <vector>

struct CacheData
{
	int Tag;
	int Flag;
};

class L1
{
public:
	L1();
	~L1();
	bool CacheHit(void*, const int);

private:
	std::vector<std::list<CacheData*>> Cache;
	int Way;
	int TotalIndex;
	int CacheLineSize;

	void Insert(const int, const int);
	void Change(const int, const int);
};

