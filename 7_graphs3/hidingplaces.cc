#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

#define vvvp vector<vector<vector<pair<int, int>>>>
#define vvp vector<vector<pair<int, int>>> 
#define vp vector<pair<int, int>>
#define pi pair<int, int>
#define si unordered_set<int>
#define qp queue<pair<int, int>>
#define vb vector<vector<bool>>

vp get_neighbours(int column, int row)
{
    vp neighbours{};

    neighbours.emplace_back(make_pair(column - 1, row + 2));
    neighbours.emplace_back(make_pair(column - 2, row + 1));
    neighbours.emplace_back(make_pair(column - 2, row - 1));
    neighbours.emplace_back(make_pair(column - 1, row - 2));
    neighbours.emplace_back(make_pair(column + 1, row - 2));
    neighbours.emplace_back(make_pair(column + 2, row - 1));
    neighbours.emplace_back(make_pair(column + 2, row + 1));
    neighbours.emplace_back(make_pair(column + 1, row + 2));

    neighbours.erase(
        remove_if(neighbours.begin(), neighbours.end(),
                  [] (pi const& n) {
                      return (n.first < 0 || n.second < 0 
                             || n.first > 7 || n.second > 7);
                  }),
        neighbours.end());

    return neighbours;
}


vvvp make_chess_board()
{
    vvvp board(8, vvp(8));

    for (size_t column{0}; column < 8; column++)
    {
        for (size_t row{0}; row < 8; row++)
        {
            // try to find the neighbours of each square 
            vp neighbours{get_neighbours(column, row)};
            board[column][row] = neighbours;
        }
    }

    return board;
}


void bfs (vvvp const& board, pi const& start)
{
    vb visited(8, vector<bool>(8, false));
    qp next_node{};
    vp tracker{};
    int steps{};


    next_node.push(start);

    while(!next_node.empty())
    {
        pi curr {next_node.front()};
        next_node.pop();

        if(visited[curr.first][curr.second])
            continue;

        visited[curr.first][curr.second] = true;

        tracker.clear();

        steps++;
        for (pi const& neighbour : board[curr.first][curr.second])
        {
            next_node.push(neighbour);
            tracker.emplace_back(neighbour);
        }
    }

    cerr << "steps " << steps << " possible ways " << tracker.size() << '\n';
    cerr << tracker[0].first << " " <<tracker[0].second << '\n';
}


int main()
{
    int tests{}, x{}, y{};
    scanf("%d", &tests);
    x = 3;
    y = 4;

    vvvp board{make_chess_board()};

    bfs(board, make_pair(x, y));

    
}