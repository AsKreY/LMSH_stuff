#include <iostream>
#include <deque>
#include <queue>
#include <stack>
 
typedef  long long ll;
 
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    std::stack <std::pair<ll, ll>> min_l, min_r;
    ll n, a[1000000], mina_l[1000000];
    ll max_s=-1;
    std::cin >> n >> a[0];
    min_l.push(std::make_pair(a[0], 0));
    mina_l[0]=-1;
    for (ll i = 1;i < n; ++i) {
        std::cin >> a[i];
        while ((!min_l.empty())&&(a[i] <= min_l.top().first)) {
            min_l.pop();
        }
        if (!min_l.empty()) mina_l[i] = min_l.top().second;
        else mina_l[i]=-1;
        min_l.push(std::make_pair(a[i], i));
    }
    min_r.push(std::make_pair(a[n-1], n-1));
    if (a[n-1]*(n-mina_l[n-1]-1)>max_s) max_s=a[n-1]*(n-mina_l[n-1]-1);
    for (ll i = n - 2; i > -1 ; --i){
        while ((!min_r.empty())&&(a[i]<=min_r.top().first)){
            min_r.pop();
        }
        if (!min_r.empty()){
            if (a[i]*(min_r.top().second-mina_l[i]-1)>max_s) max_s=a[i]*(min_r.top().second-mina_l[i]-1);
        }
        else{
            if (a[i]*(n-mina_l[i]-1)>max_s) max_s=a[i]*(n-mina_l[i]-1);
        }
        min_r.push(std::make_pair(a[i], i));
    }
    std::cout<<max_s;
}
