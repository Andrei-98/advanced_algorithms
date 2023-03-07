/*
Author: Andrei Plotoaga (andpl509)
Date: 2023-03-07
*/

#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm> 

using namespace std;

#define ld long double
#define vvp vector<vector<pair<int, ld>>>
#define vp vector<pair<int, ld>>
#define pii pair<int, ld>
#define vi vector<int>
#define vld vector<ld>
#define pvv pair<vector<int>, vector<int>>

class PrioQueueComparator
{
public:
    bool operator()(const pii &a, const pii &b)
    {
        return a.second < b.second;
    }
};

#define pq priority_queue<pii, vp, PrioQueueComparator>
const int INF = numeric_limits<int>::max();


vvp build_adj_list(int const nodes, int const edges)
{
    vvp adj_list(nodes);
    int from{}, to{};
    ld weight{};

    for (int i{0}; i < edges; i++)
    {
        scanf("%d %d %Lf", &from, &to, &weight);
        adj_list[from].emplace_back(make_pair(to, weight));
        adj_list[to].emplace_back(make_pair(from, weight));
    }

    return adj_list;
}


ld dijkstra(vvp adj_list, int const start_index = 0)
{
    vld shortest_dist(adj_list.size(), 0);
    vi prev_vertex(adj_list.size(), 0);
    vector<bool> visisted(adj_list.size(), false);
    pq next_vertex_queue{};

    shortest_dist[start_index] = 1.0f;
    next_vertex_queue.push(make_pair(start_index, 1.0f));
    int node{};
    ld new_shortest{};

    while (!next_vertex_queue.empty())
    {
        node = next_vertex_queue.top().first;
        next_vertex_queue.pop();

        for (auto const &neighbour : adj_list[node])
        {
            if (!visisted[neighbour.first])
            {
                new_shortest = shortest_dist[node] * neighbour.second;
                if (new_shortest > shortest_dist[neighbour.first])
                {
                    prev_vertex[neighbour.first] = node;
                    shortest_dist[neighbour.first] = new_shortest;
                    next_vertex_queue.push(make_pair(neighbour.first, new_shortest));
                }
            }
        }
        visisted[node] = true;
    }

    return shortest_dist[adj_list.size() - 1];
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
        ld get_shorty{dijkstra(adj_list)};
        printf("%.4Lf\n", get_shorty);
    }

    return 0;
}
