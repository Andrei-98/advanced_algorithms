#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define mii map<int, int>
#define umii unordered_map<int, int>
#define si set<int>
#define sc set<char>


vi get_values(vi &values, umii &values_tracker)
{
    int loops{}, cur_value{};

    // scanf("%d", &loops);
    cin >> loops;
    for (int i{}; i < loops; i++)
    {
        // scanf("%d", &cur_value);
        cin >> cur_value;
        values.push_back(cur_value);
        values_tracker[cur_value] = i;
    }

    return values;
}


void go_left(vi &values, umii &values_index, int cur_index, int up_to)
{
    int counter = 0;
    int value {values[cur_index]};
    int temp{0};

    while (cur_index != up_to - 1)
    {
        temp = values_index[value];
        values_index[value] = values_index[values[cur_index - 1]];
        values_index[values[cur_index - 1]] = temp;
        swap(values[cur_index], values[cur_index - 1]);
        counter++;
        cur_index--;
    }

    printf("%d\n", counter);
}


void go_right(vi &values, umii &values_index, int cur_index, int up_to)
{
    int counter = 0;
    int value {values[cur_index]};
    int temp{0};

    while (cur_index != up_to - 1)
    {
        temp = values_index[value];
        values_index[value] = values_index[values[cur_index + 1]];
        values_index[values[cur_index + 1]] = temp;
        swap(values[cur_index], values[cur_index + 1]);
        counter++;
        cur_index++;
    }
    printf("%d\n", counter);
}


void apply_turbo(vi &values, umii &values_index)
{
    int cur_index{}, min{1}, max{values.size()};


    for (size_t i{0}; i < values.size(); i++)
    {
        cur_index = values_index[i];

        if(i % 2 == 0)
        {
            // go left
            cur_index = values_index[min];
            go_left(values, values_index, cur_index, min);
            min++;

        } else
        {
            // go right
            cur_index = values_index[max];
            go_right(values, values_index, cur_index, max);
            max--;

        }
    }
}


int main()
{
    vi values{};
    umii values_index{};
    get_values(values, values_index);
    apply_turbo(values, values_index);
    return 0;
}