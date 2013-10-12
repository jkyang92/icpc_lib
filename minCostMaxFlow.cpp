#include <stdio.h>
#include <map>
#include <limits.h>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

#define f(i,n) for(int i =0;i<n;i++)
#define fi(i,t,n) for(t::iterator i=n.begin(); i!=n.end();i++)

#define indx(i) (::begin+(i))
//COST LINE NOT NEEDED FOR MAX FLOW
#define addE(i,j,cap,cos) do{\
	nodes[i][j]=cap; nodes[j][i]=0;\
	cost[i][j]=cos;  cost[j][i]=-(cos);\
}while(false)
#define loopP() for(int c=sink, p=prevs[c]; c!=source; c=p, p=prevs[p])
#define clearN(i) for_each(i,i+mn,mem_fun_ref(&node::clear))
typedef long long ll;
const ll big = 1E17;
const int mn = 300;//MAX NODES
typedef map<int,int> node;//stores [to,cap]
node nodes[mn];
int prevs[mn];
ll pot[mn];//previous,potential
typedef pair<ll,int> edg;//edge, stores [cost,to]
int source=0, sink=1, begin=2, nnodes;//# of nodes (set at runtime)
//BEGIN NOT NEEDED FOR MAX FLOW//
node reCost[mn],cost[mn];//reducedCost, cost.
void reduce(){
	f(i,nnodes)
		fi(k,node,nodes[i]){
			int j = k->first;
			if(k->second>0){
				reCost[i][j] += pot[i] - pot[j];
				reCost[j][i]=0;
			}
		}
}
//END NOT NEEDED FOR MAX FLOW//
int d(){
	fill(prevs,prevs+nnodes,-1);
	fill(pot, pot+nnodes, big);
	priority_queue<edg, vector<edg>, greater<edg> >q;//FOR MF, YOU CAN USE JUST A QUEUE OF INTS
	pot[source] = 0;
	q.push(edg(0,source));
	while(!q.empty()){
		edg c = q.top();q.pop();
		int cur = c.second, cost = c.first;
		if(cur==sink)return pot[sink];
		if(pot[cur] < cost)continue;
		fi(i,node,nodes[cur]){//iterate for begin to end
			int to = i->first;
			if(i->second<=0)continue;
			if(pot[to] <= reCost[cur][to] + pot[cur])continue;
			pot[to] = pot[cur]+reCost[cur][to];
			q.push(edg(pot[to],to));
			prevs[to] = cur;
		}
	}
	reduce();
	return -1;
}

int update(ll &cst, int left){
	int flow = INT_MAX;
	loopP() {flow = min(flow, nodes[p][c]);}
	flow = min(left,flow);
	loopP() {nodes[p][c] -= flow; nodes[c][p] += flow; cst += cost[p][c] * flow;}//cst+= NOT NEEDED FOR MF
	return flow;
}

int maxFlow(ll& c, int dd){
	c=0;//c=cost,	//BEGIN NOT NEEDED FOR MF
	fill(pot, pot+nnodes, big);
	copy(cost, cost+nnodes, reCost);
	pot[source]=0;
	f(k,nnodes)
		f(i,nnodes){
			fi(j,node,nodes[i]){
				int to = j->first;
				if(j->second>0)//make sure the edge is not a backwards residual edge in the graph.
					pot[to] = min (pot[to], pot[i]+cost[i][to]);
			}
		}
	reduce();//END NOT NEEDED FOR MF//
	int flow=0, left = dd;
	while(d()>=0 && left>0){int f=update(c,left);flow+=f;left-=f;}
	return flow;
}


int main(){//addE(i,j,cap,cost)
	while(true){//n=num postings, m=num people
		int n,m;
		clearN(nodes);
		clearN(reCost);//NOT NEEDED FOR MF
		if(scanf("%d %d",&n,&m)==EOF)return 0;

		nnodes = 2*n+2;
		int graph[100][100];
		f(i,n)f(j,n)graph[i][j]=-1;
		//printf("reading graph\n");
		f(i,m){
			int a,b,cos;
			scanf("%d %d %d",&a,&b,&cos);
			graph[a-1][b-1]=cos;
		}
		int k,d;
		scanf("%d %d",&d,&k);
		//printf("adding edges\n");
		f(i,n)
			addE(indx(i),indx(n+i),k,0);
		f(i,n)
			f(j,n)
				if(graph[i][j]!=-1){
					addE(indx(n+i),indx(j),k,graph[i][j]);
					addE(indx(j+n),indx(n),k,graph[i][j]);
					//printf("adding from %d to %d and %d to %d and %d to %d\n",i,j,j,n+i*n+j,n+i*n+j,i);
				}
		addE(source,indx(0),1E9,0);
		addE(indx(n-1),sink,1E9,0);
		ll cst;
		//printf("starting mf\n");
		int flow = maxFlow(cst,d);
		if(flow==d)
			printf("%d\n",cst);
		else
			printf("Impossible.\n");
	}
	return 0;
}
