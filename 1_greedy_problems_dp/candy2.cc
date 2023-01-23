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
    ll total_ec {};
    vector<ll> ecv{};
    vector<ll> feed_brats{};

    ll prev {brats[0]};
    ll next {1};
    // have to keep track of candy here
    while (total_ec < candy)
    {
        feed_brats.push_back(prev);
        ec = prev - brats[next];
        total_ec += ec;
        ecv.push_back(prev - brats[next]);
        if(ec > candy / 2)
        {
            // ecv.push_back(0);
            break;
        }
        prev = brats[next];
        next++;
        if(next == brats.size())
            break;
    }
    // how much candy needs to be paid out for ecv to be same values;
    total_ec -= ec;
    candy -= total_ec;
    cerr << "candy " << candy << endl;
    cerr << "FIRST ECV = ";
    for (auto i : ecv)
    {
        cerr << i << " ";
    }
    cerr << endl;
    cerr << "candy left = " << candy << endl; 





    // if (ec < candy)
    // {
    //     candy -= ec + 1;
    // } else
    // {
    //     candy = 0;
    // }
    
    ecv[ecv.size() - 1] = 0;


    // if (candy % ecv.size() != 0)
    // {
    //     cerr << "odd number increasing first ecv elem by one candy-- " << candy
    //          << endl;
    //     ecv.at(0)++;
    //     candy--;
    // }
    for(ll i {}; i < ecv.size(); i++)
    {
        if(candy % ecv.size() == 0)
            break;
        else
        {
            ecv[i]++;
            candy--;
        }
    }

    // bool modulo{candy % ecv.size() != 0};
    // ll rest {candy & ecv.size() }

    ll deal_to_ecv {candy / ecv.size()};
    cerr << "Deal to ecv " << deal_to_ecv << " ";
    
    for (auto & i : ecv)
    {
        i += deal_to_ecv;
        cerr << i << " " << endl;
        candy -= deal_to_ecv;
    }


    // maybe can remove this loop?
    for (ll i {}; i < ecv.size(); i++)
    {
        brats[i] -= ecv[i];
    }
    cout << endl;
    cout << endl;

    ll total_ree{};
    for ( auto ree : brats)
    {
        if (candy)
        {
            ree--;
            candy--;
        }
        cout << ree << " ";
        total_ree += (ree * ree);
    }
    cout << endl;
    
    cout << total_ree;
}