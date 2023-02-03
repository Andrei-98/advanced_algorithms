#include <bitset>
#include <iostream>

int main() {
    std::bitset<8> bs{0b00000110};
    int startIndex = 1, endIndex = 5;
    std::bitset<8> mask = (1 << (endIndex - startIndex + 1)) - 1;
    std::bitset<8> sub_bs = (bs >> startIndex) & mask;
    int count = sub_bs.count();
    std::cout << "Number of set bits between indices " << startIndex << " and " << endIndex << ": " << count << '\n';
    return 0;
}