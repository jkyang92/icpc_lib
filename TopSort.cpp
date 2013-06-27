#include<iostream>
#include<malloc.h>
#include<queue>
using namespace std;

int N;

struct node {
    int numIn;
    int numOut;
    int next[101];

    node (): numIn(0), numOut(0){}
};

int *topSort(node nodes[]) {
    int *toReturn = (int *)malloc(N * sizeof(int));
    int index = 0;
    queue<int> q;
    for(int i = 0; i < N; i++)
        if(nodes[i].numIn == 0)
            q.push(i);
    while(!q.empty()){
        int popped = q.front();
        q.pop();
        toReturn[index++] = popped;
        node &curr = nodes[popped];
        for(int i = 0; i < curr.numOut; i++){
            node &nextNode = nodes[curr.next[i]];
            nextNode.numIn--;
            if(nextNode.numIn == 0)
                q.push(curr.next[i]);
        }
    }
}
