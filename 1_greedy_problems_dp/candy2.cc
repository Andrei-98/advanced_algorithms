#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

typedef int ll;

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


ll smallest_brat(vector<ll> const& brats, ll const candy)
{
    ll estimated_cost{};
    ll prev_candy {brats[0]};

    for (ll i{1}; i <= brats.size(); i++)
    {
        estimated_cost += prev_candy - brats[i];
        prev_candy = brats[i];

        if(estimated_cost >= candy)
        {
            break;
        }
    }
}


int main() 
{
    ll candy{};
    cin >> candy;

    vector<ll> brats {get_candy_demands()};




    // print_vector(ecv, "ecv :");
    // print_vector(feed_brats, "feed_brats");


    


    // for(ll i {}; i < ecv.size(); i++)
    // {
    //     if(candy % ecv.size() == 0)
    //         break;
    //     else
    //     {
    //         ecv[i]++;
    //         candy--;
    //     }
    // }

    ll deal_candy {candy / index};
    for (ll i{0}; i <= index; i++)
    {
        brats[i] -= deal_candy;
        candy -= deal_candy;

    }
    print_vector(brats);



    // ll deal_to_ecv {candy / ecv.size()};
    // cerr << "Deal to ecv " << deal_to_ecv << " ";
    
    // for (auto & i : ecv)
    // {
    //     i += deal_to_ecv;
    //     cerr << i << " " << endl;
    //     candy -= deal_to_ecv;
    // }


    // maybe can remove this loop?
    // for (ll i {}; i < ecv.size(); i++)
    // {
    //     brats[i] -= ecv[i];
    // }

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