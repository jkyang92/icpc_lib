#include <cstdio>
#include "limits.h"
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

typedef map<int,int> node;
const int MAXNODES = 305;
node nodes[MAXNODES];
int minCutSize;
int prev[MAXNODES];
typedef pair<int,int> edge;
vector<edge> minCut;
int source = 0, sink = 1, begin = 2;

//Used to add edges between seperate nodes to a graph that splits nodes int two.
void addEdgeCap(int i, int j, int cap, int nCnt){
	int iOut = begin+nCnt+i;
	int jIn = begin+j;
	nodes[iOut][jIn] = cap;
}

//Used to add an edge between in and out nodes to a graph that splits nodes into two.
void addNodeCap(int i, int cap, int nCnt){
	int iIn = begin+i;
	int iOut = iIn + nCnt;
	nodes[iIn][iOut] = cap;
}

bool bfs(){
	fill(prev, prev+MAXNODES, -1);
	queue<int> q;
	q.push(source);
	prev[source] = source;
	while(!q.empty()){
		int c = q.front(); q.pop();
		if(c==sink)
			return true;
		node n = nodes[c];
		for(node::iterator i = nodes[c].begin(); i != nodes[c].end(); i++){
			int to = i->first;
			if(nodes[c][to]<=0 || prev[to]>=0)
				continue;
			q.push(to);
			prev[to] = c;
		}
	}
	return false;
}

int update(){
	int ret = INT_MAX;
	for(int cur = sink, pr = prev[cur]; cur !=source; cur = prev[cur], pr = prev[cur])
		ret = min(ret, nodes[pr][cur]);
	for(int cur = sink, pr = prev[cur]; cur !=source; cur = prev[cur], pr = prev[cur])
			nodes[pr][cur]-=ret, nodes[cur][pr]+=ret;
	return ret;
}

int maxFlow(){
	int flow;
	for(flow=0; bfs(); flow+=update()){}
	return flow;
}


void minCutBfs()
{
	bool marked[MAXNODES];
	fill(marked,marked+MAXNODES,false);
	minCut.clear();
	queue<int> q;
	q.push(source);
	while(!q.empty()){
		int c = q.front(); q.pop();
		node n = nodes[c];
		for(node::iterator i = nodes[c].begin(); i != nodes[c].end(); i++){
			int to = i->first;
			if(nodes[c][to]>0 && !marked[to]){
				q.push(to);
				marked[to] = true;
			}
			else if (!marked[to]){
				minCut.push_back(edge(c,to));
			}
		}
	}

	for(unsigned int i=0;i<minCut.size();i++)
		if(!marked[minCut[i].second] )
			printf("%d %d\n",minCut[i].first-begin+1,minCut[i].second-begin+1);//NOTE: using 1,n, not 0,n-1
	printf("\n");
}

int main()
{
	int t,n,m;
	scanf("%d",&t);
	for(int i=0; i < t; i++)
	{
		for_each(nodes, nodes + MAXNODES-1, mem_fun_ref(&node::clear)); //NEEDED

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
					nodes[begin+k][begin+n+j] = INT_MAX;
				}
			}
		}

		printf("Case %d: %d\n",(i+1), maxFlow());
		printf("Min Cut: ");
		minCutBfs();
	}

	return 0;
}
