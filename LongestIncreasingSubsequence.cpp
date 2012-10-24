#include <algorithm>
#include <stdio.h>
using std::max;

const int maxLen = 100;
int ls[maxLen];//length of each liss ending at each index
/**
 * NOTE: Gets the length of the liss ENDING at each index.
 * To get the length of each liss STARTING at each index, reverse your list and run LDSS on it.
 * @param nums
 * @return
 */
int lis(int* nums, int len){
	int maxs = 1;
	for(int i = 0; i < len; i++){
		ls[i]=1;
		for(int j = 0; j < i; j++){
			if(nums[i]>nums[j]){
				ls[i] = max(ls[i], ls[j]+1);
				maxs = max(maxs, ls[i]);
			}
		}
	}
	return maxs;
}

const int maxWeights = 100;
const int maxLoad = 100;
int m[maxWeights][maxLoad+1];
/**
 * Given each element has a load and a weight, you want to stack elements on top of each other
 * Returns the number of elements that can be stacked
 * m[i][j] = 		length of longest sequence
 * 				Ending at element i
 * 				With a max load of j
 * @return
 */
int lisWeighted(int* weight, int* load, int len, int loadLen){
	int maxs = 1;
	for(int i = 0 ; i < len; i++){
		for(int j = 0 ; j <= loadLen; j++){
			if(i==0)
				m[i][j]=j<=load[i]?1:0;
			else if (j<=load[i] && j+weight[i]<=loadLen)
				m[i][j]=max(m[i-1][j], 1+m[i-1][j+weight[i]]);
			else if (j<=load[i])
				m[i][j]=max(m[i-1][j], 1);
			else
				m[i][j]=m[i-1][j];
			maxs = max(maxs,m[i][j]);
		}
	}
	return maxs;
}

const int maxLength = 100;
int b[maxLength];//index of numbers that form lis
int p[maxLength];

/**
 * Optimized version of the algorithm
 *  Finds longest strictly increasing subsequence. O(n log k) algorithm.
 */
int lisOptim(int* nums, int len)
{
	int u, v,bsize;

	if (len==0) return 0;

	b[0]=0;
	bsize = 1;

	//the ending point
	for (int i = 1; i < len; i++){
		// If next element nums[i] is greater than last element of current longest subsequence nums[b.back()], just push it at back of "b" and continue
		if (nums[b[bsize-1]] < nums[i]){
			p[i] = b[bsize-1];
			b[bsize]=i;
			bsize++;
			continue;
		}

		// Binary search to find the smallest element referenced by b which is just bigger than nums[i]
		// Note : Binary search is performed on b (and not a). Size of b is always <=k and hence contributes O(log k) to complexity.    
		for (u = 0, v =bsize-1; u < v;){
			int c = (u + v) / 2;
			if (nums[b[c]] < nums[i]) u=c+1; else v=c;
		}

		// Update b if new value is smaller then previously referenced value 
		if (nums[i] < nums[b[u]]){
			if (u > 0)
				p[i] = b[u-1];
			b[u]= i;
		}	
	}
	for (u = bsize-1, v = b[bsize-1];u>=0; b[u]= v, v = p[v],u--);
	return bsize;
}

int main()
{
	const int len = 5;
	int nums[len] = {0,10,5,20,15};
	int seqLen = lis(nums,len);
	printf("length of lis unOptimized: %d\n",seqLen);

	seqLen = lisOptim(nums, len);
	printf("length of lis optimized %d\n", seqLen);
	for(int i =0; i<seqLen;i++)
		printf("%d ",nums[b[i]]);
	printf("\n");
}
