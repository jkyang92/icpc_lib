#include <stdio.h>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#define f(i,n) for(int i=0;i<n;i++)
using namespace std;
map<string,int> teamMap;

struct team{
	int points;
	int wins;
	int goalDiff;
	int goals;
	int played;
	char name[101];
	int ties;
	int losses;
};

bool comp(const team a, const team b){
	if(a.points!=b.points)
		return a.points>b.points;
	if(a.wins!=b.wins)
		return a.wins>b.wins;
	if(a.goalDiff!=b.goalDiff)
		return a.goalDiff>b.goalDiff;
	if(a.goals!=b.goals)
		return a.goals>b.goals;
	if(a.played!=b.played)
		return a.played<b.played;
	return strcasecmp(a.name,b.name)<0;
}
/*
	f(i,101){
		char aa = a.name[i], bb = b.name[i];
		if(aa=='\0' && bb!='\0')return true;
		else if (aa=='\0' || bb=='\0')return false;
		else if (tolower(aa)<tolower(bb))return true;
		else if (tolower(aa)>tolower(bb))return false;
		else if (aa>bb)return true;
	}
	return false;
	//printf("Got to lex comp %s %s %d\n",a.name,b.name,order);
}*/

int main(){
	int n,nt;
	char tn[101],tmp[101];
	team teams[31];
	scanf("%d\n",&n);
	f(i,n){
		if(i!=0)
			printf("\n");		
		teamMap.clear();
		cin.getline(tn, 101);
		scanf("%d",&nt);
		cin.getline(tmp,100);
		f(j,nt){
			teams[j].points=0;
			teams[j].wins=0;
			teams[j].goalDiff=0;
			teams[j].goals=0;
			teams[j].played=0;
			teams[j].ties=0;
			teams[j].losses=0;
			cin.getline(teams[j].name,101);
			//printf("%s %d here\n",teams[j].name,j);
			teamMap[string(teams[j].name)] = j;
		}

		int num;
		scanf("%d\n",&num);
		f(j,num){
			char team1[101],team2[101]="fsdf";
			int goals1,goals2;
			scanf("%[^#]#%d@%d#%[^\n]\n",team1,&goals1,&goals2,team2);
		
			int ind1 = teamMap[string(team1)];
			int ind2 = teamMap[string(team2)];
			//printf("%s %d %s %d %d %d\n",team1,ind1,team2,ind2,goals1,goals2);
			
			teams[ind1].played++;
			teams[ind2].played++;

			teams[ind1].points+=goals1>goals2?3:goals1==goals2?1:0;
			teams[ind2].points+=goals2>goals1?3:goals2==goals1?1:0;

			teams[ind1].wins+=goals1>goals2?1:0;
			teams[ind2].wins+=goals2>goals1?1:0;

			teams[ind1].ties+=goals1==goals2?1:0;
			teams[ind2].ties+=goals1==goals2?1:0;

			teams[ind1].losses+=goals2>goals1?1:0;
			teams[ind2].losses+=goals2<goals1?1:0;

			teams[ind1].goalDiff+=goals1-goals2;
			teams[ind2].goalDiff+=goals2-goals1;
			teams[ind1].goals+=goals1;
			teams[ind2].goals+=goals2;
		}
		sort(teams,teams+nt,comp);
		printf("%s\n",tn);
		f(j,nt){
			printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n",j+1,teams[j].name,teams[j].points,teams[j].played,teams[j].wins,teams[j].ties,teams[j].losses,teams[j].goalDiff,teams[j].goals,teams[j].goals-teams[j].goalDiff);
		}
	}
}
