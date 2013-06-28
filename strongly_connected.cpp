#include<iostream>
#include<vector>
#include<set>
using namespace std;

#define MAXX 60000

int numNodes = 0;
struct node {
  int numOut;
  vector<int> next;
  vector<int> criticals;
  vector<int> non_criticals;
  set<int> next2;
  int disc;
  int comp;
  int collapsed;
};

node allNodes[MAXX];
node newNodes[MAXX];
int dfs(int from, int curr, int depth) {
  if(allNodes[curr].disc != -1)
    return allNodes[curr].disc;
  allNodes[curr].disc = depth;
  int toReturn = allNodes[curr].disc;
  for(int i = 0; i < allNodes[curr].next.size(); i++) {
    int child = allNodes[curr].next[i];
    if(child != from) {
      int child_earl = dfs(curr, child, depth + 1);
      if(allNodes[curr].disc < child_earl) {
        allNodes[curr].criticals.push_back(child);
        allNodes[child].criticals.push_back(curr);
      }
      else {
        allNodes[curr].non_criticals.push_back(child);
        allNodes[child].non_criticals.push_back(curr);
        toReturn = min(toReturn, child_earl);
      }
    }
  }
  allNodes[curr].disc = toReturn;
  return toReturn;
}

int comp = 0;
void dfs_assign_component(int curr) {
  if(allNodes[curr].comp != -1)
    return;
  allNodes[curr].comp = comp++;
  for(int i = 0; i < allNodes[curr].non_criticals.size(); i++)
    allNodes[allNodes[curr].non_criticals[i]].comp = allNodes[curr].comp;
  for(int i = 0; i < allNodes[curr].criticals.size(); i++)
    dfs_assign_component(allNodes[curr].criticals[i]);
}

void collapse_graph() {
  for(int i = 0; i < numNodes; i++) {
    newNodes[allNodes[i].comp].collapsed += 1;
    for(int j = 0; j < allNodes[i].next.size(); j++) {
      int neigh = allNodes[i].next[j];
      if(allNodes[i].comp != allNodes[neigh].comp) {
        newNodes[allNodes[i].comp].next2.insert(allNodes[neigh].comp);
        newNodes[allNodes[neigh].comp].next2.insert(allNodes[i].comp);
      }
    }
  }
}

void doStuff() {
  dfs(-1, 0, 0);
  comp = 0;
  dfs_assign_component(0);
  collapse_graph();
}

int main() {
  return 0;
}
