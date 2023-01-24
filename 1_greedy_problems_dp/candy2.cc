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


ll get_smallest_brat(vector<ll> const& brats, ll const candy)
{
    ll estimated_cost{};
    ll prev_brat {brats[0]};
    ll index {1};

    for (size_t i{1}; i <= brats.size(); i++)
    {
        estimated_cost += prev_brat - brats[i];
        prev_brat = brats[i];


        if(estimated_cost >= candy)
        {
            index = i - 1; 
            break;
        }
    }

    cerr << "Smallest number is " << brats[index] << endl;

    return index;
}


void normalize_vector(vector<ll> & brats, ll & candy, ll const up_to_index)
{
    ll smallest_value {brats[up_to_index]};
    ll normalization {};
    cout << "candy " << candy << endl;

    for (int i{0}; i < up_to_index; i++)
    {
        normalization = brats[i] - smallest_value;
        brats[i] -= normalization;
        cerr << candy << " - " << normalization << endl;
        candy -= normalization;
    }
    cout << "candy _ " << candy << endl;
}


ll get_ree_level(vector<ll> & brats, ll & candy, ll const smallest_brat_index)
{
    cout << "up to index " << smallest_brat_index << endl;
    ll total_candy = candy;
    bool deal_bags_candy {false};

    if (candy > (int)brats.size())
    {
        if(candy % brats.size() != 0)
            brats[0] -= 1;
        candy = candy / brats.size();
        deal_bags_candy = true;
    }

    ll anger {};
    for (size_t i{}; i <= brats.size(); i++)
    {
        if (total_candy > 0 && deal_bags_candy)
        {
            total_candy -= candy;
            brats[i] -= candy;
        } else if (total_candy > 0)
        {
            brats[i]--;
            candy--;
            total_candy--;
        }

        cerr << "andger " << brats[i] << endl;
        anger += (brats[i] * brats[i]);
    }

    return anger;
}



int main() 
{
    ll candy{};
    cin >> candy;

    vector<ll> brats {get_candy_demands()};
    ll const smallest_brat_index {get_smallest_brat(brats, candy)};
    cerr << smallest_brat_index << " <" << brats.size() << endl;
    if(smallest_brat_index != brats.size())
        normalize_vector(brats, candy, smallest_brat_index);
    print_vector(brats, "AFTER NORMALIZAION :");
    cout << get_ree_level(brats, candy, smallest_brat_index) << '\n';
    print_vector(brats);
}