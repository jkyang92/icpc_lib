#include <stdio.h>
#define f(i,n) for(int i =0; i<n;i++)

bool grid[2000][2000];
int sol[2000][2000], row[2000][2000];
int n;

void solveDiag()
{
	f(i,n){
		f(j,n){
			if(j==0)row[i][j]=grid[i][j];
			else row[i][j]=row[i][j-1]+grid[i][j];
			if(i==0)sol[i][j] = row[i][j];
			else sol[i][j] = sol[i-1][j]+row[i][j];
		}
	}
}
int solve(int w){
	int min=1<<30;
	f(i,n-w+1)
		f(j,n-w+1){
			int val = ((i>0&&j>0)?sol[i-1][j-1]:0)+sol[i+w-1][j+w-1]-((i>0)?sol[i-1][j+w-1]:0)-((j>0)?sol[i+w-1][j-1]:0);
			min = min>val?val:min;
		}
	return min;
}

int bsSolve(int l){
	int min = 1, max=n,works=-1;
	while(max>=min){
		int mid = (max+min)/2;
		if(solve(mid)<=l){
			min=mid+1;
			works= mid;
		}
		else
			max = mid-1;
	}
	return works;
}
int main(){
	int tc, w,l, x,y;
	scanf("%d",&tc);
	f(i,tc){
		scanf("%d%d%d",&n,&w,&l);
		f(j,n)
			f(k,n)
				grid[j][k]=false;
		f(j,w){
			scanf("%d%d", &x,&y);
			grid[x-1][y-1] = true;
		}
		
		solveDiag();
		int solu = bsSolve(l);
		printf("%d\n",solu*solu);
	}
}
