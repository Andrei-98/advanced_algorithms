/*
Author: Andrei Plotoaga (andpl509)
Date: 2023-02-27

Implementation of Prim's algorithm for finding the MST of a graph(adjacency list). 

Time Complexity:
prims()
    - O(|E| * log(|E|))
    - E = edge 
    - I am using a priority queue to keep track of the smallest next edge that needs to be processed. I am going to be pushing and popping from the priority queue at most E times. And because push and pop operations on a priority queue cost log (E). Total time complexity results in O(|E| * log(|E|))

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


// make a graph from input as an adjency list;
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


// sort the mst in a "lexicographic" for kattis to realise my solution is correct
void sort_mst(vvp & mst) {
    for (auto & adj : mst) {
        sort(adj.begin(), adj.end(), [](const pii& a, const pii& b) {
            if (a.first != b.first) {
                return a.first < b.first;
            }
            return a.second < b.second;
        });
    }
}


/*
Implementation of Prim's MST. A greedy algorithm that uses a priority queue of edges
to always pick edge with the smalles cost to include in the MST.

How it works step by step:
- It start from an arbriraty node and adds to the PQ all of the edges that extend from 
the start node.
- mark the node as visited
- process the next smallest edge from the PQ
- check if the destination node has been visited
- if not:
    - add edge weight to total cost
    - include edge in MST 
    - add all of the destination node's edges to the PQ
    - repeat
*/

vvp prims(vvp const& adj_list, int const start = 0)
{
    vvp mst(adj_list.size());
    vector<bool> visited(adj_list.size(), false);
    pq next_edge{};
    size_t msp_size{0}; 
    long long total_cost{0};

    // start from 0 or given start
    for (auto const& neighbour : adj_list[start])
        next_edge.push(Edge{start, neighbour.first, neighbour.second});
    visited[start] = true;

    while(!next_edge.empty() && adj_list.size() - 1!= msp_size)
    {
        Edge edge{next_edge.top()};
        next_edge.pop();

        if (visited[edge.to])
            continue;
        
        total_cost += edge.weight;

        // "lexicogaphic order"
        if (edge.from > edge.to)
            mst[edge.to].emplace_back(make_pair(edge.from, edge.weight));
        else
            mst[edge.from].emplace_back(make_pair(edge.to, edge.weight));
        visited[edge.to] = true;
        msp_size++;

        for (auto const& neighbour : adj_list[edge.to])
            next_edge.push(Edge{edge.to, neighbour.first, neighbour.second});
    }


    if(adj_list.size() - 1 != msp_size)
    {
        printf("Impossible\n");
        return vvp{};
    }
    else
    {
        printf("%lld\n", total_cost);
        return mst;
    }
}


void solve(vvp const& mst)
{
    for (size_t node{0}; node < mst.size(); node++)
    {
        for (size_t edge{0}; edge < mst[node].size(); edge++)
        {
                printf("%ld %d\n", node, mst[node][edge].first);
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

        vvp adj_list{build_adj_list(nodes, edges)};
        vvp mst{prims(adj_list, 0)};
        sort_mst(mst);
        solve(mst);
    }

    return 0;
}
