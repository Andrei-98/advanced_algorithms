/*
Author: Andrei Plotoaga (andpl509)
Date: 2023-02-27

*/

#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm> 

using namespace std;

#define vvp vector<vector<pair<int, int>>>
#define vvi vector<vector<int>>
#define ve vector<Edge>
#define vp vector<pair<int, int>>
#define pii pair<int, int>
#define vi vector<int>
#define pvv pair<vector<int>, vector<int>>

struct Edge
{
    int from{0}, to{0}, weight{0};
    bool operator<(Edge const& other) const
    {
        return weight > other.weight;
    }
};

#define pq priority_queue<Edge, ve>
const int INF = numeric_limits<int>::max();


vvp build_adj_list(int const nodes, int const edges)
{
    vvp adj_list(nodes);
    int from{}, to{}, weight{};

    for (int i{0}; i < edges; i++)
    {
        scanf("%d %d %d", &from, &to, &weight);
        adj_list[from].emplace_back(make_pair(to, weight));
        adj_list[to].emplace_back(make_pair(from, weight));
    }

    return adj_list;
}

vvp prims(vvp const& adj_list, bool & valid_mst, int const start = 0)
{
    vvp msp(adj_list.size());
    vector<bool> visited(adj_list.size(), false);
    pq next_edge{};
    size_t msp_size{0}; 
    int total_cost{0};
    valid_mst = true;

    // start from 0 or given start
    for (auto const& neighbour : adj_list[start])
    {
        next_edge.push(Edge{start, neighbour.first, neighbour.second});
    }
    visited[start] = true;

    while(!next_edge.empty() && adj_list.size() - 1!= msp_size)
    {
        Edge edge{next_edge.top()};
        next_edge.pop();

        if (visited[edge.to])
            continue;
        
        total_cost += edge.weight;

        msp[edge.from].emplace_back(make_pair(edge.to, edge.weight));
        visited[edge.to] = true;
        msp_size++;

        for (auto const& neighbour : adj_list[edge.to])
        {
            next_edge.push(Edge{edge.to, neighbour.first, neighbour.second});
        }
    }

    if(adj_list.size() - 1 != msp_size)
    {
        valid_mst = false;
        printf("Impossible\n");
    }
    else
        printf("%d\n", total_cost);

    for (auto& v : msp) {
    sort(v.begin(), v.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    });
}

    return msp;
}


void solve(vvp const& msp)
{
    for (size_t node{0}; node < msp.size(); node++)
    {
        for (size_t edge{0}; edge < msp[node].size(); edge++)
        {
            printf("%ld %d\n", node, msp[node][edge].first);
        }
    }

}


int main()
{
    while (true)
    {
        int nodes{}, edges{};
        scanf("%d %d", &nodes, &edges);

        if (nodes == 0 && edges == 0)
            break;
        
        bool valid_mst {};

        vvp adj_list{build_adj_list(nodes, edges)};
        vvp msp{prims(adj_list, valid_mst, 0)};

        if (valid_mst)
            solve(msp);
    }

    return 0;
}
