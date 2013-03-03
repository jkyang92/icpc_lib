#include <vector>

using namespace std;

struct edge{
    int a,b,cost;
};

void bellman_ford(int ncount,vector<edge> edges,int source,int *dist, bool *reachable, int *pred){
    for(int i=0;i<ncount;i++){
        dist[i]=-1;
        reachable[i]=false;
        pred[i] = -1;
    }
    dist[source]=0;
    reachable[source]=true;
    for(int i=0;i<ncount-1;i++){
        for(int j=0;j<edges.size();j++){
            if(reachable[edges[j].b]){
                int ncost = edges[j].cost+dist[edges[j].a];
                if(!reachable[edges[j].b] || ncost < dist[edges[j].b]){
                    dist[edges[j].b]=ncost;
                    reachable[edges[j].b]=true;
                    pred[edges[j].b] = edges[j].a;
                }
            }
        }
    }
}
