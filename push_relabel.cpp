#include <cstring>
#include <climits>
#include <queue>
#include <vector>

using namespace std;

bool cmp(const pair<int,int>& a, const pair<int,int>& b){
    if(a.second==b.second)
        return a.first<b.first;
    return a.second<b.second;
}
/* T should be some sort of two dimensional array
 * capacity[i][i]=0 for all i
 * flow matrix must be zeroed
 * the start node is assumed to be node 0, and the end node node_count-1
 * IN: capacity node_count
 * OUT: flow
 * Algorithm: push-relabel (relabel to front)
 * Time Complexity: O(V^3) (V=node_count)
 * Space Complexity: O(V)
 */
template<typename T>
void maxflow(T capacity,int node_count,T flow) {
    int *heights = new int[node_count];
    int *excess = new int[node_count];
    int *start = new int[node_count];
    memset(heights,0,sizeof(int)*node_count);
    memset(excess,0,sizeof(int)*node_count);
    memset(start,0,sizeof(int)*node_count);
    heights[0]=node_count;
    vector<int>* adj_list = new vector<int>[node_count];
    for(int i=0;i<node_count;i++){
        for(int j=i+1;j<node_count;j++){
            if(capacity[i][j]!=0 || capacity[j][i]!=0){
                adj_list[i].push_back(j);
                adj_list[j].push_back(i);
            }
        }
    }
    //setup outbound flow from v
    priority_queue<pair<int,int>,vector<pair<int,int> >,bool(*)(const pair<int,int>&,const pair<int,int>&)> todo(cmp);
    for(int i=0;i<node_count;i++){
        flow[0][i]=capacity[0][i];
        excess[i] = capacity[0][i];
        if(excess[i]!=0){
            if(i!=0 && i!=node_count-1)
                todo.push(make_pair(i,heights[i]));
        }
    }
    while(!todo.empty()){
        int curr = todo.top().first;
        todo.pop();
        while(excess[curr]>0){
            int curr_height = heights[curr];
            if(start[curr]<adj_list[curr].size()){
                int i = adj_list[curr][start[curr]];
                if(heights[i]<curr_height){
                    int res = capacity[curr][i]-flow[curr][i]+flow[i][curr];
                    if(res>0){
                        int nflow = min(res,excess[curr]);
                        excess[curr]-=nflow;
                        excess[i]+=nflow;
                        if(i!=0 && i!=node_count-1)
                            todo.push(make_pair(i,heights[i]));
                        int removed = min(flow[i][curr],nflow);
                        flow[i][curr]-=removed;
                        nflow-=removed;
                        flow[curr][i]+=nflow;
                    }
                }
                start[curr]++;
            }
            else{
                start[curr]=0;
                int best=INT_MAX;
                for(int i=0;i<adj_list[curr].size();i++){
                    int other = adj_list[curr][i];
                    if(heights[other]<best && capacity[curr][other]-flow[curr][other]+flow[other][curr]>0){
                        best = heights[other];
                    }
                }
                assert(best!=INT_MAX);
                heights[curr]=best+1;
            }
        }
    }
    delete[] adj_list;
    delete[] heights;
    delete[] excess;
    delete[] start;
}
