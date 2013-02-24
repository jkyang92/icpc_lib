#include <stdio.h>
#include <algorithm>

using namespace std;

const int MAXNODES = 600;
bool nodes[MAXNODES][MAXNODES];
int prev[MAXNODES];
int next[MAXNODES];
bool vis[MAXNODES];

#define f(i,n) for(int i =0; i<n;i++)

int h,a;
bool search(int u){
	f(i,a)
		if(nodes[u][i]>0 && !vis[i]){
			vis[i]=true;
			if(prev[i]==-1 || search(prev[i])){
				prev[i]=u;
				next[u]=i;
				return true;
			}
		}
	return false;
}

int match(){
	int flow=0;
	fill(prev,prev+a+h,-1);
	fill(next,next+a+h,-1);
	for(int u=0;u<h;u++)
		if(next[u]==-1){
			fill(vis,vis+a+h,false);
			if(search(u))
				flow++;
		}
	return flow;
}

long long sol [250][250][2];
int hrate [250][2];
int arate [250][2];
long dist  [250][250];

bool canUse(int h, int a, long long year){
	return sol[h][a][0]>=0 ||
        (sol[h][a][1]>0 && sol[h][a][1]*(year-dist[h][a])+sol[h][a][0]>=0);
}

void buildGraph(long long maxCost){
	f(i,h)f(j,a){nodes[i][j]=canUse(i,j,maxCost)?1:0;}
}

int main(){
	while(true){
		scanf("%d %d",&h,&a);
		if(h==0 && a==0)return 0;
		f(i,h)
			scanf("%lld %lld",hrate[i], hrate[i]+1);
		f(i,a)
			scanf("%lld %lld",arate[i], arate[i]+1);
		f(i,h)
			f(j,a)
				scanf("%lld",&dist[i][j]);
		long long max = 0;
		f(i,h)
			f(j,a){
				sol[i][j][0] = hrate[i][0]-arate[j][0]-arate[j][1]*dist[i][j];
				sol[i][j][1] = hrate[i][1]-arate[j][1];
				
				if(sol[i][j][0]<0 && sol[i][j][1]>0){
					long long time = (-sol[i][j][0]/sol[i][j][1])+2;
					max = time>max?time:max;
				}
			}
		long long min = 0;
		long long works = -1;
		max = 2000000000;
		while(max>=min){
			long long mid = (max+min)/2;
			buildGraph(mid);
			if(match()==a){
				works = mid;
				max = mid-1;
			}
			else{
				min = mid+1;
			}
		}
		if(works!=-1)
			printf("%d\n",works);
		else
			printf("IMPOSSIBLE\n");
	}
}

