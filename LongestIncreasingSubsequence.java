package library;

public class LongestIncreasingSubsequence {

	/**
	 * NOTE: Gets the length of the liss ENDING at each index.
	 * To get the length of each liss STARTING at each index, reverse your list and run LDSS on it.
	 * @param nums
	 * @return
	 */
	int lis(int[] nums){
		int maxs = 1;
		int[] ls = new int[nums.length];
		for(int i = 0; i < nums.length; i++){
			ls[i]=1;
			for(int j = 0; j < i; j++){
				if(nums[i]>nums[j]){
					ls[i] = Math.max(ls[i], ls[j]+1);
					maxs = Math.max(maxs, ls[i]);
				}
			}
		}
		return maxs;
	}
	
	/**
	 * Given each element has a load and a weight, you want to stack elements on top of each other
	 * Returns the number of elements that can be stacked
	 * m[i][j] = 	length of longest sequence
	 * 				Ending at element i
	 * 				With a max load of j
	 * @return
	 */
	int lis_other(int[] weight, int[] load, int n, int maxLoad){
		int[][]m = new int[n][maxLoad+1];

		int max = 1;
		for(int i = 0 ; i < n; i++){
			for(int j = 0 ; j <= maxLoad; j++){
				if(i==0)
					m[i][j]=j<=load[i]?1:0;
					else if (j<=load[i] && j+weight[i]<=maxLoad)
						m[i][j]=Math.max(m[i-1][j], 1+m[i-1][j+weight[i]]);
					else if (j<=load[i])
						m[i][j]=Math.max(m[i-1][j], 1);
					else
						m[i][j]=m[i-1][j];
				max = max>m[i][j]?max:m[i][j];
			}
		}
		return max;
	}
	
	static int[]b;

	
	/**
	 * Optimized version of the algorithm
	 *  Finds longest strictly increasing subsequence. O(n log k) algorithm.
	 */
	static int find_lis(int[] a)
	{
		b = new int[a.length];
		int[]p = new int[a.length];
		int u, v,bsize;

		if (a.length==0) return 0;

		b[0]=0;
		bsize = 1;

		//the ending point
		for (int i = 1; i < a.length; i++) 
		{
			// If next element a[i] is greater than last element of current longest subsequence a[b.back()], just push it at back of "b" and continue
			if (a[b[bsize-1]] < a[i]) 
			{
				p[i] = b[bsize-1];
				b[bsize]=i;
				bsize++;
				continue;
			}

			// Binary search to find the smallest element referenced by b which is just bigger than a[i]
			// Note : Binary search is performed on b (and not a). Size of b is always <=k and hence contributes O(log k) to complexity.    
			for (u = 0, v =bsize-1; u < v;) 
			{
				int c = (u + v) / 2;
				if (a[b[c]] < a[i]) u=c+1; else v=c;
			}

			// Update b if new value is smaller then previously referenced value 
			if (a[i] < a[b[u]]) 
			{
				if (u > 0)
					p[i] = b[u-1];
				b[u]= i;
			}	
		}

		for (u = bsize-1, v = b[bsize-1];u>=0; b[u]= v, v = p[v],u--);

		return bsize;
	}
}
