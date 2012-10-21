package library;

/**
 * Straight forward, longest common substring of two strings
 * @author ekulcyk
 *
 */
public class LongestCommonSubstring {

	/*
	 * Be careful about capitols!
	 */
	public static String longestCommonSubstring(String one, String two){
		int[][] solve = new int[one.length()+1][two.length()+1];
		int maxx=0;
		int max=0;
		
		for (int i=0; i <one.length()+1;i++)
			for (int j=0; j<two.length()+1;j++)
				if (i==0 || j==0)
					solve[i][j]=0;
				else{
					solve[i][j]=one.charAt(i-1)==two.charAt(j-1)?solve[i-1][j-1]+1:0;
					if (solve[i][j]>max){
						max=solve[i][j];
						maxx=j;
					}
				}
		return two.substring(maxx-max,maxx);
	}
	
	public static void main(String[] args){
		System.out.println(longestCommonSubstring("a","abafbabbbb"));
	}
}
