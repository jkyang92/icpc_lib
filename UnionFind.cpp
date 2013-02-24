#include<iostream>
using namespace std;

int set[100];

int findSet(int querySet)
{
    int i = querySet;
    while(i != set[i])
        i = set[i];
    
    set[querySet] = i;
    return set[querySet];
}

void unionSet(int set1, int set2)
{
    set1 = findSet(set1);
    set2 = findSet(set2);
    if(set1 < set2)
        set[set2] = set1;
    else
        set[set1] = set2;
}

int main()
{
    for(int i = 0; i < 100; i++)
        set[i] = i;
    
    unionSet(5, 6);
    unionSet(8, 0);
    unionSet(2, 3);
    unionSet(4, 5);
    unionSet(1, 6);
    unionSet(1, 2);
    unionSet(9, 4);
    for(int i = 0; i < 10; i++)
        cout << findSet(i) << endl;
    
    return 0;
}
