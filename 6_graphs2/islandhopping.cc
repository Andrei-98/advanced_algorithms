/*
Author: Andrei Plotoaga (andpl509)
Date: 2023-02-27
*/

#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm> 
#include <cmath>

using namespace std;

#define vvp vector<vector<pair<double, double>>>
#define vp vector<pair<double, double>>
#define vvi vector<vector<int>>
#define ve vector<Edge>
#define pii pair<double, double>
#define vi vector<int>
#define pvv pair<vector<int>, vector<int>>

struct Edge
{
    double from{0}, to{0}, weight{0};
    bool operator<(Edge const& other) const
    {
        return weight > other.weight;
    }
};

#define pq priority_queue<Edge, ve>

vp get_input()
{
    int iterations{};
    double x{}, y{};
    vp islands{};

    scanf("%d", &iterations);

    while(iterations--)
    {
        scanf("%lf %lf", &x, &y);
        islands.emplace_back(make_pair(x, y));
    }
    return islands;
}


double euclidean_distance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}


// make a graph from input as an adjency list;
vvp build_adj_list(vp const& islands)
{
    vvp adj_list(islands.size());

    double weight{};

    for (size_t i{0}; i < islands.size(); i++)
    {
        for (size_t ii{0}; ii < islands.size(); ii++)
        {
            if (i == ii)
                continue;
            
            weight = euclidean_distance(islands[i].first, islands[i].second,
                                        islands[ii].first, islands[ii].second);
            
            adj_list[i].emplace_back(make_pair(ii, weight));
        }
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



vvp prims(vvp const& adj_list, double const start = 0)
{
    vvp mst(adj_list.size());
    vector<bool> visited(adj_list.size(), false);
    pq next_edge{};
    size_t msp_size{0}; 
    double total_cost{0};

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

    printf("%lf\n", total_cost);
    return mst;
}


int main()
{
    int iterations{};
    scanf("%d", &iterations);

    while (iterations--)
    {
        vp islands{get_input()};
        vvp adj_list{build_adj_list(islands)};
        vvp mst{prims(adj_list, 0)};
    }

    return 0;
}
 
