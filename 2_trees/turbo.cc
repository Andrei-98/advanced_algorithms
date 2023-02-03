#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

#define vi vector<int>
#define umii unordered_map<int, int>

vi get_values(vi &values, umii &values_tracker)
{
    int loops{}, cur_value{};

    scanf("%d", &loops);
    values.resize(loops);
    for (int i{}; i < loops; i++)
    {
        scanf("%d", &cur_value);
        values[i] = cur_value;
        values_tracker[cur_value] = i;
    }

    return values;
}


void go_left(vi &values, umii &values_index, int cur_index, int up_to)
{
    int counter = 0;
    int value{values[cur_index]};
    int temp{0};

    while (cur_index != up_to - 1)
    {
        swap(values_index[value], values_index[values[cur_index - 1]]);
        swap(values[cur_index], values[cur_index - 1]);
        counter++;
        cur_index--;
    }

    printf("%d\n", counter);
}


void go_right(vi &values, umii &values_index, int cur_index, int up_to)
{
    int counter = 0;
    int value{values[cur_index]};
    int temp{0};

    while (cur_index != up_to - 1)
    {
        swap(values_index[value], values_index[values[cur_index + 1]]);
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
        if (i % 2 == 0)
        {
            // go left
            cur_index = values_index[min];
            go_left(values, values_index, cur_index, min);
            min++;
        }
        else
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