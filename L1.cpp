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
		//�Ϻθ� hit�϶�?
		L1::CacheHit(_address, this->CacheLineSize);
		L1::CacheHit((void*)((int)_address + this->CacheLineSize), _size - this->CacheLineSize);
	}

	bool Hit = false;
	//32bit ����
	const int CacheLineAds = (int)_address & 0xffffffc0;

	//�ε��� ã�Ƽ� �ش� �ε��� ��ȸ�ϸ� tag��, ������ insert, ������ true��ȯ, ���µ� �� �������� change(���� ������ ����� ������)
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
