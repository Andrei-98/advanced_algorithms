#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

typedef unsigned long long ll;

using namespace std;


void print_vector(vector<ll> brats, string const& line="BRATS :")
{
    cerr << line;
    for (ll brat : brats)
    {
        cerr << brat << " ";
    }
    cerr << endl;
}


vector<ll> get_candy_demands()
{
    vector<ll> brats {};
    ll loops{}, cur_brat{};

    cin >>  loops;

    for (ll i{}; i < loops; i++)
    {
        cin >> cur_brat;
        brats.push_back(cur_brat);
    }

    sort(brats.begin(), brats.end(), greater<ll>());
    
    return brats;
}


// vector<ll> 


int main() 
{
    ll candy{};
    cin >> candy;

    vector<ll> brats {get_candy_demands()};



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
    ecv[ecv.size() - 1] = 0;

    print_vector(ecv, "ecv :");
    print_vector(feed_brats, "feed_brats");


    


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
    cout << total_ree << endl;
}