#include <cstdio>
#include "limits.h"
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

typedef map<int,int> node;
const int MAXNODES = 305;
node nodes[MAXNODES];
int prev[MAXNODES];
int source = 0, sink = 1, begin = 2;

bool bfs()
{
	fill(prev, prev+MAXNODES, -1);
	queue<int> q;
	q.push(source);
	prev[source] = source;
	while(!q.empty())
	{
		int c = q.front(); q.pop();
		if(c==sink)
			return true;
		node n = nodes[c];
		for(node::iterator i = nodes[c].begin(); i != nodes[c].end(); i++)
		{
			int to = i->first;
			if(nodes[c][to]<=0 || prev[to]>=0)
				continue;
			q.push(to);
			prev[to] = c;
		}
	}

	return false;
}

int update()
{
	int ret = INT_MAX;
	for(int cur = sink, pr = prev[cur]; cur !=source; cur = prev[cur], pr = prev[cur])
	{
		ret = min(ret, nodes[pr][cur]);
	}
	for(int cur = sink, pr = prev[cur]; cur !=source; cur = prev[cur], pr = prev[cur])
			nodes[pr][cur]-=ret, nodes[cur][pr]+=ret;
	return ret;
}

int maxFlow()
{
	int flow=0;
	while(bfs())
	{
		flow+=update();
	}
	return flow;
}

int main()
{
	int t,n,m;
	scanf("%d",&t);
	for(int i=0; i < t; i++)
	{
		for_each(nodes, nodes + MAXNODES-1, mem_fun_ref(&node::clear));

		//ADD EDGES (SAMPLE USAGE)
		scanf("%d",&n);

		int nnums[200], mnums[200];
		for(int j=0; j < n;j++)
		{
			scanf("%d",&(nnums[j]));
			nodes[source][begin+j]=1;
		}

		scanf("%d",&m);

		for(int j=0; j < m;j++)
		{
			scanf("%d",&(mnums[j]));

			nodes[begin+n+j][sink]=1;

			for(int k=0; k < n;k++)
			{
				if(mnums[j]==0 || (nnums[k]>0 && (mnums[j]%nnums[k])==0))
				{
					nodes[begin+k][begin+n+j] = 99999;
				}
			}
		}

		printf("Case %d: %d\n",(i+1), maxFlow());
	}

	return 0;
}