#include "L1.h"

L1::L1()
{
	this->CacheLineSize = 64;
	this->Way = 8;
	this->TotalIndex = 64;
	this->Cache = std::vector<std::list<CacheData*>>();
	for (int i = 0; i < TotalIndex; i++)
	{
		std::list<CacheData*> data;
		Cache.push_back(data);
	}
}

L1::~L1()
{
	
}

bool L1::CacheHit(void* _address, const int _size)
{
	if (_size > this->CacheLineSize)
	{
		//�Ϻθ� hit�϶�?
		L1::CacheHit(_address, this->CacheLineSize);
		L1::CacheHit((void*)((int)_address + this->CacheLineSize), _size - this->CacheLineSize);
	}

	bool Hit = false;
	//32bit ����
	const unsigned int CacheLineAds = (unsigned int)_address & 0xffffffc0;

	const unsigned int _Index = (CacheLineAds & 0x00000fc0) >> 6;
	const unsigned int _Tag = CacheLineAds & 0xfffff000;

	//�ε��� ã�Ƽ� �ش� �ε��� ��ȸ�ϸ� tag��, ������ insert, ������ true��ȯ, ���µ� �� �������� change(���� ������ ����� ������)
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
			//���� ������ ������ �ε��� ã��
			Change(0, _Tag);
		}
		else
		{
			Insert(_Index, _Tag);
		}
	}

	return Hit;
}

void L1::Insert(const int _Index, const int _Tag)
{
	CacheData* data = new CacheData();
	data->Tag = _Tag;
	data->Flag = 1;
	Cache[_Index].push_back(data);
}

void L1::Change(const int _Index, const int _Tag)
{
	Cache[_Index].front()->Tag = _Tag;
}