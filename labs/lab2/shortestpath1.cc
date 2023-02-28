/*
Author: Andrei Plotoaga (andpl509)
Date: 2023-02-23

My implementation for Dijkstra's shortest path algorithm. (adjacency list)

djikstra():
My approach to solving the problem was to:
    - visit the unvisited vertex with the smallest known distance from the start vertex. First time around this will be the start node itself. I keep track of the smallest distance by having a priority_queue of pair<int, int> where the first is the node and second is the distance from the start_node to that node. Queue is sorted on second.

    - once a vertex is chosen i will look at all of it's unvisited neighbours and calculate the distance from the start node to the neighbour.
    - if this new distance is less than the known distance i will update the shortest distance vector and push the vertex on the queue
    - current vertex will than be set to visted.
    - repeat until queue is empty.


Time complexity:
dijkstra()
    - O(|V + E| * log(|V|)) 
    - V = vertices
    - E = edges
    - log(V) <- cost of updating the priority_queue



reconstruct_path() for one node (described below)
    - O(|V|) 

!Obs: Call to reconstruct_path is commented out in solve_query.
*/

#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm> 

using namespace std;

#define vvp vector<vector<pair<int, int>>>
#define vp vector<pair<int, int>>
#define pii pair<int, int>
#define vi vector<int>
#define pvv pair<vector<int>, vector<int>>

class PrioQueueComparator
{
public:
    bool operator()(const pii &a, const pii &b)
    {
        return a.second > b.second;
    }
};

#define pq priority_queue<pii, vp, PrioQueueComparator>
const int INF = numeric_limits<int>::max();


vvp build_adj_list(int const nodes, int const edges)
{
    vvp adj_list(nodes);
    int from{}, to{}, weight{};

    for (int i{0}; i < edges; i++)
    {
        scanf("%d %d %d", &from, &to, &weight);
        adj_list[from].emplace_back(make_pair(to, weight));
    }

    return adj_list;
}


pvv dijkstra(vvp adj_list, int const start_index)
{
    vi shortest_dist(adj_list.size(), INF);
    vi prev_vertex(adj_list.size(), INF);
    vector<bool> visisted(adj_list.size(), false);
    pq next_vertex_queue{};

    shortest_dist[start_index] = 0;
    next_vertex_queue.push(make_pair(start_index, 0));
    int node{}, new_shortest{};

    while (!next_vertex_queue.empty())
    {
        node = next_vertex_queue.top().first;
        next_vertex_queue.pop();

        for (auto const &neighbour : adj_list[node])
        {
            if (!visisted[neighbour.first])
            {
                new_shortest = shortest_dist[node] + neighbour.second;
                if (new_shortest < shortest_dist[neighbour.first])
                {
                    prev_vertex[neighbour.first] = node;
                    shortest_dist[neighbour.first] = new_shortest;
                    next_vertex_queue.push(make_pair(neighbour.first, new_shortest));
                }
            }
        }
        visisted[node] = true;
    }

    return make_pair(shortest_dist, prev_vertex);
}

/*
Once dijkstra's has run we can easily rebuild the shortest path from a start vertex to a given vertex by using the parents vector which keeps track of the parent vertex that got us there.
+------+--------------+---------+
| Node | Total Cost   | Parents |
+------+--------------+---------+
|   0  |      -       |    -    |
|   1  |      3       |    3    |
|   2  |      7       |    4    |
|   3  |      1       |    0    |
|   4  |      2       |    3    |
+------+--------------+---------+

For example the path from 0 to 2 has a total cost of 7 through vertex 4 (parent column).
The shortest path to vertex 4 is through vertex 3.
And the shortest path to vertex 3 is through vertex 0

So the path from 0 to 2 is 0 3 4 2.
*/
vi reconstruct_path(int const start, int const to, vi const& parents)
{
    vi path{};
    int current_node{to};

    while(true)
    {
        path.emplace_back(current_node);
        if (current_node == start)
            break;
        current_node = parents[current_node];
    }

    reverse(path.begin(), path.end());

    printf("Reconstructed path: ");
    for (auto const i : path)
    {
        printf("%d ", i);
    }
    printf("\n");

    return path;
}


// solves the queries from kattis
// get distance from start to X
void solve_queries(int const start, int const queries, 
                     vi const &distance, vi const &parents)
{
    int to{};

    for (int i{0}; i < queries; i++)
    {
        scanf("%d\n", &to);
        if (distance[to] == INF)
            printf("Impossible\n");
        else
        { 
            // reconstruct_path(start, to, parents);
            printf("%d\n", distance[to]);
        }
    }
}


int main()
{
    while (true)
    {
        int nodes{}, edges{}, queries{}, start_index{};
        scanf("%d %d %d %d", &nodes, &edges, &queries, &start_index);

        if (nodes == 0 && edges == 0 && queries == 0 && start_index == 0)
            break;

        vvp adj_list{build_adj_list(nodes, edges)};
        pvv distance_parents{dijkstra(adj_list, start_index)};

        solve_queries(start_index, queries, distance_parents.first, 
                      distance_parents.second);
    }

    return 0;
}
