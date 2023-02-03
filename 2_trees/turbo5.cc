#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <list>
#include <bitset>
using namespace std;

// #define vi vector<int>
#define umii unordered_map<int, int>
#define map map<int, bool>

class FenwickTree
{
private:
    vector<int> tree;

public:
    FenwickTree(int n) : tree(n + 1) {}

    int sum(int index)
    {
        int res = 0;
        while (index > 0)
        {
            res += tree[index];
            index -= (index & -index);
        }
        return res;
    }

    void add(int index, int value)
    {
        while (index < tree.size())
        {
            tree[index] += value;
            index += (index & -index);
        }
    }

    int rangeSum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }
};

void get_values(umii &values_tracker)
{
    int loops{}, cur_value{};

    scanf("%d", &loops);
    for (int i{}; i < loops; i++)
    {
        scanf("%d", &cur_value);
        values_tracker[cur_value] = i;
    }
}

void apply_turbo(vi &values, umii &values_index)
{
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
    umii values_index{};
    

    get_values(values, values_index);
    apply_turbo(values, values_index);
    return 0;
}