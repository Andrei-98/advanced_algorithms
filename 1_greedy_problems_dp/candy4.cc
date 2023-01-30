#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

typedef unsigned long long ll;
#define vll vector<unsigned long long>

using namespace std;

vll get_candy_demands()
{
    vll brats{};
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

// return the index of the brat 
size_t get_smallest_brat(vll & brats, ll & candy)
{
    ll step{0};
    ll additional_cost {0}; // cost to normalize the prev brats
    ll total_candy_cost {candy};
    ll normalization_counter{0}; // counter of all brats that whould have to be normalized
    ll prev{brats[0]};
    ll current{0};
    size_t index{1};

    // apply the step 100 50 would be 50 in this case
    // keep track of candy that would have to be spend to normalize prev values
    for(ll i{1}; i < brats.size(); i++)
    {
        current = brats[i];
        step = prev - current;
        additional_cost = normalization_counter * step;
    
        if(total_candy_cost >= step + additional_cost)
        {
            total_candy_cost -= step + additional_cost;
            brats[i - 1] -=  step; 
            candy -= step + additional_cost;
            prev = current;
            normalization_counter++;
        } else 
        {
            index--;
            break;
        }
        index++;
    }

    if (index == brats.size())
        index = brats.size() - 1;
    
    return index;
}


void deal_remeaning_candy(vll & brats, ll candy, ll up_to_index)
{

    ll deal {candy / (up_to_index + 1)};
    ll rest {deal * (up_to_index + 1)};
    rest = candy - rest;
    ll total_ree {0};
    cerr << "candy " << candy << " % " << up_to_index + 1 << " == " << rest << endl;


    for(ll i{0}; i < brats.size(); i++)
    {
        if(i <= up_to_index)
        {
            // apready paid for this
            brats[i] = brats[up_to_index];
        }
        
        if(candy > 0)
        {
            candy -= deal;
            brats[i] -= deal;
            if(rest > 0)
            {
                candy--;
                rest--;
                brats[i]--;
            }
        }
        if(brats[i] < 0)
            throw runtime_error("bad");

        cerr << brats[i] << " * " << brats[i] << endl;
        total_ree += (brats[i] * brats[i]);
    }

    if(candy != 0 || rest != 0)
        throw runtime_error("you done goofed");

    cout << total_ree << endl;
}


int main()
{
    ll candy{0};
    cin >> candy;
    vll brats {get_candy_demands()};
    ll up_to_index {get_smallest_brat(brats, candy)};
    deal_remeaning_candy(brats, candy, up_to_index);
}