#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <numeric>


typedef unsigned long long ll;

using namespace std;

vector<ll> get_brats()
{
    vector<ll> brats{};
    ll loops{}, cur_brat{};

    cin >> loops;

    for (ll i{}; i < loops; i++)
    {
        cin >> cur_brat;
        brats.push_back(cur_brat);
    }

    sort(brats.begin(), brats.end(), greater<ll>());

    return brats;
}


// return a vector with the most brats and how much candy to give to all of them
// in order to bring them all to the same value
// if it returns the whole list we have to do something else!
ll get_estimated_cost(vector<ll> const& brats, ll const& candy)
{
    ll ec{};
    ll total_ec{};
    ll index{};
    // vector<ll> ecv{};

    ll prev{brats[0]};
    ll next{1};
    // have to keep track of candy here
    while (total_ec < candy)
    {
        ec = prev - brats[next];
        total_ec += ec;
        if (ec > candy / 2)
        {
            // ecv.push_back(0);
            break;
        }
        index++;
        // ecv.push_back(ec);
        prev = brats[next];
        next++;
        if (next == brats.size())
            break;
    }

    // if (accumulate(ecv.begin(), ecv.end(), 0) > candy)
    //     ecv.pop_back();

    return index;
}


void apply_ecv(vector<ll> & brats, ll const smallest_index, ll & candy)
{
    ll val {brats[smallest_index]};

    for(ll i{}; i < smallest_index; i++)
    {
        candy -= ecv[i];
        brats[i] -= ecv[i];
    }

}

void display_brats(vector<ll> const& brats, string line = "BRATS :")
{
    cerr << line;
    for(ll const i : brats)
    {
        cout << i << " ";
    }
    cerr << endl;
}


int main()
{
    ll candy{};
    cin >> candy;

    vector<ll> brats{get_brats()};
    // if we still have candy left cheese
    ll index_smallest {get_estimated_cost(brats, candy)};

    apply_ecv(brats, index_smallest, candy);

    display_brats(brats);



    // ecv[ecv.size() - 1] = 0;

    // for (ll i{}; i < ecv.size(); i++)
    // {
    //     if (candy % ecv.size() == 0)
    //         break;
    //     else
    //     {
    //         ecv[i]++;
    //         candy--;
    //     }
    // }

    // // bool modulo{candy % ecv.size() != 0};
    // // ll rest {candy & ecv.size() }

    // ll deal_to_ecv{candy / ecv.size()};
    // cerr << "Deal to ecv " << deal_to_ecv << " ";

    // for (auto &i : ecv)
    // {
    //     i += deal_to_ecv;
    //     cerr << i << " " << endl;
    //     candy -= deal_to_ecv;
    // }

    // // maybe can remove this loop?
    // for (ll i{}; i < ecv.size(); i++)
    // {
    //     brats[i] -= ecv[i];
    // }
    // cout << endl;
    // cout << endl;

    // ll total_ree{};
    // for (auto ree : brats)
    // {
    //     if (candy)
    //     {
    //         ree--;
    //         candy--;
    //     }
    //     cout << ree << " ";
    //     total_ree += (ree * ree);
    // }
    // cout << endl;

    // cout << total_ree;
}