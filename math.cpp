#include <cassert>
#include <utility>
#include <algorithm>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;

ull gcd(ull a, ull b){ return a==0 ? b : gcd(b%a,a); }
//returns a pair (x,y) such that ax+by=gcd(a,b)
pair<ll,ll> egcd(ll a, ll b){
    ll x=0,x_prev=1;
    ll y=1,y_prev=0;
    ll a_curr=a;
    ll b_curr=b;
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
ull binom(ull n,ull m){
    if(m<n/2) return binom(n,n-m);
    //compute n_{(m)}/m!
    ull upper_index=(n-m)+1;
    ull lower_index=2;
    ull ret=1;
    while(lower_index<=m || upper_index<=n){
        if(ret%lower_index==0 && lower_index<=m){
            ret/=lower_index;
            lower_index++;
        }
        else if(upper_index<=n){
            ret*=upper_index;
            upper_index++;
        }
    }
    return ret;
}

#define TEST_EGCD(a,b) do{pair<ull,ull> val = egcd((a),(b)); assert(gcd((a),(b))==val.first*(a)+val.second*(b));}while(0)

int main(){
    //egcd tests
    TEST_EGCD(0,0);
    TEST_EGCD(1,0);
    TEST_EGCD(0,1);
    TEST_EGCD(1,1);
    TEST_EGCD(5,500);
    TEST_EGCD(10,25);
    TEST_EGCD(16,25);
    TEST_EGCD(16,500);
    assert(binom(1,0)==1);
    assert(binom(100,100)==1);
    assert(binom(0,0)==1);
    assert(binom(2,1)==2);
    assert(binom(300,1)==300);
    assert(binom(4,2)==6);
    assert(factorial(1)==1);
    assert(factorial(0)==1);
    assert(factorial(2)==2);
    assert(factorial(7)==5040);
}
