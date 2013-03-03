#include <stdio.h>
#include <limits.h>
#include <queue>
#include <map>
#include <algorithm>

#define f(i,n) for(int i=0; i<n; i++)

using namespace std;

typedef map<int,int> node;
const int mn = 100;
node nodes[mn];
int dist[mn];
int prev[mn];
typedef pair<int,int> edge;

struct comp{
	bool operator()(const int a, const int b){
		return dist[a]>dist[b];
	}
};

bool cmp(const int a, const int b){
	return dist[a]>dist[b];
}

void d(int start){
	fill(dist,dist+mn,INT_MAX);
	//priority_queue<edge,vector<edge>,bool (*)(const int, const int)>q(cmp);
	priority_queue<edge,vector<edge>,greater<edge> > q;
	dist[start]=0;
	q.push(edge(0,start));
	while(!q.empty()){
		edge e = q.top();q.pop();
		if(dist[e.second]<e.first)continue;
		int i = e.second;
		for(node::iterator j = nodes[i].begin(); j !=nodes[i].end();j++){
			int to = j->first;
			if(dist[i]+j->second<dist[to]){
				dist[to] = dist[i]+j->second;
				q.push(edge(dist[to],to));
				prev[to] = i;
			}
		}
	}
}

int main()
{
	for_each(nodes, nodes + mn-1, mem_fun_ref(&node::clear));
	
	nodes[0][1]=10;
	nodes[0][2]=2;
	nodes[2][3]=2;
	nodes[3][1]=2;
	d(0);
	printf("%d\n",dist[1]);
}
