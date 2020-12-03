#include <iostream>
#include <algorithm>
#include <vector>

int part1() {
    std::vector<int> entries;
    int entry;

    while( std::cin >> entry )
        entries.push_back(entry);

    std::sort(entries.begin(), entries.end());

    int l = 0, r = entries.size() - 1;

    while( l < r ){
        int s = entries[l] + entries[r];
        if( s == 2020 ){
            std::cout << entries[l] * entries[r] << std::endl;
            return 0;
        }else if( s < 2020 ) {
            l++;
        }else {
            r--;
        }
    }
    std::cout << "Not found" << std::endl;

    return 0;
}

int part2() {
    std::vector<int> entries;
    int entry;

    while( std::cin >> entry )
        entries.push_back(entry);

    std::sort(entries.begin(), entries.end());

    for( int i = 0; i < entries.size(); i++ ){
        int k = 2020 - entries[i];
        int l = i + 1, r = entries.size() - 1;
        
        while( l < r ){
            int s = entries[l] + entries[r];
            if( s == k ){
                std::cout << entries[i] * entries[l] * entries[r] << std::endl;
                return 0;
            }else if( s < k ) {
                l++;
            }else {
                r--;
            }
        }

    }


    std::cout << "Not found" << std::endl;

    return 0;
}

int main() {
    return part2();
}