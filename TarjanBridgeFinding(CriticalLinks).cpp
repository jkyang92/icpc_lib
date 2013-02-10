#include<iostream>
#include<malloc.h>
#include<cstring>
#include<cstdlib>
#include<climits>
using namespace std;

int numServers = 0;
int numEdges = 0;

char *color;
int *disc;
int *low;
int *parent;

typedef struct node
{
	int *neighbors;
	int numNeighbors;
} node;

node **allServers = NULL;

node *createNode()
{
	node *newnode = new node;
	newnode -> numNeighbors = 0;
	
	return newnode;
}

int timer = 0;
int **bridges = NULL;
int numBridges = 0;

void DFS(int source, int u)
{
	node *unode = allServers[u];
	parent[u] = source;
	
	disc[u] = timer++;
	color[u] = 'G';
	low[u] = disc[u];
	
	for(int i = 0; i < (unode -> numNeighbors); i++)
	{
		int v = (unode -> neighbors)[i];
		
		if(v == parent[u])
			continue;
		
		if(color[v] == 'W')
		{
			DFS(u, v);
			
			if(disc[u] < low[v])
			{
				bridges[numBridges][0] = min(u, v);
				bridges[numBridges][1] = max(u, v);
				numBridges++;			 
			}
			else
			{
				low[u] = min(low[u], low[v]);
			}
		}
		else if(color[v] == 'G')
		{
			low[u] = min(low[u], disc[v]);
		}
		else if(color[v] == 'B')
		{
			low[u] = min(low[u], low[v]);
		}
	}
	
	color[u] = 'B';
}

void findBridges()
{
	bridges = (int **)malloc(numEdges * sizeof(int *));
	numBridges = 0;
	
	for(int i = 0; i < numEdges; i++)
		bridges[i] = (int *)malloc(2 * sizeof(int));
	
	for(int i = 0; i < numServers; i++)
		if(color[i] == 'W')
			DFS(-1, i);
	
}

int main()
{
	
	while(cin >> numServers)
	{
		numEdges = 0;
		timer = 0;
		allServers = (node **)malloc(numServers * sizeof(node *));
		
		color = (char *)malloc(numServers * sizeof(char));
		disc = (int *)malloc(numServers * sizeof(int));
		low = (int *)malloc(numServers * sizeof(int));
		parent = (int *)malloc(numServers * sizeof(int));
		
		for(int i = 0; i < numServers; i++)
		{
			color[i] = 'W';
			disc[i] = INT_MAX;
			low[i] = INT_MAX;
		}
		
		for(int i = 0; i < numServers; i++)
		{
			int server;
			cin >> server;
			allServers[server] = createNode();
			
			char strNumNeighbors[20];
			cin >> strNumNeighbors;
			
			strNumNeighbors[strlen(strNumNeighbors) - 1] = '\0';
			char *temp = strNumNeighbors + 1;
			
			int numNeighbors = atoi(temp);
			numEdges += numNeighbors;
			
			//cout << server << " - " << numNeighbors << ": ";
			
			allServers[server] -> numNeighbors = numNeighbors;
			allServers[server] -> neighbors = (int *)malloc(numNeighbors * sizeof(int));
			
			for(int j = 0; j < numNeighbors; j++)
			{
				cin >> (allServers[server] -> neighbors)[j];
				//cout << (allServers[server] -> neighbors)[j] << " ";
			}
			
			//cout << endl;
		}
		
		findBridges();
		
		for(int i = 0; i < numBridges; i++)
		{
			for(int j = i + 1; j < numBridges; j++)
			{
				if(bridges[i][0] > bridges[j][0])
				{
					int temp = bridges[i][0];
					bridges[i][0] = bridges[j][0];
					bridges[j][0] = temp;
					temp = bridges[i][1];
					bridges[i][1] = bridges[j][1];
					bridges[j][1] = temp;
				}
				else if(bridges[i][0] == bridges[j][0])
				{
					if(bridges[i][1] > bridges[j][1])
					{
						int temp = bridges[i][0];
						bridges[i][0] = bridges[j][0];
						bridges[j][0] = temp;
						temp = bridges[i][1];
						bridges[i][1] = bridges[j][1];
						bridges[j][1] = temp;
					}
				
				}
			}
		}
		
		cout << numBridges << " critical links" << endl;
		for(int i = 0; i < numBridges; i++)
		{
			cout << bridges[i][0] << " - " << bridges[i][1] << endl;
		}
		cout << endl;
		
		for(int i = 0; i < numServers; i++)
		{
			delete(allServers[i] -> neighbors);
			delete(allServers[i]);
		}
	}
	
	return 0;
}
