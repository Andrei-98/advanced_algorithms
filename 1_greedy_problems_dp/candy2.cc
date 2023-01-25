#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

typedef int ll;

using namespace std;

void print_vector(vector<ll> brats, string const &line = "BRATS :")
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

ll get_smallest_brat(vector<ll> const &brats, ll const candy)
{
    ll estimated_cost{};
    ll prev_brat{brats[0]};
    ll index{0};
    ll step{};

    for (size_t i{1}; i < brats.size(); i++)
    {
        step = prev_brat - brats[i];
        estimated_cost += step;
        prev_brat = brats[i];

        index++;
        if (estimated_cost >= candy - 1 || step > candy / 2)
        {
            index = i - 1;
            break;
        }
    }

    cerr << "Smallest number is " << brats[index] << endl;

    return index;
}

void normalize_vector(vector<ll> &brats, ll &candy, ll const up_to_index)
{
    ll smallest_value{brats[up_to_index]};
    ll normalization{};

    for (int i{0}; i < up_to_index; i++)
    {
        normalization = brats[i] - smallest_value;
        brats[i] -= normalization;
        cerr << candy << " - " << normalization << endl;
        candy -= normalization;
    }
}

ll get_ree_level(vector<ll> &brats, ll &candy, ll const smallest_brat_index)
{
    ll total_candy = candy;
    bool deal_bags_candy{false};
    ll rest{0};

    cerr << candy % (smallest_brat_index + 1) << "rest" << endl;
    rest = candy % (smallest_brat_index + 1);
    candy = candy / (smallest_brat_index + 1);
    deal_bags_candy = true;

    ll anger{};
    for (size_t i{}; i <= brats.size(); i++)
    {
        if (brats[i] == 0)
            continue;

        if (total_candy > 0 && deal_bags_candy)
        {
            if(candy > brats[i])
            {
                total_candy -= brats[i];
                brats[i] = 0;
                continue;
            }
            else
            {
                total_candy -= candy;
                brats[i] -= candy;
            }

            if (rest > 0)
            {
                brats[i]--;
                rest--;
                total_candy--;
            }
        }
        else if (total_candy > 0)
        {
            brats[i]--;
            candy--;
            total_candy--;
        }

        cerr << "REE " << brats[i] << endl;
        anger += (brats[i] * brats[i]);
    }

    return anger;
}

int main()
{
    ll candy{};
    cin >> candy;

    vector<ll> brats{get_candy_demands()};
    ll const smallest_brat_index{get_smallest_brat(brats, candy)};
    cerr << smallest_brat_index << " <" << brats.size() << endl;
    if (smallest_brat_index != brats.size())
        normalize_vector(brats, candy, smallest_brat_index);
    print_vector(brats, "AFTER NORMALIZAION :");
    cout << get_ree_level(brats, candy, smallest_brat_index);
}