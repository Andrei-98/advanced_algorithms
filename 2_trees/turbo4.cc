#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <bitset>
using namespace std;

#define vi vector<int>
#define bs bitset<100001>
#define umii unordered_map<int, int>

void get_values(vi & values, umii & values_tracker)
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
}
    // std::bitset<8> bs{0b00000110};
    // int startIndex = 1, endIndex = 5;
    // std::bitset<8> mask = (1 << (endIndex - startIndex + 1)) - 1;
    // std::bitset<8> sub_bs = (bs >> startIndex) & mask;
    // int count = sub_bs.count();

void go_left(int value, umii & values_index, bs & bitmap)
{
    int cur_val_index {values_index[value]};
    int should_be_on {value - 1};
    bitset<100001> mask = (1 << (cur_val_index - should_be_on + 1)) - 1;
    bitset<100001> sub_mask = (bitmap >> should_be_on) & mask;
    int set_bits {sub_mask.count()};
    
    int swaps { cur_val_index - should_be_on - set_bits};
    printf("%d\n", swaps);
    bitmap.set(cur_val_index);
}

void go_right(int value, umii & values_index, bs & bitmap)
{
    int cur_val_index {values_index[value]};
    int should_be_on {value - 1};
    bitset<100001> mask = (1 << (should_be_on - cur_val_index + 1)) - 1;
    bitset<100001> sub_mask = (bitmap >> cur_val_index) & mask;
    int set_bits {sub_mask.count()};
    
    int swaps { should_be_on - cur_val_index - set_bits};
    printf("%d\n", swaps);
    bitmap.set(cur_val_index);
}


void apply_turbo(vi & values, umii & values_index)
{
    bs bitmap{};
    size_t min{1}, max{values.size()};

    for (size_t i{0}; i < values.size(); i++)
    {
        if (i % 2 == 0)
        {
            // go left
            go_left(min, values_index, bitmap);
            min++;
        }
        else
        {
            // go right
            go_right(max, values_index, bitmap);
            --max;
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