#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>


typedef unsigned long long ll;

using namespace std;

int main() 
{

    vector<ll> brats {};
    ll candy{}, loops{}, cur_brat{};

    cin >> candy >> loops;

    for (ll i{}; i < loops; i++)
    {
        cin >> cur_brat;
        brats.push_back(cur_brat);
    }

    sort(brats.begin(), brats.end(), greater<ll>());

    ll ec{};
    vector<ll> ecv{};
    vector<ll> feed_brats{};

    ll prev {brats[0]};
    ll next {1};
    while (ec < candy)
    {
        feed_brats.push_back(prev);
        if(next == brats.size())
            break;
        ec += prev - brats[next];
        ecv.push_back(prev - brats[next]);
        prev = brats[next];
        next++;
    }
    
    ecv[ecv.size() - 1] = 0;

    if (ecv.size() % 2 != 0)
        ecv[0]++;
    
    cout << "ecv" << endl;
    for (auto & i : ecv)
    {
        i++;
        cout << i << endl;
    }

    // maybe can remove this loop?
    for (ll i {}; i < ecv.size(); i++)
    {
        brats[i] -= ecv[i];
    }
    cout << endl;
    cout << endl;

    ll total_ree{};
    for ( auto const ree : brats)
    {
        cout << ree << " ";
        total_ree += (ree * ree);
    }
    cout << endl;
    
    cout << total_ree;
}