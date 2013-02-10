#include<iostream>
#include<malloc.h>
#include<queue>
using namespace std;

struct node
{
	int numIncoming;
	int numOutgoing;
	int next[101];
	
	node (): numIncoming(0), numOutgoing(0){}
};

bool exists[26];

int *topSort(node nodes[], int &length, bool &ambiguous)
{
	int *toReturn = (int *)malloc(30 * sizeof(int));
	int index = 0;
	
	queue<int> q;
	for(int i = 0; i < 26; i++)
	{
		if(exists[i])
		{
			if(nodes[i].numIncoming == 0)
			{
				q.push(i);
				break;
			}
		}
	}
	
	while(!q.empty())
	{
		int popped = q.front();
		q.pop();
		//cout << (char)(popped + 'A') << endl;
		toReturn[index++] = popped;
		
		node &curr = nodes[popped];
		for(int i = 0; i < curr.numOutgoing; i++)
		{
			node &nextNode = nodes[curr.next[i]];
			nextNode.numIncoming--;
			if(nextNode.numIncoming == 0)
				q.push(curr.next[i]);
		}
	}
	
	length = index;
	if(length < 9)
	{
		//cout << length << endl;
		ambiguous = true;
	}
	for(int i = 0; i < 26; i++)
	{
		if(exists[i])
		{
			if(nodes[i].numIncoming != 0)
			{
				ambiguous = true;
				break;
			}
		}
	}
	
	return toReturn;
}

int main()
{
	string arr;
	
	int numStrings;
	cin >> numStrings;
	
	for(int t = 1; numStrings != 0; t++)
	{
		node nodes[26];
		
		for(int i = 0; i < 26; i++)
			exists[i] = false;
			
		for(int i = 0; i < numStrings; i++)
		{
			cin >> arr;
			//cout << arr << endl;
			exists[arr[0] - 'A'] = true;
			for(int j = 1; arr[j] != '\0'; j++)
			{
				exists[arr[j] - 'A'] = true;
				
				int nodeIndex = arr[j-1] - 'A';
				//cout << (char)(arr[j-1]) << endl;
				node &prev = nodes[nodeIndex];
				prev.next[prev.numOutgoing] = arr[j] - 'A';
				prev.numOutgoing++;
				
				//cout << (char)(arr[j]) << endl;
				node &curr = nodes[arr[j] - 'A'];
				curr.numIncoming++;
			}
		}
		
		int length = 0;
		bool ambiguous = false;
		int *answer = topSort(nodes, length, ambiguous);
		
		cout << "Case " << t << ":" << endl;
		if(ambiguous)
		{
			cout << "   Ambiguous" << endl;
		}
		else
		{
			cout << "   ";
			for(int i = 1; i < 10; i++)
			{
				cout << i << " ";
			}
			cout << endl;
			
			cout << "   ";
			for(int i = 0; i < length; i++)
			{
					cout << (char)(answer[i] + 'A') << " ";
			}
			cout << endl;
		}
		cout << endl;
		free(answer);
		
		cin >> numStrings;
	}
	
	return 0;
}
