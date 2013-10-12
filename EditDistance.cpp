#include <stdio.h>
#include <string.h>

const int strLen = 25;
int sol[strLen][strLen];
int next [strLen][strLen];

char* one,*two;
int n,m;
int numDeleted;

int solve()
{
	n = strlen(one);
	m = strlen(two);
	for(int i = m; i>=0; i--){
		sol[n][i]=m-i;
	}
	for(int i = n-1; i>=0; i--){
		sol[i][m]=n-i;
	}
	for(int o = n-1; o>=0; o--){
		for(int t = m-1; t>=0; t--){
			sol[o][t] = one[o]==two[t]?sol[o+1][t+1]:sol[o+1][t+1]+1;
			sol[o][t] = sol[o][t]< sol[o][t+1]+1? sol[o][t] : sol[o][t+1]+1;
			sol[o][t] = sol[o][t]< sol[o+1][t]+1? sol[o][t] : sol[o+1][t]+1;
			next[o][t]= sol[o][t]==sol[o][t+1]+1 ? 1
				:(sol[o][t]==sol[o+1][t]+1?2:0);
			next[o][t]= next[o][t]==0 && one[o]==two[t]?-1:next[o][t];
		}
	}
	return sol[0][0];
}
//Prints out how to transform one string to the other.
void print(int o,int t){
	if(o==n && t==m){
		printf("E\n");//END
	}
	else if (o==n){
		for(int i = t; i <m; i++){
			printf("I%c%02d",two[i],(o+i-t-numDeleted+1));//INSERT
		}
		printf("E\n");//END
	}
	else if (t==m){
		for(int i = o; i <n; i++)
			printf("D%c%02d",one[i],(o-numDeleted+1));//DELETE
		printf("E\n");
	}
	else {
		switch (next[o][t]){
			case 0:
				printf("C%c%02d",two[t],(o-numDeleted+1));//CHANGE
				print(o+1,t+1);
				break;
			case -1:
				print(o+1,t+1);//ALL GOOD
				break;
			case 1:
				printf("I%c%02d",two[t],(o-numDeleted+1));//INSERT
				numDeleted--;
				print(o,t+1);
				break;
			case 2:
				printf("D%c%02d",one[o],(o-numDeleted+1));//DELETE
				numDeleted++;
				print(o+1,t);
				break;
			default:
				printf("E\n");//END
				break;
		}
	}
}
void print(){
	numDeleted = 0;
	print(0,0);
}
int main(){
	while(true){
		one = new char[strLen];
		two = new char[strLen];
		scanf("%s",one);
		if(one[0]=='#')
			break;
		scanf("%s",two);
		printf("num changed %d\n",solve());
		print();
	}
	return 0;
}
