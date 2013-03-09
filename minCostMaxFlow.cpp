#include <stdio.h>
#include <map>
#include <limits.h>
#include <queue>
#include <algorithm>
using namespace std;

#define f(i,n) for(int i =0;i<n;i++)
#define fi(i,t,n) for(t::iterator i=n.begin(); i!=n.end();i++)

const int mn = 900;//MAX NODES
typedef map<int,int> node;
node nodes[mn];
int prev[mn];
int potential[mn];
node reCost[mn];
node cost[mn];
typedef pair<int,int> edge;
int source=0, sink=1, begin=2;

void addEdge(int i, int j, int cap, int c, int nnodes){
    int iOut = begin+nnodes+i;
    int jIn = begin+j;
    nodes[iOut][jIn]=cap;
    cost[iOut][jIn] = c;
    nodes[jIn][iOut] = 0;
    cost[jIn][iOut] = -c;
}
//NOTE: EDGES FROM SOURCE GO STRAIGHT TO OUT NODES OF I.
void addFromSource(int i, int cap, int nnodes){
    int iIn = begin+i+nnodes;
    nodes[source][iIn] = cap;
    nodes[iIn][source] = 0;
    cost[iIn][source] = 0;
    cost[source][iIn] = 0;
}

void addToSink(int i, int cap,int nnodes){    
    int iOut = begin+i+nnodes;
    nodes[iOut][sink] =  cap;
    nodes[sink][iOut] =  0;
    cost[iOut][sink] = 0;
    cost[sink][iOut] = 0;
}

void addBetweenNodes(int i, int cap, int c, int nnodes){
    int iIn = begin+i;
    int iOut= begin+i+nnodes;
    nodes[iIn][iOut] = cap;
    nodes[iOut][iIn] = 0;
    cost[iIn][iOut] = c;
    cost[iOut][iIn] = -c;
}

void reduce(){
    f(i,mn)
    	fi(j,node,nodes[i]){
    		edge e = *j;
    		if(e.first!=0)
    			reCost[i][e.first] += potential[i] - potential[e.first];
    	}
}

int d(){
    reduce();
    fill(prev,prev+mn,-1);
    fill(potential, potential+mn, INT_MAX);
    priority_queue<edge, vector<edge>, greater<edge> >q;
    potential[source] = 0;
    q.push(edge(0,source));
    while(!q.empty()){
    	edge c = q.top();q.pop(); int cur = c.second, cost = c.first;
    	if(potential[cur] < cost)continue;
    	fi(i,node,nodes[cur]){
    		edge e = *i;
    		if(nodes[cur][e.first]<=0)continue;
    		if(potential[e.first] - reCost[cur][e.first] <= potential[cur])continue;
    		potential[e.first] = potential[cur]+reCost[cur][e.first];
    		q.push(edge(potential[e.first],e.first));
    		prev[e.first] = cur;
    	}
    }
    return potential[sink];
}

int update(int &cst){
    int ret = INT_MAX;
        for (int c = sink, p = prev[c]; c != source; c = p, p = prev[c])
                ret = min(ret, nodes[p][c]);
        for (int c = sink, p = prev[c]; c != source; c = p, p = prev[c])
                cst += cost[p][c] * ret, nodes[p][c] -= ret, nodes[c][p] += ret;
    	return ret;	
}

int maxFlow(int& c)
{
    int flow=0; c=0;//c=cost
    fill(potential, potential+mn, INT_MAX/2);
    copy(cost, cost+mn, reCost);
    potential[source]=0;
    f(k,mn)
        f(i,mn)
    	fi(j,node,nodes[i])
    	    if(j->second > 0)
    		potential[j->first] = min (potential[j->first], potential[i]+cost[i][j->first]);
    while(d()<INT_MAX)flow+=update(c);
    return flow;
}

int m;
int ind(int i,int j){
    return i*m+j;
}

int main(){
    for_each(nodes,nodes+mn,mem_fun_ref(&node::clear));//NEEDED TO CLEAR
    for_each(reCost,reCost+mn,mem_fun_ref(&node::clear));//NEED TO CLEAR
    return 0;
}
