#include <cassert>
#include <utility>
#include <algorithm>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;

ull gcd(ull a, ull b){ return a==0 ? b : gcd(b%a,a); }
//returns a pair (x,y) such that ax+by=gcd(a,b)
pair<ll,ll> egcd(ll a, ll b){
    ll x=0,x_prev=1,y=1,y_prev=0,a_curr=a,b_curr=b;
    while(b_curr!=0){
        ll q = a_curr/b_curr;
        ll r = a_curr%b_curr;
        a_curr = b_curr;
        b_curr = r;
        ll nx = x_prev-q*x;
        ll ny = y_prev-q*y;
        x_prev = x;
        y_prev = y;
        x=nx;
        y=ny;
    }
    return make_pair(x_prev,y_prev);
}

ull factorial(int n){
    ull ret=1;
    for(int i=2;i<=n;i++) ret*=i;
    return ret;
}

//n choose m
//tries hard not to overflow
//runtime is O(M log M) where M=min(m,n-m) but for any M that could even have
//an issue, the resulting value is too large to fit in a long long
ull binom(ull n,ull m){
    if(2*m>n) return binom(n,n-m);
    ull upper=(n-m)+1,lower=2,ret=1,denom=1;
    while(lower<=m || upper<=n){
        if((denom>ret || lower>n) && upper<=m)
            ret*=upper++;
        else if(lower<=n)
            denom*=lower++;
        ull g = gcd(ret,denom);
        ret/=g;
        denom/=g;
    }
    return ret;
}
