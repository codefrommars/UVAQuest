#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> loadSortedAdapters() {
    std::vector<int> adapters;
    adapters.push_back(0);
    for( int num ; std::cin >> num; )
        adapters.push_back(num);
    
    std::sort(begin(adapters), end(adapters));
    return adapters;
}

void part1() {
    std::vector<int> adapters = loadSortedAdapters();

    int dif[3] = {0, 0, 1};//The last has a difference of 3 jolts
    for( int i = 1; i < adapters.size(); i++)
        dif[ adapters[i] - adapters[i - 1] - 1 ]++;

    std::cout << dif[0] * dif[2] << std::endl;
}

void part2(){
    std::vector<int> adapters = loadSortedAdapters();
    
    int N = adapters.size();
    std::vector<int64_t> comb(N);
    
    comb[N - 1] = 1;
    for( int k = N - 2; k >= 0; k--)
        for( int i = k + 1; i < N && adapters[i] - adapters[k] <= 3; i++)
            comb[k] += comb[i];
    
    std::cout << comb[0] << std::endl;    
}

int main() {
    part2();
}
