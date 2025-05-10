#include "L1.h"
#include <iostream>

using namespace std;

int main()
{
	L1* l1 = new L1();

	int a = 1;
	int b = 2;
	int c[65] = { 0, };
	int d = 3;
	long long e = 4;
	short f = 5;
	bool c1 = l1->CacheHit(&a, sizeof(int));
	bool c2 = l1->CacheHit(&b, sizeof(int));
	bool c3 = l1->CacheHit(&d, sizeof(int));
	bool c4 = l1->CacheHit(&e, sizeof(long long));
	bool c5 = l1->CacheHit(&f, sizeof(short));
	cout << c1 << '\n';
	cout << c2 << '\n';
	cout << c3 << '\n';
	cout << c4 << '\n';
	cout << c5 << '\n';
}