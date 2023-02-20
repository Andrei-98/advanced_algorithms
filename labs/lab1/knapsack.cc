// Author: Andrei Plotoaga
// Date: 2023-02-07
/*
My implemenation of the Knapsack problem.
My approach to solving this was to create solutions to subproblems in order to help me solve the whole problem using my previous solutions.

Time complexity:
  get_optimal_gear - O(n*c)
                   - n = number of items
                   - c = capacity
  
  show_chosen_gear - O(n)
                   - n = number of items
*/

#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

#define ll long long
#define vi vector<int>
#define vvi vector<vector<int>>
#define vp vector<pair<int, int>>


vp read_items(int objects)
{
    vp items{};
    int value{}, weight{};
    while(objects--)
    {
        scanf("%d%d", &value, &weight);
        items.push_back({value, weight});
    }
    return items;
}


/*
Iterate through the items given.
A nested loop for the capacity of each iteam. starting from 0 to the given capacity.

For each iteartion of the second loop I ask:
what is the max value i can get with a weight constraint of X
if i cant fit anything i just copy from my previous answered subproblems.

If I can fit my item:
    - i subtract the weight of the item and check my previous solved subproblem for the max value for the remaning weight(Y) 
    - if the value of the item + Y > the previous soved subproblem use this value instead
*/

vvi get_optimal_gear(int max_capacity, vp const& all_items)
{
    vvi subproblems{};
    // deal with first iteration of capacity loop
    subproblems.emplace_back(vector<int>(max_capacity + 1, 0)); 
    int value{}, weight{}, above{}, chosen{}, s_index{};

    for (size_t i{}; i < all_items.size(); i++) 
    {
        value = all_items[i].first;
        weight = all_items[i].second;

        vi new_vec{};
        subproblems.emplace_back(new_vec);
        s_index = i + 1;

        for (int capacity {0}; capacity <= max_capacity; capacity++)
        {
            above = subproblems[s_index - 1][capacity];
            if (capacity >= weight)
            {
                chosen = value + subproblems[s_index - 1][capacity - weight];
                if(chosen > above)
                    subproblems[s_index].emplace_back(chosen);
                else
                    subproblems[s_index].emplace_back(above);
            } else 
            {
                subproblems[s_index].emplace_back(above);
            }
        }
    }
    subproblems.erase(subproblems.begin());
    return subproblems;
}


/*
Now that all the subproblems have been resolved, i know that the last item in the vector subproblems has the max value solution. starting from there i go backwords and check:

Is the above solution larger?
Yes - means we didnt choose this item
No - means that we chose this item
*/
void show_chosen_gear(vvi const& subproblems, vp const& all_items, int capacity)
{
    vi gear_index{};
    int total_value{subproblems[subproblems.size() - 1][capacity]};
    int weight{};
    int above{};

    for(int i{(int)all_items.size() - 1}; i >= 0; i--)
    { 
        total_value = subproblems[i][capacity];
        weight = all_items[i].second;

        if(i != 0)
            above = subproblems[i - 1][capacity];
        else
            above = 0;

        if (total_value > above)
        {
            gear_index.emplace_back(i);
            capacity -= weight;
        }
    }

    printf("%ld\n", gear_index.size());
    copy(gear_index.rbegin(), gear_index.rend(), ostream_iterator<int>(cout, " "));
    printf("\n");
}


void knapsack()
{
    int capacity{}, objects{};

    scanf("%d%d", &capacity, &objects);
    vp all_items {read_items(objects)};
    vvi optimal_gear{};
    optimal_gear = get_optimal_gear(capacity, all_items);
    show_chosen_gear(optimal_gear, all_items, capacity);
}


int main()
{
    int tests{30};
    while(tests--)
        knapsack();

    return 0;
}