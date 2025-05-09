#include "L1.h"

L1::L1()
{
	this->CacheLineSize = 64;
	this->Way = 8;
	this->TotalIndex = 64;
	this->Cache = new std::list<CacheData*>(TotalIndex);
}

L1::~L1()
{
	delete[] Cache;
}

bool L1::CacheHit(void* _address, const int _size) const
{
	if (_size > this->CacheLineSize)
	{
		//일부만 hit일땐?
		L1::CacheHit(_address, this->CacheLineSize);
		L1::CacheHit((void*)((int)_address + this->CacheLineSize), _size - this->CacheLineSize);
	}

	bool Hit = false;
	//32bit 기준
	const int CacheLineAds = (int)_address & 0xffffffc0;

	//인덱스 찾아서 해당 인덱스 순회하며 tag비교, 없으면 insert, 있으면 true반환, 없는데 꽉 차있으면 change(가장 이전에 사용한 데이터)
	const int _Index = CacheLineAds & 0x00000fc0;
	const int _Tag = CacheLineAds & 0xfffff000;

	auto Target = Cache[_Index].begin();
	int CurSize = 0;
	while (Target != Cache[_Index].end())
	{
		if ((*Target)->Tag == _Tag)
		{
			Hit = true;
			break;
		}
		Target++;
		CurSize++;
	}

	if (Target == Cache[_Index].end())
	{
		if (CurSize >= Way)
		{
			//change
		}
		else
		{
			//insert
		}
	}

	return Hit;
}

void L1::Insert(void*, int)
{
}

void L1::Change(void*, int)
{
}

void L1::Delete(void*, int)
{
}
