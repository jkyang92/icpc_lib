
#include <cmath>
#include <vector>

using namespace std;

/*does gaussian elimination in place in the nxn matrix, agumented with k columns
 *A[r][c] should be row r, col c
 *returns true if the processes succeeds
 *uses partial pivoting, so reasonably stable with floating point if nessary
 *runtime: O(n^3+kn^2)
 *DO NOT use with int, use with either doubles or rationals, rationals suggested
 *the resulting matrix will always be in row-reduced echelon form
 *returns the non-pivot columns
 */
template<typename T>
vector<int> gaussian_elimination(T** A,int n, int k){
    vector<int> ret;
    for(int c=0;c<n;c++){
        //find piviot
        int pivot = -1;
        T pivotValue = 0;
        for(int r=c;r<n;r++){
            if(abs(A[r][c])>pivotValue){
                pivotValue = abs(A[r][c]);
                pivot = r;
            }
        }
        if(pivotValue==0){
            ret.push_back(c);
            continue;
        }
        if(c!=pivot){
            T* temp = A[c];
            A[c]=A[pivot];
            A[pivot]=temp;
        }
        pivotValue = A[c][c];
        for(int r=0;r<n;r++){
            if(r==c)
                continue;
            T multiplier = A[r][c]/pivotValue;
            if(multiplier!=0)
                for(int i=c+1;i<n+k;i++)
                    A[r][i]-=A[r][i]*multiplier;
            A[r][c]=0;
        }
        //set pivot to 1
        A[c][c]=1;
        for(int i=c+1;i<n+k;i++)
            A[c][i]/=pivotValue;
    }
    return ret;
}

//returns a basis for the subspace of homogeneous solutions
//i.e. solutions to Ax=0
template<typename T>
vector<T*> find_homogeneous_solutions(T** A,int n){
    vector<T*> ret;
    vector<int> non_pivots = gaussian_elimination(A,n,0);
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
