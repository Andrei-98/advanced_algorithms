#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    // unordered_map<
    int n{};
    std::cin >> n;
    while(true)
    {
        std::cout << n << ' ';

        if (n % 2 != 0)
            n = 3 * n +1;
        else
            n = n / 2;

        if(n == 1)
            break;
    }
    cout << endl;
}