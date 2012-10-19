
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

/*does gaussian elimination in place in the nxm matrix
 *A[r][c] should be row r, col c
 *returns true if the processes succeeds
 *uses partial pivoting, so reasonably stable with floating point if nessary
 *runtime: O(nm^2)
 *DO NOT use with int, use with either doubles or rationals, rationals suggested
 *the resulting matrix will always be in row-reduced echelon form
 *returns the non-pivot columns
 */
template<typename T>
vector<int> gaussian_elimination(T** A,int n, int m){
    vector<int> ret;
    int p_row=0;
    for(int c=0;c<m;c++){
        //find piviot
        int pivot = -1;
        T pivotValue = 0;
        for(int r=p_row;r<n;r++){
            if(abs(A[r][c])>pivotValue){
                pivotValue = abs(A[r][c]);
                pivot = r;
            }
        }
        if(pivotValue==0){
            ret.push_back(c);
            continue;
        }
        if(p_row!=pivot)
            swap_ranges(A[p_row],A[p_row]+n,A[pivot]);
        pivotValue = A[p_row][c];
        for(int r=0;r<n;r++){
            if(r==c)
                continue;
            T multiplier = A[r][c]/pivotValue;
            if(multiplier!=0)
                for(int i=c+1;i<m;i++)
                    A[r][i]-=A[r][i]*multiplier;
            A[r][c]=0;
        }
        //set pivot to 1
        A[p_row][c]=1;
        for(int i=p_row+1;i<m;i++)
            A[p_row][i]/=pivotValue;
        p_row++;
    }
    return ret;
}

//returns a basis for the subspace of homogeneous solutions
//i.e. solutions to Ax=0
template<typename T>
vector<T*> find_homogeneous_solutions(T** A,int n){
    vector<T*> ret;
    vector<int> non_pivots = gaussian_elimination(A,n,n);
    vector<int> pivots;
    int index = 0;
    for(int i=0;i<n;i++){
        if(index>=non_pivots.size() || non_pivots[index]==i)
            index++;
        else
            pivots.push_back(i);
    }
    ret.resize(non_pivots.size());
    for(int i=0;i<ret.size();i++){
        ret[i] = new T[n];
        for(int j=0;j<n;j++)
            ret[i][j]=0;
        for(int j=0;j<n-non_pivots.size();j++)
            ret[i][pivots[j]]=-A[non_pivots[i]][j];
        ret[i][non_pivots[i]]=1;
    }
    return ret;
}
