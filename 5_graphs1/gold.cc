#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

#define vvp vector<vector<pair<int, char>>>
#define si unordered_set<int>
#define qp queue<pair<int, char>


pair<vvp, int> get_input()
{
    int width{}, height{}, player_index{}, node_index{-1};
    string prev{}, line{}, next{};
    vvp adj_list{};

    cin >> width >> height;
    // node_index = width + 2;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, prev);
    getline(cin, line);

    for(int i{0}; i < height - 1; i++)
    {
        getline(cin, next);


        for(int ii{1}; ii < width - 1; ii++)
        {
            char current{line[ii]};
            vector<pair<int, char>> neighbours{};
            ++node_index;

            if(current == '#')
            {

                adj_list.emplace_back(neighbours);
                continue;
            }


            if(current == 'P')
                player_index = node_index;

            char prev_node {line[ii - 1]};
            if(prev_node != '#')
                neighbours.emplace_back(make_pair(node_index - 1, prev_node));

            char next_node {line[ii + 1]};
            if(next_node != '#')
                neighbours.emplace_back(make_pair(node_index + 1, next_node));

            char above_node {prev[ii]};
            if(above_node != '#')
                neighbours.emplace_back(make_pair(node_index - width + 2, above_node));

            char below_node {next[ii]};
            if(below_node != '#')
                neighbours.emplace_back(make_pair(node_index + width - 2, below_node));

            adj_list.emplace_back(neighbours);
        }

        prev = line;
        line = next;
    }

    return make_pair(adj_list, player_index);
}


void bfs(vvp const& adj_matrix, int player)
{
    unordered_set<int> visted{};
    queue<pair<int, char>> node_queue{};
    node_queue.push(make_pair(player, 'P'));
    int current {}, total_gold{};
    char type{};

    while(!node_queue.empty())
    {
        // check if visited first
        current = node_queue.front().first;
        type = node_queue.front().second;
        node_queue.pop();

        if(visted.count(current))
            continue;

        visted.insert(current);
        if(type == 'G')
            total_gold++;

        // add neighbours to queue
        bool safe{true};
        for(auto const& neightbour : adj_matrix[current])
        {
            if(neightbour.second == 'T')
            {
                safe = false;
                break;
            }
        }
        if (!safe)
            continue;

        for(auto const& neighbour : adj_matrix[current])
        {
            node_queue.emplace(make_pair(neighbour.first, neighbour.second));
        }
    }

    printf("%d", total_gold);
}


int main()
{
    pair<vvp, int> adj_list {get_input()};
    bfs(adj_list.first, adj_list.second);
}