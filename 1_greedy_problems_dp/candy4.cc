#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

#define vi vector<int>

using namespace std;

void print_vector(vi brats, string const &line = "BRATS :")
{
    cerr << line;
    for (int brat : brats)
    {
        cerr << brat << " ";
    }
    cerr << endl;
}

vi get_candy_demands()
{
    vi brats{};
    int loops{}, cur_brat{};

    cin >> loops;

    for (int i{}; i < loops; i++)
    {
        cin >> cur_brat;
        brats.push_back(cur_brat);
    }

    sort(brats.begin(), brats.end(), greater<int>());

    return brats;
}


// return the index of the brat 
size_t get_smallest_brat(vi & brats, int & candy)
{
    int step{0};
    int additional_cost {0}; // cost to normalize the prev brats
    int total_candy_cost {candy};
    int normalization_counter{0}; // counter of all brats that whould have to be normalized
    int prev{brats[0]};
    int current{0};
    size_t index{1};

    // apply the step 100 50 would be 50 in this case
    // keep track of candy that would have to be spend to normalize prev values
    for(size_t i{1}; i < brats.size(); i++)
    {
        current = brats[i];
        step = prev - current;
        additional_cost = normalization_counter * step;
    
        if(total_candy_cost >= step + additional_cost)
        {
            total_candy_cost -= step + additional_cost;
            brats[i - 1] -=  step; 
            candy -= step;
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
    // rest of candy has to be distributed equally to every brat up to index
    cerr << "Normalize up to index = " << index << " value " << brats[index] << endl;
    print_vector(brats, "AFTER NORMALIZATION ");
    cerr << "Candy left is " << candy << endl;
    
    return index;
}


void normalize_vector(vi &brats, int &candy, int const up_to_index)
{
    int smallest_value{brats[up_to_index]};
    int normalization{};

    for (int i{0}; i < up_to_index; i++)
    {
        normalization = brats[i] - smallest_value;
        brats[i] -= normalization;
        cerr << candy << " - " << normalization << endl;
        candy -= normalization;
    }
}


void deal_remeaning_candy(vi & brats, int candy, size_t up_to_index)
{

    size_t rest {candy % (up_to_index + 1)};
    size_t deal {candy / (up_to_index + 1)};
    int total_ree {0};

    for(size_t i{0}; i <= up_to_index; i++)
    {
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

        total_ree += (brats[i] * brats[i]);
    }

    print_vector(brats, "AFTER DEALING CANDY");
    if(candy != 0)
        throw runtime_error("thre is still candy!!!");
    cout << total_ree << endl;
}


int main()
{
    int candy{0};
    cin >> candy;
    vi brats {get_candy_demands()};
    size_t up_to_index {get_smallest_brat(brats, candy)};
    normalize_vector(brats, candy, up_to_index);
    print_vector(brats, "after normalization ");
    cout << "candy left is " << candy << endl;
    deal_remeaning_candy(brats, candy, up_to_index);
}