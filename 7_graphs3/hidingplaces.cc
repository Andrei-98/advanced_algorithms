#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <limits>
#include <string>
#include <unordered_map>

using namespace std;

#define vvvp vector<vector<vector<pair<int, int>>>>
#define vvp vector<vector<pair<int, int>>> 
#define vp vector<pair<int, int>>
#define pi pair<int, int>
#define si unordered_set<int>
#define qp queue<pair<int, int>>
#define vb vector<vector<bool>>


struct Node
{
    int cost{};
    pi prev{};
};


unordered_map<char, int> char_to_int = {
    {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3},
    {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}
};

unordered_map<int, char> int_to_char = {
    {0, 'a'}, {1, 'b'}, {2, 'c'}, {3, 'd'},
    {4, 'e'}, {5, 'f'}, {6, 'g'}, {7, 'h'}
};

unordered_map<int, int> int_to_row = {
    {0, 8}, {1, 7}, {2, 6}, {3, 5},
    {4, 4}, {5, 3}, {6, 2}, {7, 1}
};

std::unordered_map<int, int> row_to_int = {
    {8, 0}, {7, 1}, {6, 2}, {5, 3},
    {4, 4}, {3, 5}, {2, 6}, {1, 7}
};


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


bool compare(pi const& a, pi const& b) 
{
    if (a.second == b.second)
    {
        return a.first < b.first;
    } else
    {
        return a.second < b.second;
    }
}


void output_longest(vector<vector<Node>> const& tracker)
{
    vp all_coords{};
    int longest_dist{-1};

    for (int i{0}; i < 8; i++)
    {
        // cout << endl;
        for (int ii{0}; ii < 8; ii++)
        {
            int cost{tracker[i][ii].cost};
            // cout << cost << " ";

            if (cost == longest_dist)
            {
                all_coords.emplace_back(make_pair(i, ii));
            } else if (cost > longest_dist)
            {
                longest_dist = cost;
                all_coords.clear();
                all_coords.emplace_back(make_pair(i, ii));
            }
        }
    }
    // cout << endl;

    sort(all_coords.begin(), all_coords.end(), compare);

    printf("%d ", longest_dist);

    for (auto const& position : all_coords)
    {
        // printf("%d%d ", position.first, position.second);
        printf("%c%d ", int_to_char[position.first], int_to_row[position.second]);
    }
    printf("\n");
}


void bfs (vvvp const& board, pi const& start)
{
    vb visited(8, vector<bool>(8, false));
    qp next_node{};
    vector<vector<Node>> tracker(8, vector<Node>(8));

    next_node.push(start);
    tracker[start.first][start.second].cost = 0;
    tracker[start.first][start.second].prev = make_pair(-1, -1);

    int dist{};

    while(!next_node.empty())
    {
        pi cur {next_node.front()};
        next_node.pop();

        if(visited[cur.first][cur.second])
            continue;

        visited[cur.first][cur.second] = true;

        dist = tracker[cur.first][cur.second].cost; 

        for (pi const& neighbour : board[cur.first][cur.second])
        {
            next_node.push(neighbour);
            if (visited[neighbour.first][neighbour.second])
                continue;
            tracker[neighbour.first][neighbour.second].cost = dist + 1;
            tracker[neighbour.first][neighbour.second].prev = cur;
        }
    }

    output_longest(tracker);
}


int main()
{
    // int tests{}, row_index{}, col_index{};
    // char input[3];

    int tests{}, row_index{};
    char col_raw{};
    // scanf("%d", &tests);
    cin >> tests;

    while (tests--)
    {
        // scanf("%s", input);
        // row_index = 7 - (input[1] - '0');
        // col_index = input[0] - 'a';
        // scanf("%c%d", &col_raw, &row_index);
        cin >> col_raw >> row_index;


        vvvp board{make_chess_board()};

        bfs(board, make_pair(move(char_to_int[col_raw]), row_to_int[row_index]));
    }

    
}