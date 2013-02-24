package library;

/**
 * This code does two things,
 * First, finds the minimum number of insertions, deletions, and changes to word one to make it into word two.
 * This is stored in sol[][]
 * 
 * Second, it prints out the changes it made to word one, which is in the form
 * Ia4Db5Cc6E    ================ Inserts 'a' at posistion 4, Delete 'b' at pos 5, Change 'c' at pos 6, End
 * @author ekulcyk
 *
 */
public class EditDistance {

	//NEEDED FOR EDIT DISTANCE
	int[][] sol;
	char[] one,two;
	int n,m;
	
	//NEEDED FOR PRINT EDIT DISTANCE
	int[][] next;
	int numDeleted;

	
	int editDistance(char[] one, char[] two){
		n = one.length;
		m = two.length;

		sol = new int[n+1][m+1];
		next = new int[n+1][m+1];

		for(int i = m; i>=0; i--)
			sol[n][i]=m-i;
		for(int i = n-1; i>=0; i--)
			sol[i][m]=n-i;

		for(int o = n-1; o>=0; o--)
			for(int t = m-1; t>=0; t--){
				sol[o][t] = one[o]==two[t]?sol[o+1][t+1]:sol[o+1][t+1]+1;
				sol[o][t] = sol[o][t]< sol[o][t+1]+1? sol[o][t] : sol[o][t+1]+1;
				sol[o][t] = sol[o][t]< sol[o+1][t]+1? sol[o][t] : sol[o+1][t]+1;
				next[o][t]= sol[o][t]==sol[o][t+1]+1?1:(sol[o][t]==sol[o+1][t]+1?2:0);
				next[o][t]= next[o][t]==0 && one[o]==two[t]?-1:next[o][t];
			}
		return sol[0][0];
	}
	
/////////////////////////////////////END EDIT DISTANCE/////////////BEGIN PRINT EDIT DISTANCE///////////////////////////
	void printTrail(){
		numDeleted = 0;
		print(0,0);
	}

	void print(int o,int t){
		if(o==n && t==m){
			System.out.println("E");
		}
		else if (o==n){
			for(int i = t; i <m; i++){
				System.out.printf("I%c%02d",two[i],(o+i-t-numDeleted+1));
			}
			System.out.println("E");
		}
		else if (t==m){
			for(int i = o; i <n; i++)
				System.out.printf("D%c%02d",one[i],(o-numDeleted+1));
			System.out.println("E");
		}
		else {
			switch (next[o][t]){
			case 0:
				System.out.printf("C%c%02d",two[t],(o-numDeleted+1));
				print(o+1,t+1);
				break;
			case -1:
				print(o+1,t+1);
				break;
			case 1:
				System.out.printf("I%c%02d",two[t],(o-numDeleted+1));
				numDeleted--;
				print(o,t+1);
				break;
			case 2:
				System.out.printf("D%c%02d",one[o],(o-numDeleted+1));
				numDeleted++;
				print(o+1,t);
				break;
			default:
				System.out.println("E");
				break;
			}
		}
	}

	public static void main(String[] args) {
		new EditDistance();

	}

}
