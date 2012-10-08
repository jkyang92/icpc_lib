#include <cstring>
#include <climits>
#include <vector>
#include <list>

using namespace std;

/* T should be some sort of two dimensional array
 * capacity[i][i]=0 for all i
 * flow matrix must be zeroed
 * the start node is assumed to be node 0, and the end node node_count-1
 * IN: capacity node_count
 * OUT: flow
 * Algorithm: push-relabel (highest active vertex)
 * Time Complexity: O(V^2 sqrt(E)) (V=node_count,E=edges)
 * Space Complexity: O(V+E)
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
    int top_height = 0;
    int remain=0;
    list<int> *height_array = new list<int>[node_count*2];
    bool *in_queue = new bool[node_count];
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
    for(int i=0;i<node_count;i++){
        flow[0][i]=capacity[0][i];
        excess[i] = capacity[0][i];
        if(excess[i]!=0){
            if(i!=0 && i!=node_count-1){
                remain++;
                in_queue[i]=true;
                height_array[heights[i]].push_back(i);
            }
        }
    }
    while(remain>0){
        int curr = height_array[top_height].front();
        height_array[top_height].pop_front();
        in_queue[curr]=false;
        remain--;
        while(height_array[top_height].empty() && top_height>0){
            top_height--;
        }
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
                        if(!in_queue[i] && i!=0 && i!=node_count-1){
                            remain++;
                            in_queue[i]=true;
                            height_array[heights[i]].push_back(i);
                            if(heights[i]>top_height){
                                top_height=heights[i];
                            }
                        }
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
                heights[curr]=best+1;
            }
        }
    }
    delete[] height_array;
    delete[] in_queue;
    delete[] adj_list;
    delete[] heights;
    delete[] excess;
    delete[] start;
}
