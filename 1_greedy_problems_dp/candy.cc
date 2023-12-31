#include <iostream>
#include <queue>
#include <algorithm>


typedef unsigned long long ll;

using namespace std;

int main() 
{

    priority_queue<ll> brats {};
    ll candy{}, loops{}, cur_brat{};

    cin >> candy >> loops;

    for (ll i{}; i < loops; i++)
    {
        cin >> cur_brat;
        brats.push(cur_brat);
    }

    ll demanding_brat{};
    ll next{};
    for (ll i{}; i < candy; i++)
    {
        demanding_brat = brats.top();
        brats.pop();
        next = demanding_brat - brats.top();


        brats.push(demanding_brat - next);
    }

    ll total_ree{};

    while(!brats.empty())
    {
        ll ree{brats.top()};
        brats.pop();
        total_ree += (ree * ree);
    }
    
    cout << total_ree;
}