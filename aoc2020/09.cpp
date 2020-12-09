#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

bool sumInPreamble(const std::set<int>& set, int num){
    int limit = num / 2 + num % 2;
    for( auto n = set.begin(); n != set.end() && (*n < limit); n++ ){
        if( set.count(num - *n) != 0 )
            return true;
    }
    return false;
}

std::vector<int> numbers;

int loadUpToWeak(int psize){
    int start = 0;
    std::set<int> preamble;
    for( int number; std::cin >> number; ){
        if( preamble.size() == psize ){
            if( !sumInPreamble(preamble, number) )
                return number;

            preamble.erase(numbers[start++]);
        }
        preamble.insert(number);
        numbers.push_back(number);
    }
    return -1; // No weak number?
}

//Part 1
void part1() {
    std::cout << loadUpToWeak(25) << std::endl;
}

//Part 2
void part2() {
    int weak = loadUpToWeak(25);
    int s = 0, t = 0, sum = 0;
    while( sum != weak ){
        if( sum < weak )
            sum += numbers[t++];
        else
            sum -= numbers[s++];
    }
    std::sort( &numbers[s], &numbers[t] + 1);
    std::cout << numbers[s] + numbers[t] << std::endl;
}

int main() {
    part2();
}