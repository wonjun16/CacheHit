#pragma once

#include <list>

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
	bool CacheHit(void*, const int) const;

private:
	std::list<CacheData*>* Cache;
	int Way;
	int TotalIndex;
	int CacheLineSize;

	void Insert(void*, int);
	void Change(void*, int);
	void Delete(void*, int);
};

