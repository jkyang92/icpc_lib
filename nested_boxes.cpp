//FINDS THE LONGEST SEQUENCE OF BOXES THAT CAN FIT INSIDE EACH OTHER
#include <stdio.h>
#include <algorithm>
#include <limits.h>
using namespace std;
#define f(i,n) for(int i=0; i<n;i++)
int boxes[30][11];
int k,d;
int comp(const void* aa, const void* bb){
	int* a = (int*)aa;
	int* b = (int*)bb;
	f(i,d)
		if (a[i]<b[i])return 1;
		else if(a[i]>b[i])return -1;
	return 0;
}

bool isIn(const void* aa, const void* bb){
	int* a = (int*)aa;
	int* b = (int*)bb;
	f(i,d)
		if (a[i]>b[i] || a[i]==b[i])return false;
	return true;
}

int ls[30];
int prev[30];
int maxi;
int lis(int len){
	int maxs = 1;
	maxi=0;
	for(int i = 0; i < len; i++){
		ls[i]=1;
		prev[i]=-1;
		for(int j = 0; j < i; j++){
			if(isIn(boxes[i],boxes[j])){
				if(ls[j]+1>ls[i]){
					prev[i]=j;
					ls[i] = ls[j]+1;
				}
				if(ls[i]>maxs){
					maxs = ls[i];
					maxi = i;
				}
			}
		}
	}
	return maxs;
}

int main(){
	while(scanf("%d %d",&k, &d)!=EOF){
		f(i,k){
			fill_n(boxes[i],11,INT_MAX);
			f(j,d)
				scanf("%d",boxes[i]+j);
			sort(boxes[i],boxes[i]+d);
			boxes[i][10]=i+1;
		}
		qsort(boxes,k,sizeof boxes[0], comp);
		printf("%d\n",lis(k));
		while(maxi!=-1){
			if(prev[maxi]==-1)printf("%d\n",boxes[maxi][10]);
			else printf("%d ",boxes[maxi][10]);
			maxi =prev[maxi];
		}
	}
}
