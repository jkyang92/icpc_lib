#include<iostream>
#include<bitset>
using namespace std;

bitset<100> dominated_by[100];
bitset<100> temp;
int N;

struct node
{
    int numIn;
    int numOut;
    int prev[100];
    int next[100];
    
    node() : numIn(0), numOut(0) {};
};

node nodes[100];
bool visited[100];

void DFS(int n)
{
    if(visited[n])
        return;
    visited[n] = true;
    
    for(int i = 0; i < nodes[n].numOut; i++)
        DFS(nodes[n].next[i]);
}

void findDominatorMatrix()
{
    dominated_by[0].reset();
    dominated_by[0].set(0);
    
    bool any_change = true;
    
    while(any_change)
    {
        any_change = false;
        for(int i = 1; i < N; i++)
        {
            for(int j = 0; j < nodes[i].numIn; j++)
            {
                temp = dominated_by[i];
                dominated_by[i] = (dominated_by[i] & dominated_by[nodes[i].prev[j]]);
                dominated_by[i].set(i);
                
                if(temp != dominated_by[i])
                    any_change = true;
            }
        }
    }
    
    for(int i = 0; i < N; i++)
        visited[i] = false;
    DFS(0);
    
    for(int i = 1; i < N; i++)
        if(!visited[i])
            dominated_by[i].reset();
}

int main()
{
    int cases;
    cin >> cases;
    
    for(int t = 1; t <= cases; t++)
    {
        cin >> N;
        
        for(int i = 0; i < N; i++)
            dominated_by[i].set();
        
        for(int i = 0; i < N; i++)
        {
            nodes[i].numOut = 0;
            nodes[i].numIn = 0;
        }
        
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                int temp_in = 0;
                cin >> temp_in;
                if(temp_in == 1)
                {
                    nodes[j].prev[nodes[j].numIn] = i;
                    nodes[i].next[nodes[i].numOut] = j;
                    nodes[i].numOut++;
                    nodes[j].numIn++;
                }
            }
        }
        
        findDominatorMatrix();
        
        cout << "Case " << t << ":" << endl;
        cout << "+";
        for(int i = 0; i < 2 * N - 1; i++)
            cout << "-";
        cout << "+" << endl;
        for(int i = 0; i < N; i++)
        {
            cout << "|";
            for(int j = 0; j < N; j++)
                if(dominated_by[j].test(i))
                    cout << "Y|";
                else
                    cout << "N|";
            cout << endl;
            cout << "+";
            for(int k = 0; k < 2 * N - 1; k++)
                cout << "-";
            cout << "+" << endl;
        }
    }
    
    return 0;
}
