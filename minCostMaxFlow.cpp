#include <stdio.h>
#include <map>
#include <limits.h>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

#define f(i,n) for(int i =0;i<n;i++)
#define fi(i,t,n) for(t::iterator i=n.begin(); i!=n.end();i++)

#define outI(i) (::begin+nnodes+(i))
#define indx(i) (::begin+(i))
//COST LINE NOT NEEDED FOR MAX FLOW
#define addE(i,j,cap,cos) do{\
	nodes[i][j]=cap; nodes[j][i]=0;\
	cost[i][j]=cos;  cost[j][i]=-(cos);\
}while(false)
#define loopP() for(int c=sink, p=prevs[c]; c!=source; c=p, p=prevs[c])
#define clearN(i) for_each(i,i+mn,mem_fun_ref(&node::clear))

const int mn = 300;//MAX NODES
typedef map<int,int> node;//stores [to,cap]
node nodes[mn];
int prevs[mn],pot[mn];//previous,potential
typedef pair<int,int> edg;//edge, stores [cost,to]
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
	fill(pot, pot+nnodes, INT_MAX/2);
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

int update(int &cst){
	int ret = INT_MAX;
	loopP() {ret = min(ret, nodes[p][c]);}
	loopP() {nodes[p][c] -= ret; nodes[c][p] += ret; cst += cost[p][c] * ret;}//cst+= NOT NEEDED FOR MF
	return ret;
}

int maxFlow(int& c){
	c=0;//c=cost,	//BEGIN NOT NEEDED FOR MF
	fill(pot, pot+nnodes, INT_MAX/2);
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
	int flow=0;
	int loop = 0;
	while(d()>=0 && loop<1000){loop++;flow+=update(c);}
	return flow;
}

int main(){//addE(i,j,cap,cost)
	while(true){//n=num postings, m=num people
		int n,m;
		clearN(nodes);
		clearN(reCost);//NOT NEEDED FOR MF
		scanf("%d %d",&n,&m);
		nnodes = n+m+2;
		if(n==0&&m==0)
			return 0;
		f(i,n){
			int pos;
			scanf("%d",&pos);
			addE(source,indx(i),pos,0);
		}
		int co[3][4]={{4,3,2,1},{8,7,6,5},{12,11,10,9}};
		f(i,m){
			int y,cs[4];
			scanf("%d %d %d %d %d",&y,cs,cs+1,cs+2,cs+3);
			f(j,4)
				addE(indx(cs[j]),indx(n+i),1,-co[y-1][j]);
			addE(indx(n+i),sink,1,0);
		}
		int cst;
		maxFlow(cst);
		printf("%d\n",-cst);
	}

	/*
	   nnodes = 5;

	   addE(source,indx(0),5,0);
	   addE(indx(0),indx(1),7,1);
	   addE(indx(0),indx(2),7,5);
	   addE(indx(1),indx(2),2,-2);
	   addE(indx(1),indx(3),3,8);
	   addE(indx(2),indx(3),3,-3);
	   addE(indx(3),sink,3,0);
	   addE(indx(2),indx(4),2,4);
	   addE(indx(4),sink,2,0);

	   int cost,mf;
	   mf=maxFlow(cost);
	   printf("cost:%d %d\n",cost,mf);
	   */	return 0;
}
