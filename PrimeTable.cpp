#include<iostream>
#include<malloc.h>
using namespace std;

bool *generatePrimeTable(int limit)
{
	limit++;
	bool *primeTable = (bool *)malloc(limit * sizeof(bool));
	for(int i = 0; i < limit; i++)
		primeTable[i] = true;
	primeTable[0] = false;
	primeTable[1] = false;
	
	for(int i = 2; i < limit; i++)
	{
		if(primeTable[i])
			for(int j = 2*i; j < limit; j += i)
				primeTable[j] = false;
	}
	
	return primeTable;
}

int main()
{
	int limit = 46340; //sqrt(2^31 - 1)
	cout << "limit = " << limit << endl;
	bool *primes = generatePrimeTable(limit);
	/*
	for(int i = 0; i < limit; i++)
		if(primes[i])
			cout << i << endl;
	*/
	
	return 0;
}
