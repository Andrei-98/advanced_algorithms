#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <list>
#include <bitset>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define li list<int>
#define mii map<int, int>
#define umii unordered_map<int, int>
#define si set<int>
#define sc set<char>
#define pq priority_queue<int, std::vector<int>, std::greater<int>>

template <class T>
void print_v(vector<T> &v)
{
    cout << "{";
    for (auto x : v)
        cout << x << ",";
    cout << "\b}";
}

void yes() { cout << "YES\n"; }
void no() { cout << "NO\n"; }

void get_input(vi &edges, umii &edges_counter, pq &available_nodes)
{
    int loops1{0}, cur_int{0};

    cin >> loops1;
    edges.resize(loops1);
    bitset<200002> bitmap{};

    // while(loops1--)
    for (int i{0}; i < loops1; i++)
    {
        cin >> cur_int;
        // edges.push_back(cur_int);
        edges[i] = cur_int;
        edges_counter[cur_int] += 1;
        bitmap.set(cur_int, 1);
    }

    for (int i{1}; i <= loops1; i++)
    {
        if (!bitmap.test(i))
        {
            // cout << "set " << i << endl;
            available_nodes.push(i);
        }
    }
}

void reconstruct(vi &edges, umii &edges_counter, pq &available_nodes)
{
    int cur_value{};

    for (size_t i{}; i < edges.size(); i++)
    {
        cur_value = edges[i];
        if (available_nodes.empty())
        {
            printf("Error");
            break;
        }

        int chopped_node{available_nodes.top()};
        available_nodes.pop();

        // cout << chopped_node << '\n';
        printf("%d\n", chopped_node);

        if (edges_counter.count(cur_value))
        {
            edges_counter[cur_value]--;

            if (edges_counter[cur_value] == 0)
            {
                available_nodes.push(cur_value);
                // map.erase(cur_value) ? maybe better? time complexity should be 1
            }
        } else {
            printf("Error");
        }
    }
}

int main()
{
    // 6 7 7 4 4 4 7       -       1 2 3 5 6 4
    // 6 1 1 1 1 1 7       -       2 3 4 5 6 1
    // 6 7 7 4 4 2 7       -       1 3 5 6 4 2
    // 

    vi edges{};
    // edges repeat, when an edges is no longer in counter it can be added
    // to available_nodes
    umii edges_counter{};
    priority_queue<int, std::vector<int>, std::greater<int>> available_nodes{};

    // seg fault in get_input() ?
    get_input(edges, edges_counter, available_nodes);
    reconstruct(edges, edges_counter, available_nodes);

    return 0;
}