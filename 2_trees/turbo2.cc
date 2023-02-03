#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
using namespace std;

#define vi vector<int>
#define li list<int>
#define umii unordered_map<int, int>
#define umip unordered_map<int,  std::list<int>::iterator> 

void get_values(li & values, umip & values_tracker)
{
    int loops{}, cur_value{};

    scanf("%d", &loops);
    for (int i{}; i < loops; i++)
    {
        scanf("%d", &cur_value);
        values.push_back(cur_value);
        values_tracker[cur_value] = --values.end();
    }

    values.push_front(0);
    values.push_back(0);
}


void go_left(li &values, umip & values_index, auto min_sorted, auto begin)
{
    auto swaps {distance(++min_sorted, begin)};
    printf("%ld\n", swaps);
    values.splice(min_sorted, values, begin);
    // --min_sorted;
    // int val {*begin};
    // values.erase(begin);
    // values.insert(min_sorted, val);
    // values_index[val] = min_sorted;
}


void go_right(li &values, umip & values_index, auto & max_sorted, auto & begin)
{
    auto swaps {distance(begin, max_sorted)};
    printf("%ld\n", swaps - 1);
    // values.splice(begin, values, max_sorted);
    int val {*begin};
    values.erase(begin);
    values.insert(max_sorted, val);
    values_index[val] = max_sorted;
    --max_sorted;
}


void apply_turbo(li &values, umip &values_index)
{
    size_t min{1}, max{values.size() - 2};
    auto min_it {values.begin()};
    auto max_it {--values.end()};

    for (size_t i{0}; i < values.size() - 2; i++)
    {
        if (i % 2 == 0)
        {
            // go left
            go_left(values, values_index, min_it, values_index[min]);
            min_it = values_index[min];
            min++;
        }
        else
        {
            // go right
            auto it = values_index[max];
            go_right(values, values_index, max_it, values_index[max]);
            // max_it = values_index[max];
            --max;
        }
    }
}

int main()
{
    li values{};
    umip values_index{};
    get_values(values, values_index);
    apply_turbo(values, values_index);
    return 0;
}